#ifndef OS_MANAGER_H_
#define OS_MANAGER_H_
#include <stdint.h>
#include <stdlib.h>

typedef void* Thread_t;
typedef void* (*ThreadFunc_t)(void* argument);
typedef void* Mutex_t;

void os_initialisation();
void os_start();

Mutex_t create_mutex();
void get_mutex(Mutex_t mutex);
void release_mutex(Mutex_t mutex);

Thread_t create_thread(ThreadFunc_t func, void* argument);
uint32_t get_current_timeMs();

#endif // OS_MANAGER_H_
