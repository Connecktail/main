#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <cjson/cJSON.h>

#define PROTOCOL_CHECK 0x2a

/**
 * @brief Function to check if the message received is a valid protocol
 * @param sd Socket descriptor
 * @return  1 if the message is valid, -1 if the connection is closed, 0 otherwise
 * @note It the protocol is not valid, the message is discarded
 */
int check_protocol(int sd);

/**
 * @brief Function retrieving data from the message received through the socket
 * @param sd Socket descriptor
 * @return  Pointer to the cJSON object containing the data
 * @note The protocol must be valid to use this function
 */
cJSON *get_response_data(int sd);

#endif