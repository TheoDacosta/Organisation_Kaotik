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

uint16_t get_target_angle(Spaceship_t attacker, Spaceship_t* spaceships, uint16_t nb_spaceships);

void find_nearest_planet(Spaceship_t* spaceship, Planet_t* planets, uint16_t nb_planets, Planet_t* nearest_planet);

uint16_t get_angle_to_follow(Spaceship_t follower, Spaceship_t target, int16_t offset_x, int16_t offset_y);
#endif // TRAJECTORY_H
