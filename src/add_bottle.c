#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <curl/curl.h>
#include <msq-utils/msqutils.h>
#include <msq-utils/msqtypes.h>
#include <cjson/cJSON.h>
#include <db-utils/dbutils.h>

#include "../include/add_bottle.h"
#include "../include/configure_curl.h"

int msqid;
extern PGconn *conn;

void *add_bottle(void *arg)
{
    ResponseData data;
    msq_msg_t msg;
    CURLcode res;

    char url[MAX_LENGTH_BARCODE + strlen(OPENFOODFACT_API_URL)];
    char barcode[MAX_LENGTH_BARCODE];

    msqid = init_message_queue();
    CURL *curl = configure_curl(&data);

    while (1)
    {
        receive_message(&msg, ADD_BOTTLE_TYPE);

        strcpy(barcode, msg.message.scanner.barcode);
        sprintf(url, "%s%s.json", OPENFOODFACT_API_URL, barcode);
        curl_easy_setopt(curl, CURLOPT_URL, url);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s", curl_easy_strerror(res));
            continue;
        }

        cJSON *json = cJSON_Parse(data.data);
        reset_response_data(&data);

        cJSON *product = cJSON_GetObjectItem(json, "product");
        cJSON *product_name = cJSON_GetObjectItem(product, "product_name");
        cJSON *product_quantity = cJSON_GetObjectItem(product, "product_quantity");
        bottle_t bottle;

        // TODO: use the fonction provided by the db-utils lib to create the bottle_t struct
        bottle.id = NULL;
        strcpy(bottle.name, product_name->valuestring);
        strcpy(bottle.url, url);
        bottle.quantity = atoi(product_quantity->valuestring);
        bottle.module = NULL;
        bottle.price = msg.message.scanner.price;

        _print_bottle(&bottle);

        printf("Inserting bottle in db...");
        insert_bottle(conn, &bottle);
        printf("done\n");
    }

    curl_easy_cleanup(curl);
    pthread_exit(NULL);
}