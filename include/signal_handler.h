#ifndef SIGNAL_HANDLER_H
#define SIGNAL_HANDLER

/**
 * @brief Signal handler
 * @details This function is called when a signal is received. If the signal is SIGUSR1 then a listening socket is created  to handle connection of new module.
 * Otherwise, if it recieves a SIGALRM then the current socket is closed.
 * @param signum Signal number
 */
void signal_handler(int signum);

#endif
