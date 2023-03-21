#ifndef PAIR_H
#define PAIR_H

#define PAIRING_TIME 30

#include <cjson/cJSON.h>
#include <db-utils/types.h>

/**
 * @brief Add a module to the database
 * @param sd socket file descriptor
 * @param root JSON object : payload of the packet
 */
void add_module(int sd, cJSON *root);

/**
 * @brief Add a client to the clients array
 * @param sd socket file descriptor
 * @param ip_address ip address of the client
 */
void add_client(int sd, ip_address_t ip_address);

/**
 * @brief Remove a client from the clients array
 * @param ip_address ip address of the client
 */
void remove_client(ip_address_t ip_address);

/**
 * @brief Send the response to client finalizing the pairing process
 * @param sc socket file descriptor
 * @param ip_address ip address of the client
 */
void pair_response(int sd, ip_address_t ip_address);

/**
 * @brief Search a socket from the clients array
 * @param ip_address ip address of the client
 * @return socket_client_t
 */
socket_client_t search_bottle(ip_address_t ip_address);

#endif