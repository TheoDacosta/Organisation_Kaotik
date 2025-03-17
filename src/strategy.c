#include "strategy.h"
#include "commands.h"
#include "trajectory.h"

uint8_t return_to_base(Spaceship_t* spaceship, uint16_t speed, char* command)
{
    if (spaceship->broken) {
        uint16_t angle = get_angle(spaceship->x, spaceship->y, base.x, base.y);
        create_move_command(spaceship->ship_id, angle, speed, command);
    }
    return spaceship->broken;
}

void manage_spaceship_radar(Spaceship_t* my_spaceship, Spaceship_t* target_spaceship, uint16_t offset_x, uint16_t offset_y, Base_t* base, char* command)
{
    if (return_to_base(my_spaceship, MAX_EXPLORERS_SPEED, command))
        return;
    uint16_t angle = get_angle_to_follow(my_spaceship, target_spaceship, offset_x, offset_y);
    create_move_command(my_spaceship->ship_id, angle, MAX_EXPLORERS_SPEED, command);
}

void manage_spaceship_collector(Spaceship_t* my_spaceship, char* command)
{
    if (return_to_base(my_spaceship, MAX_COLLECTORS_SPEED, command))
        return;
    uint16_t angle;
    Planet_t* nearest_planet = find_nearest_planet(my_spaceship, planets, nb_planets);
    if (nearest_planet == NULL)
        angle = 0;
    else
        angle = get_angle(my_spaceship->x, my_spaceship->y, nearest_planet->x, nearest_planet->y);
    create_move_command(my_spaceship->ship_id, angle, MAX_COLLECTORS_SPEED, command);
}
void manage_spaceship_attacker(Spaceship_t* my_spaceship, Spaceship_t* target_spaceship, uint16_t offset_x, uint16_t offset_y, Spaceship_t* spaceships, uint16_t nb_spaceships, Base_t* base, char* command)
{
    if (return_to_base(my_spaceship, MAX_ATTACKERS_SPEED, command))
        return;
    uint16_t angle_to_enemy = get_target_angle(my_spaceship, spaceships, nb_spaceships);
    if (angle_to_enemy != NOT_FOUND) {
        create_fire_command(my_spaceship->ship_id, angle_to_enemy, command);
        return;
    }
    uint16_t angle = get_angle_to_follow(my_spaceship, target_spaceship, offset_x, offset_y);
    create_move_command(my_spaceship->ship_id, angle, MAX_ATTACKERS_SPEED, command);
}
