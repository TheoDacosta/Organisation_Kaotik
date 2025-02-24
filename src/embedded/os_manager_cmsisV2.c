#include "cmsis_os2.h"
#include "os_manager.h"

const osThreadAttr_t thread_attr = {
    .name = "Thread",
    .stack_size = 1024,
    .priority = (osPriority_t)osPriorityNormal,
};

const osMutexAttr_t serial_mutex_attr = {
    "SerialMutex",
    osMutexRecursive | osMutexPrioInherit,
    NULL,
    0U
};

void os_initialisation()
{
    osKernelInitialize();
}
void os_start()
{
    osKernelStart();
}

Thread_t create_thread(ThreadFunc_t func)
{
    osThreadId_t new_thread_id = osThreadNew((osThreadFunc_t)func, NULL, &thread_attr);
    if (new_thread_id == NULL) {
        while (1)
            ;
    }
    return (Thread_t)new_thread_id;
}

Mutex_t create_mutex()
{
    osMutexId_t new_mutex_id = osMutexNew(&serial_mutex_attr);
    if (new_mutex_id == NULL) {
        while (1)
            ;
    }
    return (Mutex_t)new_mutex_id;
}

void get_mutex(Mutex_t mutex)
{
    if (osMutexAcquire((osMutexId_t)mutex, osWaitForever) != osOK) {
        while (1)
            ;
    }
}

void release_mutex(Mutex_t mutex)
{
    if (osMutexRelease((osMutexId_t)mutex) != osOK) {
        while (1)
            ;
    }
    osThreadYield(); //  Permet de bien repasser la main au thread de meme priorité
}
