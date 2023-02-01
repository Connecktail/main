#ifndef PAIR_H
#define PAIR_H

#include <cjson/cJSON.h>
#include <db-utils/dbutils.h>

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

#endif