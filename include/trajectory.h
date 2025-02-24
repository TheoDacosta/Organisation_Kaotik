#ifndef FONCTION_H
#define FONCTION_H

#include "planet.h"
#include "spaceship.h"

#include <math.h>
#include <stdint.h>

#define AREA_LENGTH 20000

#ifndef M_PI

#define M_PI (3.14159265358979323846)

#endif

/** Calcule l'angle de déplacement (0-359°) entre deux points. */
uint16_t get_travel_angle(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y);

// Calcule la distance entre deux points.
float calculate_distance(float x1, float y1, float x2, float y2);

// Assigne aux collecteurs les planètes les plus proches non encore ciblées.
void determine_target_planets(Spaceship_t collector1, Spaceship_t collector2,
    Planet_t* planets, uint8_t nb_planets, uint16_t results[2][2]);

#endif // FONCTION
