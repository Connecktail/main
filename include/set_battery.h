#ifndef SET_BATTERY_H
#define SET_BATTERY_H

/**
 * @brief Update the battery_level of the module in the database
 * @param data The JSON data object
 * @param ip_address The IP address of the module
 * @param mac_address The MAC address of the module
*/
void set_battery(cJSON *data, ip_address_t ip_address, mac_address_t mac_address);

#endif