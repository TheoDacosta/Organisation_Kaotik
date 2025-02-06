#include <math.h>
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif
#include "main.h"
#include "os_manager.h"

void StartDefaultTask(void* argument);

int main(void)
{
    hardware_init();
    os_initialisation();
    create_thread(StartDefaultTask);
    os_start();
    while (1) {
    }
}

void StartDefaultTask(void* argument)
{
    while (1) {
        puts("Hello world\n");
    }
}
