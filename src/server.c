#include <pthread.h>
#include <db-utils/dbutils.h>
#include <db-utils/types.h>
#include <cjson/cJSON.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>
#include <shm-utils/shmutils.h>

#include "../include/server.h"
#include "../include/search_bottle.h"
#include "../include/pair.h"
#include "../include/signal_handler.h"
#include "../include/protocol.h"
#include "../include/bottle_taken.h"

extern int nb_clients;
extern socket_client_t *clients;
extern PGconn *conn;
int sock;

sem_t accept_connection;

void _print_clients()
{
    for (int i = 0; i < nb_clients; i++)
        printf("Client : %s\n", clients[i].ip_address);
}

void *server_socket(void *arg)
{
    sem_init(&accept_connection, 0, 0);

    struct sigaction newact;
    newact.sa_handler = signal_handler;
    sigemptyset(&newact.sa_mask);
    newact.sa_flags = 0;
    sigaction(SIGUSR1, &newact, NULL);
    sigaction(SIGALRM, &newact, NULL);

    pthread_t th_listen_search_bottle;
    pthread_create(&th_listen_search_bottle, NULL, listen_search_bottle, NULL);

    char buffer[MAX_BUFF];
    int sd;
    struct sockaddr_in svc, clt;
    struct sockaddr_in sock_info;
    socklen_t cltLen, infoLen = sizeof(struct sockaddr);
    conn = db_connect("localhost", "connecktail", "admin", "admin");

    svc.sin_family = PF_INET;
    svc.sin_port = htons(SERVER_PORT);
    svc.sin_addr.s_addr = INADDR_ANY;
    memset(&svc.sin_zero, 0, 8);

    int reuseaddr = 1;

    while (1)
    {
        sem_wait(&accept_connection);

        sock = socket(PF_INET, SOCK_STREAM, 0);
        setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr));
        bind(sock, (struct sockaddr *)&svc, sizeof svc);

        getsockname(sock, (struct sockaddr *)&sock_info, &infoLen);
        printf("Server listening on %s, port %d\n", inet_ntop(AF_INET, &sock_info.sin_addr, buffer, sizeof(buffer)), ntohs(sock_info.sin_port));
        listen(sock, MAX_PENDING_CONNECTIONS);

        cltLen = sizeof(clt);
        sd = accept(sock, (struct sockaddr *)&clt, &cltLen);

        shm_t *shm = get_shm();
        if (shm->device_handler_pid != 0)
            kill(shm->device_handler_pid, SIGUSR1); // Notify the device handler that a client is connected

        getpeername(sd, (struct sockaddr *)&sock_info, &infoLen);
        printf("Connection from client %s on port %d\n", inet_ntop(AF_INET, &sock_info.sin_addr, buffer, sizeof(buffer)), ntohs(sock_info.sin_port));

        socket_info_t socket_info;
        socket_info.sd = sd;
        socket_info.sock_info = sock_info;

        pthread_t th_client;
        pthread_create(&th_client, NULL, client_handler, (void *)&socket_info);
    }

    close(sock);
    pthread_exit(NULL);
}

void *client_handler(void *arg)
{
    socket_info_t socket_info = *(socket_info_t *)arg;
    int sd = socket_info.sd;
    struct sockaddr_in sock_info = socket_info.sock_info;
    ip_address_t ip_address;
    inet_ntop(AF_INET, &sock_info.sin_addr, ip_address, sizeof(ip_address));

    add_client(sd, ip_address);
    _print_clients();

    while (1)
    {
        int res = check_protocol(sd);
        if (res == 0)
            break;
        else if (res == -1)
        {
            printf("Client %s disconnected\n", ip_address);
            remove_client(ip_address);
            close(sd);
            pthread_exit(NULL);
        }

        cJSON *json = get_response_data(sd);
        cJSON *action = cJSON_GetObjectItem(json, "action");

        if (strcmp(action->valuestring, "pair") == 0)
        {
            printf("action : pair\n");
            add_module(sd, json);
            pair_response(sd, ip_address);
            close(sock);
        }
        else if (strcmp(action->valuestring, "bottle_taken") == 0)
        {
            printf("action : bottle_taken\n");
            bottle_taken();
        }
    }

    remove_client(ip_address);
    close(sd);
    pthread_exit(NULL);
}