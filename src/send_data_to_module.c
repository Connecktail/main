#include "../include/send_data_to_module.h"
#include "../include/server.h"

void send_enable_led(socket_client_t client)
{
    char buffer[] = "*23 {\"action\":\"enable_led\"}";
    send(client.sd, buffer, 27, 0);
}

void send_enable_buzzer(socket_client_t client)
{
    char buffer[] = "*26 {\"action\":\"enable_buzzer\"}";
    send(client.sd, buffer, 30, 0);
}