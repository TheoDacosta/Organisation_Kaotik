#ifndef PLANET_H
#define PLANET_H

#include <stdint.h>

#define NB_MAX_PLANETS 8
typedef struct {
    uint16_t planet_id;
    uint16_t x;
    uint16_t y;
    int8_t ship_id;
    uint8_t saved;
    int8_t focus;
} Planet_t;

void parse_planet(char* data, Planet_t* planet, uint16_t* nb_planets);

Planet_t* find_planet(uint16_t planet_id, Planet_t* planet, uint16_t nb_planets);

#endif // PLANET_H
