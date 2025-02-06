#include <math.h>
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif
#include "cmsis_os.h"
#include "main.h"
#include "os_manager.h"

// Mettre çà aussi dans le .h
osThreadId_t defaultTaskHandle;

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
    defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &thread_attr);
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

void thread_1(void* argument)
{
    while (1) {
        puts("Thread 1\n");
        osDelay(1);
    }
}

void thread_2(void* argument)
{
    while (1) {
        puts("Thread 2\n");
        osDelay(1);
    }
}

void thread_3(void* argument)
{
    while (1) {
        puts("Thread 3\n");
        osDelay(1);
    }
}

void thread_4(void* argument)
{
    while (1) {
        puts("Thread 4\n");
        osDelay(1);
    }
}

void thread_5(void* argument)
{
    while (1) {
        puts("Thread 5\n");
        osDelay(1);
    }
}

void thread_6(void* argument)
{
    while (1) {
        puts("Thread 6\n");
        osDelay(1);
    }
}

void thread_7(void* argument)
{
    while (1) {
        puts("Thread 7\n");
        osDelay(1);
    }
}

void thread_8(void* argument)
{
    while (1) {
        puts("Thread 8\n");
        osDelay(1);
    }
}

void thread_9(void* argument)
{
    while (1) {
        puts("Thread 9\n");
        osDelay(1);
    }
}
