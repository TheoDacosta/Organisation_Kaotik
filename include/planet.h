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

/**
 *  Analyse les données et les stocke dans la liste des planètes.
 *  Si la planète existe déjà, elle est mise à jour, sinon elle est ajoutée.
 * */
void parse_planet(char* data, Planet_t* planet, uint16_t* nb_planets);

// Recherche une planète dans la liste en utilisant son identifiant.
Planet_t* find_planet(uint16_t planet_id, Planet_t* planet);

#endif // PLANET_H
