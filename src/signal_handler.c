#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

#include "../include/server.h"
#include "../include/pair.h"

extern int sock;
extern sem_t accept_connection;

void signal_handler(int signum)
{
    if (signum == SIGUSR1)
    {
        alarm(PAIRING_TIME);
        sem_post(&accept_connection);
    }
    else if (signum == SIGALRM)
    {
        close(sock);
    }
}