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
    Spaceship_t* my_spaceship;
    Spaceship_t* target_spaceship;
    uint16_t offset_x;
    uint16_t offset_y;
} ThreadArgs_t;

uint8_t is_start(char* response)
{
    if (*response == 'S' && *(response + 1) == 'T' && *(response + 2) == 'A' && *(response + 3) == 'R' && *(response + 4) == 'T') {
        return 1;
    }
    return 0;
}

int main(void)
{
    char response[MAX_RESPONSE_SIZE] = { 0 };

    hardware_init();
    os_initialisation();
    serial_mutex = create_mutex();
    // Attendre start avant de commencer
    while (gets(response) == NULL || !is_start(response))
        ;
    ThreadArgs_t attacker1_args = { NULL, NULL, -100, 100 };

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
    ThreadArgs_t* args = (ThreadArgs_t*)argument;
    char command[MAX_COMMAND_SIZE] = { 0 };
    char response[MAX_RESPONSE_SIZE] = { 0 };
    while (1) {
        create_move_command(1, 0, MAX_ATTACKERS_SPEED, command);
        get_mutex(serial_mutex);
        puts(command);
        gets(response);
        release_mutex(serial_mutex);
        if (response[0] != 'O' || response[1] != 'K') {
            while (1)
                ;
        }
    }
}

void* explorer_thread(void* argument)
{
    ThreadArgs_t* args = (ThreadArgs_t*)argument;
    char command[MAX_COMMAND_SIZE];
    char response[MAX_RESPONSE_SIZE];
    while (1) {
        manage_spaceship_radar(args->my_spaceship, args->target_spaceship, args->offset_x, args->offset_y, &base, command);
        send_command(command, response);
    }
}

void* collector_thread(void* argument)
{
    ThreadArgs_t* args = (ThreadArgs_t*)argument;
    char command[MAX_COMMAND_SIZE];
    char response[MAX_RESPONSE_SIZE];
    while (1) {
        manage_spaceship_collector(args->my_spaceship, planets, nb_planets, &base, command);
        send_command(command, response);
    }
}
