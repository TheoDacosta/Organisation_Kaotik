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
#include "strategy.h"
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
    const Spaceship_t* const my_spaceship;
    const Spaceship_t* const target_spaceship;
    const int16_t offset_x;
    const int16_t offset_y;
} ThreadArgs_t;

uint8_t is_start()
{
    if (response[0] == 'S' && (response[1]) == 'T' && (response[2]) == 'A' && (response[3]) == 'R' && (response[4]) == 'T') {
        return 1;
    }
    return 0;
}

int main(void)
{
    char command[MAX_COMMAND_SIZE];

    hardware_init();
    os_initialisation();
    serial_mutex = create_mutex();
    response_mutex = create_mutex();
    parsing_mutex = create_mutex();
    // Attendre start avant de commencer
    // Pas de gestion de mutexes car les threads ne sont pas encore lancés
    while (gets(response) == NULL || !is_start())
        ;

    // Premier scan radar pour initialiser les données
    send_command("RADAR 6\n");
    gets(response);
    parse_response(planets, &nb_planets, spaceships, &nb_spaceships, &base);

    Spaceship_t* collector_1_spaceship = find_spaceship(0, 8, spaceships, nb_spaceships);
    Spaceship_t* collector_2_spaceship = find_spaceship(0, 9, spaceships, nb_spaceships);
    ThreadArgs_t attacker1_args = { find_spaceship(0, 1, spaceships, nb_spaceships), collector_1_spaceship, -100, 100 };
    ThreadArgs_t attacker2_args = { find_spaceship(0, 2, spaceships, nb_spaceships), collector_1_spaceship, 100, 100 };
    ThreadArgs_t attacker3_args = { find_spaceship(0, 3, spaceships, nb_spaceships), collector_1_spaceship, 0, -100 };
    ThreadArgs_t attacker4_args = { find_spaceship(0, 4, spaceships, nb_spaceships), collector_2_spaceship, -100, -100 };
    ThreadArgs_t attacker5_args = { find_spaceship(0, 5, spaceships, nb_spaceships), collector_2_spaceship, 100, 100 };
    ThreadArgs_t explorer1_args = { find_spaceship(0, 6, spaceships, nb_spaceships), collector_1_spaceship, 0, 0 };
    ThreadArgs_t explorer2_args = { find_spaceship(0, 7, spaceships, nb_spaceships), collector_2_spaceship, 0, 0 };
    ThreadArgs_t collector1_args = { collector_1_spaceship, NULL, 0, 0 };
    ThreadArgs_t collector2_args = { collector_2_spaceship, NULL, 0, 0 };

    create_thread(attacker_thread, &attacker1_args);
    // create_thread(attacker_thread, &attacker2_args);
    // create_thread(attacker_thread, &attacker3_args);
    // create_thread(attacker_thread, &attacker4_args);
    // create_thread(attacker_thread, &attacker5_args);
    // create_thread(explorer_thread, &explorer1_args);
    // create_thread(explorer_thread, &explorer2_args);
    // create_thread(collector_thread, &collector1_args);
    // create_thread(collector_thread, &collector2_args);
    os_start();
    while (1) {
    }
}

void* attacker_thread(void* argument)
{
    const ThreadArgs_t* args = (const ThreadArgs_t*)argument;
    char command[MAX_COMMAND_SIZE] = "MOVE 6 6 6\n";
    while (1) {
        if (args->my_spaceship->ship_id <= 0 || args->my_spaceship->ship_id > MAX_SHIP_ID) {
            while (1)
                ;
        }
        send_command(command);
    }
}

void* explorer_thread(void* argument)
{
    const ThreadArgs_t* args = (const ThreadArgs_t*)argument;
    char command[MAX_COMMAND_SIZE] = { 0 };
    while (1) {
        manage_spaceship_radar(args->my_spaceship, args->target_spaceship, args->offset_x, args->offset_y, &base, command);
        send_command(command);
    }
}

void* collector_thread(void* argument)
{
    const ThreadArgs_t* args = (const ThreadArgs_t*)argument;
    char command[MAX_COMMAND_SIZE] = { 0 };
    while (1) {
        manage_spaceship_collector(args->my_spaceship, planets, nb_planets, &base, command);
        send_command(command);
    }
}
