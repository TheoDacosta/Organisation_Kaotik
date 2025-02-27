#include "strategy.h"
#include "commands.h"
#include "trajectory.h"

void manage_spaceship_radar(int8_t ship_id, int8_t ship_id_reference, Spaceship_t* spaceships, Base_t* base, char* command)
{
    uint16_t angle = 0;
    Spaceship_t* space = find_spaceship(0, ship_id, spaceships, NB_MAX_SPACESHIPS);
    if (space->broken) {
        angle = get_angle(space->x, space->y, base->x, base->y);
        create_move_command(ship_id, angle, MAX_EXPLORERS_SPEED, command);
    } else {
        Spaceship_t* space_ref = find_spaceship(0, ship_id_reference, spaceships, NB_MAX_SPACESHIPS);
        angle = get_angle(space->x, space->y, space_ref->x, space_ref->y);
        create_move_command(ship_id, angle, MAX_EXPLORERS_SPEED, command);
    }
}

void manage_spaceship_collector(int8_t ship_id, Spaceship_t* spaceships, Base_t* base, Planet_t* planet, char* command)
{
    Spaceship_t* space = find_spaceship(0, ship_id, spaceships, NB_MAX_SPACESHIPS);
    // Planet_t* planet = find_nearest_planet(&space, NB_MAX_PLANETS);

    if (space->broken) {
        uint16_t angle = get_angle(space->x, space->y, base->x, base->y);
        create_move_command(ship_id, angle, MAX_COLLECTORS_SPEED, command);
    } else {
        // mettre la planète la plus proche
        // uint16_t angle = get_angle(space->x, space->y, planet->x, planet->y);
        uint8_t angle = 8;
        create_move_command(ship_id, angle, MAX_COLLECTORS_SPEED, command);
    }
}
void manage_spaceship_attacker(int8_t ship_id, int8_t ship_ref_id, Spaceship_t* spaceships, Base_t* base, char* command)
{
    Spaceship_t* space = find_spaceship(0, ship_id, spaceships, NB_MAX_SPACESHIPS);
    uint16_t angle_enemi = get_target_angle(*space, spaceships, NB_MAX_SPACESHIPS);
    if (space->broken) {
        uint16_t angle = get_angle(space->x, space->y, base->x, base->y);
        create_move_command(ship_id, angle, MAX_ATTACKERS_SPEED, command);
    } else if (angle_enemi != NOT_FOUND) {
        create_fire_command(ship_id, angle_enemi, command);
    } else {
        Spaceship_t* space_ref = find_spaceship(0, ship_ref_id, spaceships, MAX_ATTACKERS_SPEED);
        uint16_t angle = get_angle(space->x, space->y, space_ref->x, space_ref->y);
        create_move_command(ship_id, angle, MAX_ATTACKERS_SPEED, command);
    }
}
