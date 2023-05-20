# Main

## Purpose of the process :

Be able to create new module when pairing the module with the RPI. The module will be inserted in the database and a TCPsocket will be created to communicate with the module. To indentify the module, the module will send a message to the RPI with its MAC address.

## How to use it :

### Prerequisites :

- lib cJSON installed
- lib pq installed
- lib db-utils installed
- lib curl installed
- lib msq-utils installed
- lib shm-utils installed

That command will create the executable file "main" in the folder "build".

```bash
make
```

## How it works :

A listenning socket is created in order to wait for incoming connections from the modules. Every client is handled by a separated thread.
In another thread, we are listenning from incoming messages in the message queue. When a message of type 2 is received, it means that a bottle has been scanned. Then we retrieve the barcode and the price defined by the user in that message, we call the openfoodfact api to get some data about the product and finally we insert it into the database. We also listen messages of type 3 and 4 meaning we have to enable the led or the buzzer of a module.

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

Struct to store the result of the http request to the openfoodfact api :

```c
typedef struct
{
    char *data;
    size_t size;
} ResponseData;
```

## Main threads :

- Thread to handle incoming connections on the listenning socket :

```c
void *server_socket(void *arg)
```

- Thread function to add the bottle :

```c
void *add_bottle(void *arg)
```

## Functions :

### Server

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

- Function to remove the client from the array :

```c
void remove_client(ip_address_t ip_address)
```

- Function to send the response of the pairing process to the client :

```c
void pair_response(int sd, ip_address_t ip_address)
```

- Search a module depending on its ip address :

```c
socket_client_t search_bottle(ip_address_t ip_address)
```

### Bottle taken

- Function to move on to the next step of the order (when the bottle has been taken) :

```c
void bottle_taken()
```

### Configure curl

- Function to configure curl

```c
CURL *configure_curl(ResponseData *data)
```

- Callback function to handle the response of the openfoodfact api :

```c
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
```

- Function to reset the response data :

```c
void reset_response_data(ResponseData *data)
```

### Protocol

- Function to check if the data recieved is from the module (according to our protocol) :

```c
int check_protocol(int sd)
```

- Retrieve json object from data :

```c
cJSON *get_response_data(int sd)
```

### Search bottle

- Thead listening to message queue to enable led or buzzer

```c
void *listen_search_bottle(void *arg)
```

### Send data to module

- Send the enable_led message to a module :

```c
void send_enable_led(socket_client_t client)
```

- Send the enable_sound message to a module :

```c
void send_enable_buzzer(socket_client_t client)
```

### Set battery

- Update the battery level of a module :

```c
void set_battery(cJSON *data, ip_address_t ip_address, mac_address_t mac_address)
```

### Signal handler

- Handler of unix signals :

```c
void signal_handler(int signum)
```
