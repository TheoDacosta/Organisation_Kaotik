#ifndef PLANET_H
#define PLANET_H

#include <stdint.h>

#define NB_MAX_PLANETS 8
typedef struct Planet_t {
    uint16_t planet_id;
    uint16_t x;
    uint16_t y;
    int8_t ship_id;
    uint8_t saved;
    int8_t focus;
} Planet;

#endif // PLANET_H
