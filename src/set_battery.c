#include <cjson/cJSON.h>
#include <db-utils/dbutils.h>
#include <db-utils/types.h>
#include <string.h>
#include "../include/set_battery.h"

extern PGconn *conn;

void set_battery(cJSON *data, ip_address_t ip_address, mac_address_t mac_address)
{
    cJSON *battery_level = cJSON_GetObjectItem(data, "battery_level");
    int battery_level_int = battery_level->valueint;
    module_t module;
    strcpy(module.mac_address, mac_address);
    update_module(conn, &module, ip_address, &battery_level_int);
}