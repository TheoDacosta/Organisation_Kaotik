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

extern char response[MAX_RESPONSE_SIZE];

void* attacker_thread(void* argument);
void* explorer_thread(void* argument);
void* collector_thread(void* argument);

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

int main(int argc, char* argv[])
{
    char command[MAX_COMMAND_SIZE];

    hardware_init();
    os_initialisation(argc, argv);
    response_mutex = create_mutex();
    // Attendre start avant de commencer
    while (gets(response) == NULL || !is_start(response))
        ;

    init_spaceships(spaceships);
    init_planets(planets);
    create_radar_command(6, command);
    send_command(command, response);
    parse_response(response);

    Spaceship_t* collector_1_spaceship = find_spaceship(0, 8);
    Spaceship_t* collector_2_spaceship = find_spaceship(0, 9);
    ThreadArgs_t attacker1_args = { find_spaceship(0, 1), collector_1_spaceship, -1000, 1000 };
    ThreadArgs_t attacker2_args = { find_spaceship(0, 2), collector_1_spaceship, 1000, 1000 };
    ThreadArgs_t attacker3_args = { find_spaceship(0, 3), collector_1_spaceship, 0, -1000 };
    ThreadArgs_t attacker4_args = { find_spaceship(0, 4), collector_2_spaceship, -1000, -1000 };
    ThreadArgs_t attacker5_args = { find_spaceship(0, 5), collector_2_spaceship, 1000, 1000 };
    ThreadArgs_t explorer1_args = { find_spaceship(0, 6), collector_1_spaceship, 0, 0 };
    ThreadArgs_t explorer2_args = { find_spaceship(0, 7), collector_2_spaceship, 0, 0 };
    ThreadArgs_t collector1_args = { collector_1_spaceship, NULL, 0, 0 };
    ThreadArgs_t collector2_args = { collector_2_spaceship, NULL, 0, 0 };

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
    char command[MAX_COMMAND_SIZE];
    Point_t target;
    while (1) {
        get_point_with_offset(args->target_spaceship->position, args->offset_x, args->offset_y, &target);
        manage_spaceship_attacker(args->my_spaceship, target, command);
        get_mutex(response_mutex);
        send_command(command, response);
        release_mutex(response_mutex);
    }
}

void* explorer_thread(void* argument)
{
    ThreadArgs_t* args = (ThreadArgs_t*)argument;
    char command[MAX_COMMAND_SIZE];
    Point_t target;
    while (1) {
        get_point_with_offset(args->target_spaceship->position, args->offset_x, args->offset_y, &target);
        manage_spaceship_radar(args->my_spaceship, target, command);
        get_mutex(response_mutex);
        send_command(command, response);
        parse_response(response);
        release_mutex(response_mutex);
    }
}

void* collector_thread(void* argument)
{
    ThreadArgs_t* args = (ThreadArgs_t*)argument;
    char command[MAX_COMMAND_SIZE];
    while (1) {
        manage_spaceship_collector(args->my_spaceship, command);
        get_mutex(response_mutex);
        send_command(command, response);
        release_mutex(response_mutex);
    }
}
