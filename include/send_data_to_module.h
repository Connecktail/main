#ifndef SEND_DATA_TO_MODULE_H
#define SEND_DATA_TO_MODULE_H

#include "server.h"

/**
 * @brief  Send the enable led message to the right module
 * @param client : client socket
 */
void send_enable_led(socket_client_t client);

/**
 * @brief Send the enable_sound message to the right module
 * @param client : client socket
 */
void send_enable_buzzer(socket_client_t client);

#endif