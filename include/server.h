#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>
#include <arpa/inet.h>
#include <db-utils/types.h>

#define SERVER_PORT 5000
#define MAX_PENDING_CONNECTIONS 5
#define MAX_BUFF 1024

#define CLIENT_GAP 5

typedef struct
{
    int sd;
    ip_address_t ip_address;
} socket_client_t;

typedef struct
{
    int sd;
    struct sockaddr_in sock_info;
} socket_info_t;

/**
 * @brief Thread function for incoming connections
 * @param arg non used
 */
void *server_socket(void *arg);

/**
 * @brief Thread function for the client socket
 * @param arg socket file descriptor
 */
void *client_handler(void *arg);

/**
 * @brief Print the clients array
 */
void _print_clients();

#endif