#include "os_manager.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

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
}

Thread_t create_thread(ThreadFunc_t func)
{
    pthread_t* new_thread = malloc(sizeof(pthread_t));
    if (new_thread == NULL) {
        perror("thread malloc failed");
        while (1)
            ;
    }
    if (pthread_create(new_thread, NULL, func, NULL) != 0) {
        perror("thread creation failed");
        free(new_thread);
        while (1)
            ;
    }
    return (Thread_t)new_thread;
}

void os_initialisation()
{
}
void os_start()
{
    pthread_exit(NULL);
}
