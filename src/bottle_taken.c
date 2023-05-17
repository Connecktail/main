#include <shm-utils/shmutils.h>
#include <signal.h>
#include <stdio.h>
#include "../include/bottle_taken.h"

extern int shmid;

void bottle_taken()
{
    shm_t *shm = get_shm();
    printf("sending SIPROF to %d\n", shm->device_handler_pid);
    kill(shm->device_handler_pid, SIGPROF);
}