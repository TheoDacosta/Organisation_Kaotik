#include "strategy.h"
#include "commands.h"
#include "trajectory.h"

void manage_spaceship_radar(Spaceship_t* space, Spaceship_t* space_ref, Base_t* base, char* command)
{
    uint16_t angle = 0;
    if (space->broken) {
        angle = get_angle(space->x, space->y, base->x, base->y);
        create_move_command(space->ship_id, angle, MAX_EXPLORERS_SPEED, command);
    } else {
        angle = get_angle(space->x, space->y, space_ref->x, space_ref->y);
        create_move_command(space->ship_id, angle, MAX_EXPLORERS_SPEED, command);
    }
}

void manage_spaceship_collector(Spaceship_t* space, Spaceship_t* space_ref, Base_t* base, char* command)
{
    // Planet_t* planet = find_nearest_planet(&space, NB_MAX_PLANETS);

    if (space->broken) {
        uint16_t angle = get_angle(space->x, space->y, base->x, base->y);
        create_move_command(space->ship_id, angle, MAX_COLLECTORS_SPEED, command);
    } else {
        // mettre la planète la plus proche
        // uint16_t angle = get_angle(space->x, space->y, planet->x, planet->y);
        uint8_t angle = 8;
        create_move_command(space->ship_id, angle, MAX_COLLECTORS_SPEED, command);
    }
}
void manage_spaceship_attacker(Spaceship_t* space, Spaceship_t* space_ref, Spaceship_t* space_ships, Base_t* base, char* command)
{
    uint16_t angle_enemi = get_target_angle(*space, space_ships, NB_MAX_SPACESHIPS);
    uint16_t angle = 0;
    if (space->broken) {
        angle = get_angle(space->x, space->y, base->x, base->y);
    } else if (angle_enemi != NOT_FOUND) {
        create_fire_command(space->ship_id, angle_enemi, command);
        return;
    } else {
        angle = get_angle(space->x, space->y, space_ref->x, space_ref->y);
    }
    create_move_command(space->ship_id, angle, MAX_ATTACKERS_SPEED, command);
}
