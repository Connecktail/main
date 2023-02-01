# Main

## Purpose of the process :

Be able to create new module when pairing the module with the RPI. The module will be inserted in the database and a TCPsocket will be created to communicate with the module. To indentify the module, the module will send a message to the RPI with its MAC address. That mac address will be converted in base 10 and will be used as the ID of the module.

## How to use it :

### Prerequisites :

- lib cJSON installed
- lib pq installed
- lib db-utils installed

That command will create the executable file "main" in the folder "build".

```bash
make
```

## How it works :

A listenning socket is created in order to wait for incoming connections from the modules. Every client is handled by a separated thread.

## Data structures :

Some structs have been defined with a view to passing multiple arguments ot threads, and store sockets.
Struct to store client socket in an array :

```c
typedef struct
{
    int sd;
    ip_address_t ip_address;
} socket_client_t;
```

Struct to pass multiple arguments to threads :

```c
typedef struct
{
    int sd;
    struct sockaddr_in sock_info;
} socket_info_t;
```

## Functions :

### Server

- Thread to handle incoming connections on the listenning socket :

```c
void *server_socket(void *arg)
```

- Thread to handle incoming messages from one client :

```c
void *client_handler(void *arg)
```

- Function to print the list of connected clients :

```c
void _print_clients()
```

### Pair

- Function to add a module in the database :

```c
void add_module(int sd, cJSON *root)
```

- Function to add the client in the array :

```c
void add_client(int sd, ip_address_t ip_address)
```

> TODO: We need to first detect when the connection is closed by the client

- Function to remove the client from the array :

```c
void remove_client(ip_address_t ip_address)
```
