#include "cmsis_os2.h"
#include "os_manager.h"

const ThreadAttr_t thread_attr = {
    .stack_size = 2048,
    //.priority = osPriorityNormal
};

const MutexAttr_t serial_mutex_attr = {
    "SerialMutex",
    MutextRecursive | MutexPrioInherit,
    NULL,
    0U
};

Thread_t create_thread(ThreadFunc_t func)
{
    ThreadId_t thread_id = osThreadNew(func, NULL, &thread_attr);
    if (thread_id == NULL) {
        while (1) {
        }
    }
    Thread_t thread_t = (Thread_t)thread_id;
    return thread_t;
}

Mutex_t create_mutex()
{
    osMutexId_t mutex_id = osMutexNew(&serial_mutex_attr);
    if (mutex_id == NULL) {
        while (1) {
        }
    }
    Mutex_t mutex_t = (Mutex_t)mutex_id;
    return mutex_t;
}

void get_mutex(Mutex_t mutex)
{
    if (osMutexAcquire(mutex, osWaitForever) != osOK) {
        while (1) {
        }
    }
}

void release_mutex(Mutex_t mutex)
{
    if (osMutexRelease(mutex) != osOK) {
        while (1) {
        }
    }
}
