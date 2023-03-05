#ifndef CONFIGURE_CURL_H
#define CONFIGURE_CURL_H

#include <stdio.h>
#include <curl/curl.h>

typedef struct
{
    char *data;
    size_t size;
} ResponseData;

/**
 * @brief Configure curl
 * @param data : pointer to the ResponseData struct
 * @return CURL * : pointer to the curl struct
 */
CURL *configure_curl(ResponseData *data);

/**
 * @brief Callback function for curl to write data
 * @param ptr : pointer to the data
 * @param size : size of the data
 * @param nmemb : number of elements
 * @param userdata : pointer to the ResponseData struct where the data will be stored
 * @return size_t : size of the data
 */
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);

/**
 * @brief Reset the ResponseData struct
 * @param data : pointer to the ResponseData struct
 */
void reset_response_data(ResponseData *data);

#endif