#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include "base.h"
#include "parsing.h"
#include "planet.h"
#include "point.h"
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

uint16_t get_angle(Point_t start_point, Point_t end_point);

uint16_t get_distance(Point_t point1, Point_t point2);

void determine_target_planets(Spaceship_t collector1, Spaceship_t collector2,
    Planet_t* planets, uint16_t nb_planets, Planet_t* target_planet1, Planet_t* target_planet2);

uint16_t get_target_angle(Spaceship_t* attacker);

Planet_t* find_nearest_planet(Spaceship_t* spaceship, Planet_t* planets, uint16_t nb_planets);

void get_point_with_offset(Point_t point, int16_t offset_x, int16_t offset_y, Point_t* point_with_offset);
#endif // TRAJECTORY_H
