#include <pthread.h>
#include <msq-utils/msqutils.h>
#include <msq-utils/msqtypes.h>
#include <stdio.h>
#include <string.h>

#include "../include/server.h"
#include "../include/search_bottle.h"
#include "../include/pair.h"
#include "../include/send_data_to_module.h"

extern int msqid;
extern socket_client_t *clients;
extern int nb_clients;

void *listen_search_bottle(void *arg)
{
    msq_msg_t msg_enable_led, msg_enable_buzzer;
    ssize_t size_enable_led_type, size_enable_buzzer_type;
    ip_address_t ip_address;
    while (1)
    {
        do
        {
            size_enable_led_type = receive_message(&msg_enable_led, ENABLE_LED_TYPE, 1);
            size_enable_buzzer_type = receive_message(&msg_enable_buzzer, ENABLE_BUZZER_TYPE, 1);
        } while (size_enable_buzzer_type == -1 && size_enable_led_type == -1);

        strcpy(ip_address, size_enable_buzzer_type != -1 ? msg_enable_buzzer.message.buzzer.ip_address : msg_enable_led.message.led.ip_address);
        socket_client_t client = search_bottle(ip_address);
        if (client.sd == -1)
        {
            printf("client %s not found\n", ip_address);
            continue;
        }
        if (size_enable_led_type != -1)
            send_enable_led(client);
        else
            send_enable_buzzer(client);
    }

    pthread_exit(NULL);
}