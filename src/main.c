#include "../include/main.h"

PGconn *conn;
socket_client_t *clients; // need an array of file descriptors to com
int nb_clients = 0;

int main()
{
    clients = (socket_client_t *)malloc(CLIENT_GAP * sizeof(socket_client_t));

    pthread_t th_socket_server;
    pthread_create(&th_socket_server, NULL, server_socket, NULL);
    pthread_join(th_socket_server, NULL);
    return 0;
}