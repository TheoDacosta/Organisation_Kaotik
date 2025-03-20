#include "cmsis_os2.h"
#include "os_manager.h"
#include "stm32f4xx_hal.h"

typedef void (*OsThreadFunc_t)(void* argument);

/*
 /!\ Pour la gestion des mutexes par les threads, stack_size doit être > 1024
     Mais stack_size < 2048 pour ne pas dépasser la taille de la pile avec 10 threads en même temps (9 threads + main)
 Dans le cas où on aurai moins de threads lancés simultanément, on pourrait augmenter la taille de la pile des threads
 Ou alors on pourrait augmenter la taille allouée à la pile
*/
const osThreadAttr_t thread_attr = {
    .name = "Thread",
    .stack_size = 1536,
    .priority = (osPriority_t)osPriorityNormal,
};

const osMutexAttr_t mutex_attr = {
    "Mutex",
    osMutexRecursive | osMutexPrioInherit,
    NULL,
    0U
};

void os_initialisation(int argc, char* argv[])
{
    osKernelInitialize();
}
void os_start()
{
    osKernelStart();
}

Thread_t create_thread(ThreadFunc_t func, void* argument)
{
    osThreadId_t new_thread_id = osThreadNew((OsThreadFunc_t)func, argument, &thread_attr);
    if (new_thread_id == NULL) {
        while (1)
            ;
    }
    return (Thread_t)new_thread_id;
}

Mutex_t create_mutex()
{
    osMutexId_t new_mutex_id = osMutexNew(&mutex_attr);
    if (new_mutex_id == NULL) {
        while (1)
            ;
    }
    return (Mutex_t)new_mutex_id;
}

void get_mutex(Mutex_t mutex)
{
    osStatus_t status = osMutexAcquire((osMutexId_t)mutex, osWaitForever);
    if (status != osOK) {
        while (1)
            ;
    }
}

void release_mutex(Mutex_t mutex)
{
    osStatus_t status = osMutexRelease((osMutexId_t)mutex);
    if (status != osOK) {
        while (1)
            ;
    }
    osThreadYield(); // Permet de repasser la main à un autre thread de même priorité si existant et prêt
}

uint32_t get_current_timeMs()
{
    return HAL_GetTick();
}
