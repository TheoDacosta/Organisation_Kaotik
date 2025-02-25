// #include <stdio.h>
#include <math.h>
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif
#include "commands.h"
#include "hardware.h"
#include "os_manager.h"
#include "parsing.h"
#include "trajectory.h"

void* vaisseau_1(void* argument);
void* vaisseau_2(void* argument);
void* vaisseau_3(void* argument);

Mutex_t mutex_vaisseau_radar;
Mutex_t serial_mutex;

Planet_t planets[NB_MAX_PLANETS];
uint16_t nb_planets;
Spaceship_t spaceships[NB_MAX_SPACESHIPS];
uint16_t nb_spaceships;
Base_t base;

int main(void)
{
    hardware_init();
    os_initialisation();
    serial_mutex = create_mutex();
    mutex_vaisseau_radar = create_mutex();
    create_thread(vaisseau_1);
    create_thread(vaisseau_2);
    os_start();
    while (1) {
    }
}

void* vaisseau_1(void* argument)
{
    char buffer[256];
    uint16_t angle = 0;
    while (1) {
        get_mutex(serial_mutex);
        angle = get_angle(base.x, base.y, 10000, 10000);
        send_move_command(3, angle, 1000);
        release_mutex(serial_mutex);
    }
}

void* vaisseau_2(void* argument)
{
    char buffer[256];
    uint16_t angle = 0;
    while (1) {
        get_mutex(serial_mutex);
        angle = deplace_space_from_an_other(1, 3, spaceships, &base);
        send_move_command(1, angle, 1000);
        release_mutex(serial_mutex);
    }
}

void* vaisseau_3(void* argument)
{
    char buffer[256];
    uint16_t angle = 0;
    while (1) {
        get_mutex(serial_mutex);
        angle = get_target_angle(spaceships[2], spaceships);
        if (angle == NOT_FOUND) {
            angle = (angle + 180) % 360;
        }
        send_fire_command(2, angle);
        release_mutex(serial_mutex);
    }
}
