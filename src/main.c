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
#include "strategie.h"
#include "trajectory.h"

void* attacker_thread(void* argument);
void* explorer_thread(void* argument);
void* collector_thread(void* argument);

Planet_t planets[NB_MAX_PLANETS];
uint16_t nb_planets = 0;
Spaceship_t spaceships[NB_MAX_SPACESHIPS];
uint16_t nb_spaceships = 0;
Base_t base;

typedef struct {
    Spaceship_t* my_spaceship;
    Spaceship_t* target_spaceship;
    uint16_t offset_x;
    uint16_t offset_y;
} ThreadArgs_t;

int main(void)
{
    char buffer[MAX_RESPONSE_SIZE];
    hardware_init();
    os_initialisation();
    serial_mutex = create_mutex();
    parsing_mutex = create_mutex();

    // Premier scan radar pour initialiser les données
    send_radar_command(6, buffer);
    parse_response(buffer, planets, &nb_planets, spaceships, &nb_spaceships, &base);

    ThreadArgs_t attacker1_args = { find_spaceship(0, 1, spaceships, nb_spaceships), find_spaceship(0, 8, spaceships, nb_spaceships), -100, 100 };
    ThreadArgs_t attacker2_args = { find_spaceship(0, 2, spaceships, nb_spaceships), find_spaceship(0, 8, spaceships, nb_spaceships), 100, 100 };
    ThreadArgs_t attacker3_args = { find_spaceship(0, 3, spaceships, nb_spaceships), find_spaceship(0, 8, spaceships, nb_spaceships), 0, -100 };
    ThreadArgs_t attacker4_args = { find_spaceship(0, 4, spaceships, nb_spaceships), find_spaceship(0, 9, spaceships, nb_spaceships), -100, -100 };
    ThreadArgs_t attacker5_args = { find_spaceship(0, 5, spaceships, nb_spaceships), find_spaceship(0, 9, spaceships, nb_spaceships), 100, 100 };
    ThreadArgs_t explorer1_args = { find_spaceship(0, 6, spaceships, nb_spaceships), find_spaceship(0, 8, spaceships, nb_spaceships), 0, 0 };
    ThreadArgs_t explorer2_args = { find_spaceship(0, 7, spaceships, nb_spaceships), find_spaceship(0, 9, spaceships, nb_spaceships), 0, 0 };
    ThreadArgs_t collector1_args = { find_spaceship(0, 8, spaceships, nb_spaceships), NULL, 0, 0 };
    ThreadArgs_t collector2_args = { find_spaceship(0, 9, spaceships, nb_spaceships), NULL, 0, 0 };

    create_thread(attacker_thread, &attacker1_args);
    create_thread(attacker_thread, &attacker2_args);
    create_thread(attacker_thread, &attacker3_args);
    create_thread(attacker_thread, &attacker4_args);
    create_thread(attacker_thread, &attacker5_args);
    create_thread(explorer_thread, &explorer1_args);
    create_thread(explorer_thread, &explorer2_args);
    create_thread(collector_thread, &collector1_args);
    create_thread(collector_thread, &collector2_args);
    os_start();
    while (1) {
    }
}

void* attacker_thread(void* argument)
{
    ThreadArgs_t* args = (ThreadArgs_t*)argument;
    while (1) {
        // Appeler la fonction manage_spaceship_attacker
    }
}

void* explorer_thread(void* argument)
{
    ThreadArgs_t* args = (ThreadArgs_t*)argument;
    while (1) {
        // Appeler la fonction manage_spaceship_radar
    }
}

void* collector_thread(void* argument)
{
    ThreadArgs_t* args = (ThreadArgs_t*)argument;
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
        target_planet1 = find_nearest_planet(my_spaceship, planets, nb_planets);
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
        target_planet2 = find_nearest_planet(my_spaceship, planets, nb_planets);
        angle = get_angle(my_spaceship->x, my_spaceship->y, target_planet2->x, target_planet2->y);
        send_move_command(9, angle, MAX_COLLECTORS_SPEED);
    }
}
