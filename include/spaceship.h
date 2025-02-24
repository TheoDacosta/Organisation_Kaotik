#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <stdint.h>

#define NB_MAX_SPACESHIPS 36

typedef struct {
    uint8_t team_id;
    int8_t ship_id;
    uint16_t x;
    uint16_t y;
    uint8_t broken; // 0 ou 1
} Spaceship_t;

// Ajoute ou met à jour un vaisseau à partir des données reçues.
void parse_spaceship(char* data, Spaceship_t* spaceships, uint16_t* nb_spaceships);

// Recherche un vaisseau par ID d'équipe et ID de vaisseau
Spaceship_t* find_spaceship(uint8_t team_id, int8_t ship_id, Spaceship_t* spaceships);

#endif // SPACESHIP_H
