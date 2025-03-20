#ifndef PLANET_H
#define PLANET_H

#include "point.h"
#include <stdint.h>

#define NB_MAX_PLANETS 8
#define DEFAULT_PLANET (Planet_t) { .planet_id = 0, .position = { 0, 0 }, .ship_id = -1, .saved = 0, .focus = 0 }
typedef struct {
    uint16_t planet_id;
    Point_t position;
    int8_t ship_id;
    uint8_t saved;
    int8_t focus;
} Planet_t;

extern Planet_t planets[NB_MAX_PLANETS];
extern uint16_t nb_planets;

void init_planets(Planet_t planets[]);
void parse_planet(char* data, Planet_t* planets, uint16_t* nb_planets);

Planet_t* find_planet(uint16_t planet_id);

#endif // PLANET_H
