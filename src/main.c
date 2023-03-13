#include <db-utils/dbutils.h>
#include <stdlib.h>
#include <pthread.h>
#include "../include/main.h"
#include "../include/server.h"
#include "../include/add_bottle.h"

PGconn *conn;
socket_client_t *clients; // need an array of file descriptors to com
int nb_clients = 0;

int main()
{
    clients = (socket_client_t *)malloc(CLIENT_GAP * sizeof(socket_client_t));

    pthread_t th_socket_server, th_add_bottle;

    pthread_create(&th_socket_server, NULL, server_socket, NULL);
    pthread_create(&th_add_bottle, NULL, add_bottle, NULL);

    pthread_t threads[THREAD_NB] = {th_socket_server, th_add_bottle};

    for (int i = 0; i < THREAD_NB; i++)
        pthread_join(threads[i], NULL);
    return 0;
}