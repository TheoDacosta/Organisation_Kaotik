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

Planet_t planets[NB_MAX_PLANETS];
uint16_t nb_planets;
Spaceship_t spaceships[NB_MAX_SPACESHIPS];
uint16_t nb_spaceships;
Base_t base;

int main(void)
{
    char buffer[MAX_RESPONSE_SIZE];
    hardware_init();
    os_initialisation();
    serial_mutex = create_mutex();
    mutex_vaisseau_radar = create_mutex();

    // Premier scan radar
    send_radar_command(6, buffer);
    get_mutex(mutex_vaisseau_radar);
    parse_response(buffer, planets, &nb_planets, spaceships, &nb_spaceships, &base);
    release_mutex(mutex_vaisseau_radar);

    create_thread(thread_attackers_1, NULL);
    create_thread(thread_attackers_2, NULL);
    create_thread(thread_attackers_3, NULL);
    create_thread(thread_attackers_4, NULL);
    create_thread(thread_attackers_5, NULL);
    create_thread(thread_explorers_1, NULL);
    create_thread(thread_explorers_2, NULL);
    create_thread(thread_collectors_1, NULL);
    create_thread(thread_collectors_2, NULL);
    os_start();
    while (1) {
    }
}

void* thread_attackers_1(void* argument)
{
    uint16_t angle = 0;
    Spaceship_t* my_spaceship = find_spaceship(0, 1, spaceships, nb_spaceships);
    while (1) {
        angle = get_angle_to_follow(*my_spaceship, spaceships[5], -100, 100);
        send_move_command(1, angle, MAX_ATTACKERS_SPEED);
    }
}

void* thread_attackers_2(void* argument)
{
    uint16_t angle = 0;
    Spaceship_t* my_spaceship = find_spaceship(0, 2, spaceships, nb_spaceships);
    while (1) {
        angle = get_angle_to_follow(*my_spaceship, spaceships[5], 100, 100);
        send_move_command(2, angle, MAX_ATTACKERS_SPEED);
    }
}

void* thread_attackers_3(void* argument)
{
    uint16_t angle = 0;
    Spaceship_t* my_spaceship = find_spaceship(0, 3, spaceships, nb_spaceships);
    while (1) {
        angle = get_angle_to_follow(*my_spaceship, spaceships[5], 0, 100);
        if (angle == NOT_FOUND) {
            angle = (angle + 180) % 360;
        }
        send_move_command(3, angle, MAX_ATTACKERS_SPEED);
    }
}

void* thread_attackers_4(void* argument)
{
    uint16_t angle = 0;
    Spaceship_t* my_spaceship = find_spaceship(0, 4, spaceships, nb_spaceships);
    while (1) {
        angle = get_angle_to_follow(*my_spaceship, spaceships[6], -100, 100);
        send_move_command(4, angle, MAX_ATTACKERS_SPEED);
    }
}

void* thread_attackers_5(void* argument)
{
    uint16_t angle = 0;
    Spaceship_t* my_spaceship = find_spaceship(0, 5, spaceships, nb_spaceships);
    while (1) {
        angle = get_angle_to_follow(*my_spaceship, spaceships[6], 100, 100);
        send_move_command(5, angle, MAX_ATTACKERS_SPEED);
    }
}

void* thread_explorers_1(void* argument)
{
    char buffer[MAX_RESPONSE_SIZE];
    uint16_t angle = 0;
    Spaceship_t* my_spaceship = find_spaceship(0, 6, spaceships, nb_spaceships);
    while (1) {
        send_radar_command(6, buffer);
        get_mutex(mutex_vaisseau_radar);
        parse_response(buffer, planets, &nb_planets, spaceships, &nb_spaceships, &base);
        release_mutex(mutex_vaisseau_radar);
        angle = get_angle(base.x, base.y, 10000, 10000);
        send_move_command(6, angle, MAX_EXPLORERS_SPEED);
    }
}

void* thread_explorers_2(void* argument)
{
    char buffer[MAX_RESPONSE_SIZE];
    uint16_t angle = 0;
    Spaceship_t* my_spaceship = find_spaceship(0, 7, spaceships, nb_spaceships);
    while (1) {
        send_radar_command(7, buffer);
        get_mutex(mutex_vaisseau_radar);
        parse_response(buffer, planets, &nb_planets, spaceships, &nb_spaceships, &base);
        release_mutex(mutex_vaisseau_radar);
        angle = get_angle(base.x, base.y, 15000, 15000);
        send_move_command(7, angle, MAX_EXPLORERS_SPEED);
    }
}

void* thread_collectors_1(void* argument)
{
    uint16_t angle = 0;
    Planet_t* target_planet1 = NULL;
    Spaceship_t* my_spaceship = find_spaceship(0, 8, spaceships, nb_spaceships);
    while (1) {
        find_nearest_planet(my_spaceship, planets, nb_planets, target_planet1);
        angle = get_angle(my_spaceship->x, my_spaceship->y, target_planet1->x, target_planet1->y);
        send_move_command(8, angle, MAX_COLLECTORS_SPEED);
    }
}

void* thread_collectors_2(void* argument)
{
    uint16_t angle = 0;
    Planet_t* target_planet2 = NULL;
    Spaceship_t* my_spaceship = find_spaceship(0, 9, spaceships, nb_spaceships);
    while (1) {
        find_nearest_planet(my_spaceship, planets, nb_planets, target_planet2);
        angle = get_angle(my_spaceship->x, my_spaceship->y, target_planet2->x, target_planet2->y);
        send_move_command(9, angle, MAX_COLLECTORS_SPEED);
    }
}
