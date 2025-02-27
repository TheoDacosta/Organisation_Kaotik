#ifndef STRATEGY_H
#define STRATEGY_H

#include "base.h"
#include "os_manager.h"
#include "planet.h"
#include "spaceship.h"
#include <stdint.h>

uint8_t return_to_base(Spaceship_t* spaceship, Base_t* base, uint16_t speed, char* command);
void manage_spaceship_radar(Spaceship_t* my_spaceship, Spaceship_t* target_spaceship, uint16_t offset_x, uint16_t offset_y, Base_t* base, char* command);
void manage_spaceship_collector(Spaceship_t* my_spaceship, Planet_t* planets, uint16_t nb_planets, Base_t* base, char* command);
void manage_spaceship_attacker(Spaceship_t* my_spaceship, Spaceship_t* target_spaceship, uint16_t offset_x, uint16_t offset_y, Spaceship_t* spaceships, uint16_t nb_spaceships, Base_t* base, char* command);

#endif // __STRATEGY_H__
