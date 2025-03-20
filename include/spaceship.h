#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "point.h"
#include <stdint.h>

#define NB_MAX_SPACESHIPS 36

typedef struct
{
    uint8_t team_id;
    int8_t ship_id;
    Point_t position;
    uint8_t broken; // 0 ou 1
    uint32_t last_shoot_time;
    uint32_t last_radar_time;
} Spaceship_t;

extern Spaceship_t spaceships[NB_MAX_SPACESHIPS];
extern uint16_t nb_spaceships;

void parse_spaceship(char* data);

Spaceship_t* find_spaceship(uint8_t team_id, int8_t ship_id, Spaceship_t* spaceships, uint16_t nb_spaceships);

// Gère le tir du vaisseau en fonction du temps écoulé.
void shoot(Spaceship_t* my_spaceship, char* commande);

uint8_t can_shoot(Spaceship_t* my_spaceship);

uint8_t can_scan(Spaceship_t* my_spaceship);
#endif // SPACESHIP_H
