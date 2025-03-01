#include "os_manager.h"
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Mutex_t create_mutex()
{
    pthread_mutex_t* mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
    if (mutex == NULL) {
        perror("mutex malloc failed");
        return NULL;
    }
    if (pthread_mutex_init(mutex, NULL) != 0) {
        perror("pthread_mutex_init failed");
        free(mutex);
        return NULL;
    }
    return (Mutex_t)mutex;
}

void get_mutex(Mutex_t mutex)
{
    if (mutex == NULL)
        return;
    pthread_mutex_lock((pthread_mutex_t*)mutex);
}

void release_mutex(Mutex_t mutex)
{
    if (mutex == NULL)
        return;
    pthread_mutex_unlock((pthread_mutex_t*)mutex);
    sched_yield();
}

Thread_t create_thread(ThreadFunc_t func, void* argument)
{
    pthread_t* new_thread = malloc(sizeof(pthread_t));
    if (new_thread == NULL) {
        perror("thread malloc failed");
        while (1)
            ;
    }
    if (pthread_create(new_thread, NULL, func, argument) != 0) {
        perror("thread creation failed");
        free(new_thread);
        while (1)
            ;
    }
    return (Thread_t)new_thread;
}

uint32_t get_current_timeMs()
{
    return (clock() * 1000) / CLOCKS_PER_SEC;
}

void os_initialisation()
{
}
void os_start()
{
    pthread_exit(NULL);
}
