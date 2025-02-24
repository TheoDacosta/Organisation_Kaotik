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

// Ajoute ou met à jour un vaisseau à partir des données reçues.
void parse_spaceship(char** params, Spaceship* spaceships, uint16_t* nb_spaceships);

// Ajoute un vaisseau à la liste des vaisseaux
void create_spaceship(uint8_t team_id, int8_t ship_id, uint16_t pos_x, uint16_t pos_y,
    uint8_t broken, Spaceship* spaceships, uint16_t* nb_spaceships);

// Recherche un vaisseau par ID d'équipe et ID de vaisseau
Spaceship* find_spaceship_by_id(uint8_t team_id, int8_t ship_id, Spaceship* spaceships);

// Met à jour la position et l'état d'un vaisseau existant
void set_spaceship(uint8_t team_id, int8_t ship_id, uint16_t pos_x, uint16_t pos_y,
    uint8_t broken, Spaceship* spaceships);

// Réinitialise tous les vaisseaux et remet le compteur à zéro
void delete_all_spaceships(Spaceship* spaceships, uint16_t* nb_spaceships);

#endif // SPACESHIP_H
