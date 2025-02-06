#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <stdint.h>

#define NB_MAX_SPACESHIPS 36

typedef struct spaceship {
    uint8_t team_id;
    int8_t ship_id;
    uint16_t x;
    uint16_t y;
    uint8_t broken; // 0 ou 1
} Spaceship;

#endif // SPACESHIP_H
