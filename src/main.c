// #include <stdio.h>
#include <math.h>
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif
#include "hardware.h"
#include "os_manager.h"
#include "trajectory.h"

void* vaisseau_1(void* argument);
void* vaisseau_2(void* argument);
void* vaisseau_3(void* argument);
void* vaisseau_4(void* argument);
void* vaisseau_5(void* argument);
void* vaisseau_6(void* argument);
void* vaisseau_7(void* argument);
void* vaisseau_8(void* argument);
void* vaisseau_9(void* argument);

Mutex_t mutex_task1;
Mutex_t mutex_task2;
Mutex_t mutex_vaisseau_radar;
Mutex_t serial_mutex;

int main(void)
{
    hardware_init();
    os_initialisation();
    mutex_task1 = create_mutex();
    mutex_task2 = create_mutex();
    serial_mutex = create_mutex();
    mutex_vaisseau_radar = create_mutex();
    create_thread(vaisseau_1);
    create_thread(vaisseau_2);
    create_thread(vaisseau_3);
    create_thread(vaisseau_4);
    create_thread(vaisseau_5);
    create_thread(vaisseau_6);
    create_thread(vaisseau_7);
    create_thread(vaisseau_8);
    create_thread(vaisseau_9);
    os_start();
    while (1) {
    }
}

void* vaisseau_1(void* argument)
{
    while (1) {
        get_mutex(serial_mutex);
        puts("vaisseau 1\n");
        release_mutex(serial_mutex);
    }
    return NULL;
}

void* vaisseau_2(void* argument)
{

    while (1) {
        get_mutex(serial_mutex);
        puts("vaisseau 2\n");
        release_mutex(serial_mutex);
    }
    return NULL;
}

void* vaisseau_3(void* argument)
{
    while (1) {
        get_mutex(serial_mutex);
        puts("vaisseau 3\n");
        release_mutex(serial_mutex);
    }
    return NULL;
}

void* vaisseau_4(void* argument)
{
    while (1) {
        get_mutex(serial_mutex);
        puts("vaisseau 4\n");
        release_mutex(serial_mutex);
    }
    return NULL;
}

void* vaisseau_5(void* argument)
{
    while (1) {
        get_mutex(serial_mutex);
        puts("vaisseau 5\n");
        release_mutex(serial_mutex);
    }
    return NULL;
}

void* vaisseau_6(void* argument)
{
    while (1) {
        get_mutex(serial_mutex);
        puts("vaisseau 6\n");
        release_mutex(serial_mutex);
    }
    return NULL;
}

void* vaisseau_7(void* argument)
{
    while (1) {
        get_mutex(serial_mutex);
        puts("vaisseau 7\n");
        release_mutex(serial_mutex);
    }
    return NULL;
}

void* vaisseau_8(void* argument)
{
    while (1) {
        get_mutex(serial_mutex);
        puts("vaisseau 8\n");
        release_mutex(serial_mutex);
    }
    return NULL;
}

void* vaisseau_9(void* argument)
{
    while (1) {
        get_mutex(serial_mutex);
        puts("vaisseau 9\n");
        release_mutex(serial_mutex);
    }
    return NULL;
}
