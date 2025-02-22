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

/**
 *  Analyse les données et les stocke dans la liste des planètes.
 *  Si la planète existe déjà, elle est mise à jour, sinon elle est ajoutée.
 * */
void parse_planet(char** data, Planet* planet, uint16_t* nb_planets);

// Recherche une planète dans la liste en utilisant son identifiant.
Planet* find_planet(uint16_t planet_id, Planet* planet);

// Crée une nouvelle planète avec les données fournies et l'ajoute à la liste des planètes.
void create_planet(uint16_t planet_id, uint16_t pos_x, uint16_t pos_y, int8_t ship_id,
    uint8_t is_saved, Planet* planet, uint16_t* nb_planets);

// Réinitialise toutes les planètes et remet le compteur à zéro.
void delete_all_planets(Planet* planet, uint16_t* nb_planets);

#endif // PLANET_H
