// #include <stdio.h>
#include <math.h>
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif
#include "base.h"
#include "commands.h"
#include "hardware.h"
#include "os_manager.h"
#include "parsing.h"
#include "planet.h"
#include "spaceship.h"
#include "trajectory.h"

void* thread_attackers_1(void* argument);
void* thread_attackers_2(void* argument);
void* thread_attackers_3(void* argument);
void* thread_attackers_4(void* argument);
void* thread_attackers_5(void* argument);
void* thread_explorers_1(void* argument);
void* thread_explorers_2(void* argument);
void* thread_collectors_1(void* argument);
void* thread_collectors_2(void* argument);

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
    create_thread(thread_attackers_1);
    create_thread(thread_attackers_2);
    create_thread(thread_attackers_3);
    create_thread(thread_attackers_4);
    create_thread(thread_attackers_5);
    create_thread(thread_explorers_1);
    create_thread(thread_explorers_2);
    create_thread(thread_collectors_1);
    create_thread(thread_collectors_2);
    os_start();
    while (1) {
    }
}

void* thread_attackers_1(void* argument)
{
    uint16_t angle = 0;
    while (1) {
        get_mutex(serial_mutex);
        angle = get_angle(base.x, base.y, 10000, 10000);
        send_move_command(1, angle, 1000);
        release_mutex(serial_mutex);
    }
}

void* thread_attackers_2(void* argument)
{
    uint16_t angle = 0;
    while (1) {
        get_mutex(serial_mutex);
        angle = get_angle_to_follow(spaceships[1], spaceships[3], 100, 100);
        send_move_command(2, angle, 1000);
        release_mutex(serial_mutex);
    }
}

void* thread_attackers_3(void* argument)
{
    uint16_t angle = 0;
    while (1) {
        get_mutex(serial_mutex);
        angle = get_target_angle(spaceships[2], spaceships);
        if (angle == NOT_FOUND) {
            angle = (angle + 180) % 360;
        }
        send_fire_command(3, angle);
        release_mutex(serial_mutex);
    }
}

void* thread_attackers_4(void* argument)
{
    uint16_t angle = 0;
    while (1) {
        get_mutex(serial_mutex);
        angle = get_angle_to_follow(spaceships[4], spaceships[3], -100, 100);
        send_move_command(4, angle, 1000);
        release_mutex(serial_mutex);
    }
}

void* thread_attackers_5(void* argument)
{
    uint16_t angle = 0;
    while (1) {
        get_mutex(serial_mutex);
        angle = get_angle_to_follow(spaceships[5], spaceships[3], 100, 100);
        send_move_command(5, angle, 1000);
        release_mutex(serial_mutex);
    }
}

void* thread_explorers_1(void* argument)
{
    char buffer[256];
    uint16_t angle = 0;
    while (1) {
        get_mutex(serial_mutex);
        gets(buffer);
        get_mutex(mutex_vaisseau_radar);
        parse_response(buffer, planets, &nb_planets, spaceships, &nb_spaceships, &base);
        release_mutex(mutex_vaisseau_radar);
        angle = get_angle(base.x, base.y, 10000, 10000);
        send_move_command(6, angle, 1000);
        release_mutex(serial_mutex);
    }
}

void* thread_explorers_2(void* argument)
{
    char buffer[256];
    uint16_t angle = 0;
    while (1) {
        get_mutex(serial_mutex);
        gets(buffer);
        get_mutex(mutex_vaisseau_radar);
        parse_response(buffer, planets, &nb_planets, spaceships, &nb_spaceships, &base);
        release_mutex(mutex_vaisseau_radar);
        angle = get_angle(base.x, base.y, 15000, 15000);
        send_move_command(7, angle, 1000);
        release_mutex(serial_mutex);
    }
}

void* thread_collectors_1(void* argument)
{
    uint16_t angle = 0;
    Planet_t* target_planet1 = NULL;
    while (1) {
        get_mutex(serial_mutex);
        find_nearest_planet(&spaceships[7], planets, &target_planet1);
        angle = get_angle(spaceships[7].x, spaceships[7].y, target_planet1->x, target_planet1->y);
        send_move_command(8, angle, MAX_COLLECTORS_SPEED);
        release_mutex(serial_mutex);
    }
}

void* thread_collectors_2(void* argument)
{
    uint16_t angle = 0;
    Planet_t* target_planet2 = NULL;
    while (1) {
        get_mutex(serial_mutex);
        find_nearest_planet(&spaceships[8], planets, &target_planet2);
        angle = get_angle(spaceships[8].x, spaceships[8].y, target_planet2->x, target_planet2->y);
        send_move_command(9, angle, MAX_COLLECTORS_SPEED);
        release_mutex(serial_mutex);
    }
}
