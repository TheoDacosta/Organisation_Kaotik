#include "cmsis_os2.h"
#include "os_manager.h"
#include "stm32f4xx_hal.h"

typedef void (*OsThreadFunc_t)(void* argument);

const osThreadAttr_t thread_attr = {
    .name = "Thread",
    .stack_size = 1024,
    .priority = (osPriority_t)osPriorityNormal,
};

const osMutexAttr_t serial_mutex_attr = {
    "SerialMutex",
    osMutexPrioInherit | osMutexRobust, // look reste bloqué sur -> osMutexRecursive | osMutexPrioInherit, osMutexRobust -< yield ?
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
    osMutexId_t new_mutex_id = osMutexNew(&serial_mutex_attr);
    if (new_mutex_id == NULL) {
        while (1)
            ;
    }
    return (Mutex_t)new_mutex_id;
}

void get_mutex(Mutex_t mutex)
{
    // changer le osWaitForever par un timeout dans le cas ou il reste bloqué
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

uint32_t get_current_timeMs()
{
    return HAL_GetTick();
}
