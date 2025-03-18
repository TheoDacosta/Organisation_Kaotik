#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include "base.h"
#include "parsing.h"
#include "planet.h"
#include "spaceship.h"

#include <math.h>
#include <stdint.h>

#define AREA_LENGTH 20000
#define NOT_FOUND 404
#define FIRE_RANGE 5000
#define MAX_ANGLE 360

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

uint16_t get_angle(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y);

uint16_t get_distance(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

void determine_target_planets(Spaceship_t collector1, Spaceship_t collector2,
    Planet_t* planets, uint16_t nb_planets, Planet_t* target_planet1, Planet_t* target_planet2);

uint16_t get_target_angle(const Spaceship_t* const attacker, const Spaceship_t* const spaceships, uint16_t nb_spaceships);

Planet_t* find_nearest_planet(const Spaceship_t* const spaceship, Planet_t* planets, uint16_t nb_planets);

uint16_t get_angle_to_follow(const Spaceship_t* const follower, const Spaceship_t* const target, int16_t offset_x, int16_t offset_y);
#endif // TRAJECTORY_H
