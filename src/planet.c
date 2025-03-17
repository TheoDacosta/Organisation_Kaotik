#include "planet.h"
#include <stdlib.h>

Planet_t planets[NB_MAX_PLANETS];
uint16_t nb_planets = 0;

/**
 * @brief Transforme les données reçues en informations sur une planète.
 *
 * @param data        Chaine de caractère contenant les données de la planète.
 * @param planets     Liste des planètes existantes.
 * @param nb_planets  Pointeur vers le nombre total de planètes (sera mis à jour si une nouvelle planète est ajoutée).
 **/
void parse_planet(char* data)
{
    if (data == NULL) {
        while (1)
            ;
    }

    Planet_t* planet = &planets[nb_planets];

    data++; // Ignore le premier caractère (type de données)
    data++; // Ignore l'espace
    planet->planet_id = atoi(data);
    while (*data != ' ')
        data++;
    data++;
    planet->position.x = atoi(data);
    while (*data != ' ')
        data++;
    data++;
    planet->position.y = atoi(data);
    while (*data != ' ')
        data++;
    data++;
    planet->ship_id = atoi(data);
    while (*data != ' ')
        data++;
    data++;
    planet->saved = atoi(data);

    nb_planets++;
}

/**
 * @brief Recherche une planète dans la liste à partir de son identifiant unique.
 *
 * @param planet_id    Identifiant unique de la planète recherchée.
 * @param planets      Tableau contenant toutes les planètes existantes.
 *
 * @return Planet_t*   Pointeur vers la planète trouvée, ou NULL si aucune correspondance.
 **/
Planet_t* find_planet(uint16_t planet_id, Planet_t* planets, uint16_t nb_planets)
{
    for (uint16_t i = 0; i < nb_planets; i++) {
        if (planets[i].planet_id == planet_id)
            return &planets[i];
    }
    return NULL;
}
