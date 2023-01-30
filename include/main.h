#ifndef MAIN_H
#define MAIN_H

#include "server.h"

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
 * @brief Add a module to the database
 * @param root JSON object : payload of the packet
 */
void add_module(cJSON *root);

#endif
