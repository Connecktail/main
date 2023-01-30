#include <stdio.h>
#include <stdlib.h>
#include <db-utils/dbutils.h>
#include <pthread.h>
#include <cjson/cJSON.h>
#include "../include/main.h"

PGconn *conn;

int main()
{

    pthread_t th_socket_server;
    pthread_create(&th_socket_server, NULL, server_socket, NULL);
    pthread_join(th_socket_server, NULL);
    return 0;
}

void *server_socket(void *arg)
{
    char buffer[MAX_BUFF];
    int sock, sd;
    struct sockaddr_in svc, clt;
    struct sockaddr_in sock_info;
    socklen_t cltLen, infoLen = sizeof(struct sockaddr);
    conn = db_connect("localhost", "connecktail", "admin", "admin");

    sock = socket(PF_INET, SOCK_STREAM, 0);

    svc.sin_family = PF_INET;
    svc.sin_port = htons(SERVER_PORT);
    svc.sin_addr.s_addr = INADDR_ANY;

    memset(&svc.sin_zero, 0, 8);
    bind(sock, (struct sockaddr *)&svc, sizeof svc);
    listen(sock, MAX_PENDING_CONNECTIONS);

    getsockname(sock, (struct sockaddr *)&sock_info, &infoLen);
    printf("Server listening on %s, port %d\n", inet_ntop(AF_INET, &sock_info.sin_addr, buffer, sizeof(buffer)), ntohs(sock_info.sin_port));
    cltLen = sizeof(clt);

    while (1)
    {
        sd = accept(sock, (struct sockaddr *)&clt, &cltLen);
        getpeername(sd, (struct sockaddr *)&sock_info, &infoLen);
        printf("Connection from client %s on port %d\n", inet_ntop(AF_INET, &sock_info.sin_addr, buffer, sizeof(buffer)), ntohs(sock_info.sin_port));
        pthread_t th_client;
        pthread_create(&th_client, NULL, client_handler, (void *)&sd);
    }

    close(sock);
    pthread_exit(NULL);
}

void *client_handler(void *arg)
{
    int sd = *(int *)arg;
    char buffer[MAX_BUFF];

    read(sd, buffer, MAX_BUFF);

    cJSON *json = cJSON_Parse(buffer);
    cJSON *action = cJSON_GetObjectItem(json, "action");

    printf("Client sent: %s\n", buffer);

    if (strcmp(action->valuestring, "pair") == 0)
        add_module(json);

    close(sd);
    pthread_exit(NULL);
}

void add_module(cJSON *root)
{
    ip_address_t ip_address;
    module_t module;

    printf("action : pair\n");
    strcpy(ip_address, cJSON_GetObjectItem(root, "ip_address")->valuestring);
    char *ip_string = cJSON_GetObjectItem(root, "id")->valuestring;
    int id = (int)strtol(ip_string, NULL, 16);

    module.id = &id;
    strcpy(module.ip_address, ip_address);
    _print_module(&module);

    insert_module(conn, &module);
}