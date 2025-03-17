#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <stdint.h>

#define NB_MAX_SPACESHIPS 36

typedef struct
{
    uint8_t team_id;
    int8_t ship_id;
    uint16_t x;
    uint16_t y;
    uint8_t broken; // 0 ou 1
} Spaceship_t;

extern Spaceship_t spaceships[NB_MAX_SPACESHIPS];
extern uint16_t nb_spaceships;

void parse_spaceship(char* data, Spaceship_t* spaceships, uint16_t* nb_spaceships);

Spaceship_t* find_spaceship(uint8_t team_id, int8_t ship_id, Spaceship_t* spaceships, uint16_t nb_spaceships);

//
void shoot_current_timeMs(uint32_t* time_ecoule, uint32_t time_start, uint32_t time_actuel);
#endif // SPACESHIP_H
