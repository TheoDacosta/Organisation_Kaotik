#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "point.h"
#include <stdint.h>

#define NB_MAX_SPACESHIPS 36
#define DEFAULT_SPACESHIP (Spaceship_t) { .team_id = 0, .ship_id = -1, .position = { 0, 0 }, .broken = 0, .last_shoot_time = 0, .last_radar_time = 0 }

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

void init_spaceships(Spaceship_t spaceships[]);
void parse_spaceship(char* data, Spaceship_t* spaceships, uint16_t* nb_spaceships);

Spaceship_t* find_spaceship(uint8_t team_id, int8_t ship_id);

void shoot(Spaceship_t* spaceship, char* command);
uint8_t can_shoot(Spaceship_t* spaceship);
void scan(Spaceship_t* spaceship, char* command);
uint8_t can_scan(Spaceship_t* spaceship);
#endif // SPACESHIP_H
