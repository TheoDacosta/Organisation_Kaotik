#include "os_manager.h"
#include "cmsis_os2.h"

#define osWaitForever         0xFFFFFFFFU
#define MutextRecursive      0x00000001U ///< Recursive mutex.
#define MutexPrioInherit    0x00000002U ///< Priority inherit protocol.
#define MutexRobust         0x00000008U ///< Robust mutex.


typedef enum {
  osOK                      =  0,         ///< Operation completed successfully.
  osError                   = -1,         ///< Unspecified RTOS error: run-time error but no other error message fits.
  osStatusReserved          = 0x7FFFFFFF  ///< Prevents enum down-size compiler optimization.
} osStatus_t;



// Mise en place de la structure pour les priorités
typedef enum {
 PriorityNone          =  0,         ///< No priority (not initialized).
  PriorityNormal        = 24,         ///< Priority: normal
  PriorityHigh          = 40,         ///< Priority: high
  PriorityError         = -1,         ///< System cannot determine priority or illegal priority.
  PriorityReserved      = 0x7FFFFFFF  ///< Prevents enum down-size compiler optimization.
}Priority_t;



const ThreadAttr_t thread_attr = {
    .stack_size = 2048,
    //.priority = osPriorityNormal
};

// Mise en place des paramètres des mutexes
//Changer le nom en un truc plus génér
const MutexAttr_t serial_mutex_attr = {
    "SerialMutex",
    MutextRecursive | MutexPrioInherit, 
    NULL,
    0U
};

Thread_t create_thread(ThreadFunc_t func, const ThreadAttr_t *argument)
{ 
    ThreadId_t thread_id = osThreadNew(func, NULL, argument);
    Thread_t thread_t = (Thread_t)thread_id;
    if (thread_t != NULL) {
        return thread_t;
    }
    return thread_t;
}



//Mettre un mutexT
Mutex_t create_mutex()
{
    Mutex_t mutex_t = osMutexNew(&serial_mutex_attr);
    if (mutex_t != NULL) {
        return mutex_t;
    }
    return mutex_t;
}


void get_mutex(Mutex_t mutex_id)
{
    if (osMutexAcquire(mutex_id, osWaitForever) != osOK) {
        get_mutex(mutex_id);
    }
}

void release_mutex(Mutex_t mutex_id)
{
    if (osMutexRelease(mutex_id) != osOK) {
        release_mutex(mutex_id);
    }
}
