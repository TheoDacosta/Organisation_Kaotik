#include "os_manager.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Définition des types
struct ThreadWrapper {
    pthread_t thread;
};

struct MutexWrapper {
    pthread_mutex_t mutex;
};

Mutex_t create_mutex() {
    struct MutexWrapper* mutex = (struct MutexWrapper*)malloc(sizeof(struct MutexWrapper));
    if (mutex == NULL) {
        perror("malloc failed");
        return NULL;
    }
    if (pthread_mutex_init(&mutex->mutex, NULL) != 0) {
        perror("pthread_mutex_init failed");
        free(mutex);
        return NULL;
    }
    return (Mutex_t)mutex;
}

void get_mutex(Mutex_t mutex_id) {
    if (mutex_id == NULL) return;
    struct MutexWrapper* mutex = (struct MutexWrapper*)mutex_id;
    pthread_mutex_lock(&mutex->mutex);
}

void release_mutex(Mutex_t mutex_id) {
    if (mutex_id == NULL) return;
    struct MutexWrapper* mutex = (struct MutexWrapper*)mutex_id;
    pthread_mutex_unlock(&mutex->mutex);
}

Thread_t create_thread(ThreadFunc_t func) {
    pthread_t *monthread = malloc(sizeof(pthread_t));
    if(monthread==NULL)
    {
        perror("allocation mémoire non fonctionnelle");
        while(1);
    }
    if (pthread_create(monthread, NULL, func, NULL) != 0) {
        perror("pthread_create failed");
        while(1);
    }
    return (Thread_t)monthread;
}

void os_initialisation()
{

}
void os_start()
{
    pthread_exit(NULL);
}