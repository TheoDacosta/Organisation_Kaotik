#include "planet.h"
#include <stdlib.h>

/**
 * @brief Transforme les données reçues en informations sur une planète.
 *
 * @param data    Chaine de caractère contenant les données de la planète.
 * @param planets Liste des planètes existantes.
 * @param nb_planets  Pointeur vers le nombre total de planètes (sera mis à jour si une nouvelle planète est ajoutée).
 **/
void parse_planet(char* data, Planet_t* planets, uint16_t* nb_planets)
{
    if (data == NULL || planets == NULL || nb_planets == NULL) {
        return; // Eviter les erreurs
    }

    Planet_t* planet = &planets[*nb_planets];

    data++; // Ignore le premier caractère (type de données)
    data++; // Ignore l'espace
    planet->planet_id = atoi(data);
    while (*data != ' ')
        data++;
    data++;
    planet->x = atoi(data);
    while (*data != ' ')
        data++;
    data++;
    planet->y = atoi(data);
    while (*data != ' ')
        data++;
    data++;
    planet->ship_id = atoi(data);
    while (*data != ' ')
        data++;
    data++;
    planet->saved = atoi(data);

    (*nb_planets)++;
}

/**
 * @brief Recherche une planète dans la liste à partir de son identifiant unique.
 *
 * @param planet_id    Identifiant unique de la planète recherchée.
 * @param planet  Tableau contenant toutes les planètes existantes.
 *
 * @return Planet_t*     Pointeur vers la planète trouvée, ou NULL si aucune correspondance.
 **/
Planet_t* find_planet(uint16_t planet_id, Planet_t* planet)
{
    // Parcourt chaque planète dans la liste
    for (Planet_t* current_planet = planet; current_planet < planet + NB_MAX_PLANETS; current_planet++) {
        // Vérifie si l'identifiant de la planète correspond à celui recherché
        if (current_planet->planet_id == planet_id) {
            return current_planet; // Retourne un pointeur vers la planète trouvée
        }
    }
    return NULL; // Retourne NULL si aucune planète ne correspond à l'ID
}
