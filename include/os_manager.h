#ifndef OS_MANAGER_H_
#define OS_MANAGER_H_
#include <stdint.h>
#include <stdlib.h>

typedef void* Thread_t;
typedef void (*ThreadFunc_t)(void* argument);
typedef void* Mutex_t;

Mutex_t create_mutex();
void get_mutex(Mutex_t mutex_id);
void release_mutex(Mutex_t mutex_id);

Thread_t create_thread(ThreadFunc_t func);

#endif // OS_MANAGER_H_
