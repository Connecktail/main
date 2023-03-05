#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>
#include "../include/configure_curl.h"

CURL *configure_curl(ResponseData *data)
{
    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)data);
    return curl;
}

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    size_t realsize = size * nmemb;
    ResponseData *data = (ResponseData *)userdata;
    data->data = realloc(data->data, data->size + realsize + 1);
    memcpy(&(data->data[data->size]), ptr, realsize);
    data->size += realsize;
    data->data[data->size] = '\0';
    return realsize;
}

void reset_response_data(ResponseData *data)
{
    memset(data->data, 0, data->size);
    data->size = 0;
}
