#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include "base.h"
#include "planet.h"
#include "spaceship.h"
#include "parsing.h"

#include <math.h>
#include <stdint.h>

#define AREA_LENGTH 20000
#define NOT_FOUND 404
#define FIRE_RANGE 5000

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

/** Calcule l'angle de déplacement (0-359°) entre deux points. */
uint16_t get_angle(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y);

// Calcule la distance entre deux points.
uint16_t get_distance(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

// Assigne aux collecteurs les planètes les plus proches non encore ciblées.
void determine_target_planets(Spaceship_t collector1, Spaceship_t collector2,
    Planet_t* planets, uint8_t nb_planets, Planet_t* target_planet1, Planet_t* target_planet2);

// Récupère l'angle de tir du vaisseau attaquant vers la cible la plus proche
uint16_t get_target_angle(Spaceship_t attacker, Spaceship_t* spaceships);

// Fonction qui permet de suivre un vaisseau allier
uint16_t deplace_space_from_an_other(uint8_t id, uint8_t id2, Spaceship_t* spaceships, Base_t* base);

void find_nearest_planet(Spaceship_t* spaceship, Planet_t* planets, Planet_t** nearest_planet);
#endif // TRAJECTORY_H
