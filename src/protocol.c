#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <cjson/cJSON.h>
#include "../include/protocol.h"

int check_protocol(int sd)
{
    char flag;
    int nb = read(sd, &flag, 1);
    if (nb == 0)
        return -1;
    if (flag == PROTOCOL_CHECK)
        return 1;
    else
    {
        while (nb > 0)
            nb = read(sd, &flag, 1);
        return 0;
    }
}

cJSON *get_response_data(int sd)
{
    char carac;
    char length_as_string[5];
    int i = 0;

    // Get the length of the data
    do
    {
        read(sd, &carac, 1);
        length_as_string[i++] = carac;
    } while (carac != ' ');

    length_as_string[i] = '\0';
    int length = atoi(length_as_string);

    // Retrieve data
    char *content = (char *)malloc((length + 1) * sizeof(char));
    for (int i = 0; i < length; i++)
        read(sd, &content[i], 1);
    content[length] = '\0';
    return cJSON_Parse(content);
}