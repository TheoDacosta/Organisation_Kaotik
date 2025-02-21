#include <math.h>
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif
#include "hardware.h"
#include "os_manager.h"

void* start_default_task(void* argument);
void* start_default_task2(void* argument);

Mutex_t mutex_task1;
Mutex_t mutex_task2;

int main(void)
{
    hardware_init();
    os_initialisation();
    mutex_task1 = create_mutex();
    mutex_task2 = create_mutex();
    create_thread(start_default_task);
    create_thread(start_default_task2);
    os_start();
    while (1) {
    }
}

void* start_default_task(void* argument)
{
    while (1) {
        get_mutex(mutex_task1);
        puts("default task 1\n");
        release_mutex(mutex_task2);
    }
    return NULL;
}

void* start_default_task2(void* argument)
{
    while (1) {
        get_mutex(mutex_task2);
        puts("default task 2\n");
        release_mutex(mutex_task1);
    }
    return NULL;
}
