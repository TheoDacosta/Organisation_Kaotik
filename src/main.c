#include <math.h>
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif
#include "cmsis_os.h"
#include "main.h"

// Mettre çà aussi dans le .h 
osThreadId_t defaultTaskHandle;

// Mettre les arguments du mutex dans le .h

void StartDefaultTask(void* argument);

int main(void)
{
    hardware_init();

    osKernelInitialize();
    // Mettre toute les task dans le .h 

    const osThreadAttr_t defaultTask_attributes = {
        .name = "defaultTask",
        .priority = (osPriority_t)osPriorityNormal,
        .stack_size = 128,
    };
    defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);
    // Partie pour rajouter tout les threads
    osKernelStart();

    while (1) {
    }
}

void StartDefaultTask(void* argument)
{
    while (1) {
        puts("Hello world\n");
        osDelay(1);
    }
}
