#include "../include/main.h"

extern int nb_clients;
extern socket_client_t *clients;
extern PGconn *conn;

void add_module(int sd, cJSON *root)
{
    ip_address_t ip_address;
    module_t module;

    strcpy(ip_address, cJSON_GetObjectItem(root, "ip_address")->valuestring);
    char *id_string = cJSON_GetObjectItem(root, "id")->valuestring;
    long long int id = strtol(id_string, NULL, 16);
    module.id = &id;
    strcpy(module.ip_address, ip_address);

    _print_module(&module);
    insert_module(conn, &module);
}

void add_client(int sd, ip_address_t ip_address)
{
    nb_clients++;
    printf("Adding client %s , nb of clients : %d\n", ip_address, nb_clients);
    if (nb_clients % CLIENT_GAP == 0)
        clients = (socket_client_t *)realloc(clients, (nb_clients + CLIENT_GAP) * sizeof(socket_client_t));

    socket_client_t client;
    client.sd = sd;
    strcpy(client.ip_address, ip_address);
    clients[nb_clients - 1] = client;
}

// TODO: need to deteck when a client socket is destroyed
void remove_client(ip_address_t ip_address)
{
    printf("Removing client %s\n", ip_address);
    for (int i = 0; i < nb_clients; i++)
    {
        if (strcmp(clients[i].ip_address, ip_address) == 0)
        {
            for (int j = i; j < nb_clients - 1; j++)
                clients[j] = clients[j + 1];
            nb_clients--;
            if (nb_clients % CLIENT_GAP == 0)
                clients = (socket_client_t *)realloc(clients, (nb_clients + CLIENT_GAP) * sizeof(socket_client_t));
            break;
        }
    }
}