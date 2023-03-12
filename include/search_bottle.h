#ifndef SEARCH_BOTTLE_H
#define SEARCH_BOTTLE_H

/**
 * @brief Thread that will listen to type 3 and 4 messages from message queue
 * @param arg : won't be used
 * @return  nothing
 */
void *listen_search_bottle(void *arg);

#endif