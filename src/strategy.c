#include "strategy.h"
#include "commands.h"
#include "trajectory.h"

void return_to_base(Spaceship_t* spaceship, uint16_t speed, char* command)
{

    uint16_t angle = get_angle(spaceship->position, base);
    create_move_command(spaceship->ship_id, angle, speed, command);
}

void manage_spaceship_radar(Spaceship_t* my_spaceship, Point_t target, char* command)
{
    if (my_spaceship->broken) {
        return_to_base(my_spaceship, MAX_EXPLORERS_SPEED, command);
        return;
    }
    if (can_scan(my_spaceship)) {
        scan(my_spaceship, command);
        return;
    }
    uint16_t angle = get_angle(my_spaceship->position, target);
    create_move_command(my_spaceship->ship_id, angle, MAX_EXPLORERS_SPEED, command);
}

void manage_spaceship_collector(Spaceship_t* my_spaceship, char* command)
{
    uint16_t angle;
    Planet_t* nearest_planet = find_nearest_planet(my_spaceship, planets, nb_planets);
    if (my_spaceship->broken || nearest_planet == NULL || (my_spaceship->planet_id != 0)) {
        return_to_base(my_spaceship, MAX_COLLECTORS_SPEED, command);
        return;
    } else {
        angle = get_angle(my_spaceship->position, nearest_planet->position);
    }

    create_move_command(my_spaceship->ship_id, angle, MAX_COLLECTORS_SPEED, command);
}
void manage_spaceship_attacker(Spaceship_t* my_spaceship, Point_t target, char* command)
{
    if (my_spaceship->broken) {
        return_to_base(my_spaceship, MAX_ATTACKERS_SPEED, command);
        return;
    }
    uint16_t angle_to_enemy = get_target_angle(my_spaceship);
    if (angle_to_enemy != NOT_FOUND) {
        shoot(my_spaceship, command);
        return;
    }
    uint16_t angle = get_angle(my_spaceship->position, target);
    create_move_command(my_spaceship->ship_id, angle, MAX_ATTACKERS_SPEED, command);
}
