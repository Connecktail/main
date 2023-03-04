#ifndef ADD_BOTTLE_H
#define ADD_BOTTLE_H

#define OPENFOODFACT_API_URL "https://world.openfoodfacts.org/api/v0/product/"

/**
 * @brief thread function to add a bottle scanned in the database
 */
void *add_bottle(void *arg);

#endif