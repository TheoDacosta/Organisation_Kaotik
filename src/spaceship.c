#include "spaceship.h"
#include "os_manager.h"
#include <stdint.h>
#include <stdlib.h>

/**
 * @brief Transforme les données reçues en informations sur un vaisseau.
 *
 * @param data       Tableau contenant les informations du vaisseau sous forme de chaîne de caractère.
 * @param spaceships   Liste des vaisseaux existants.
 * @param nb_spaceships Pointeur sur le nombre total de vaisseaux (mis à jour si un nouveau vaisseau est ajouté).
 **/
void parse_spaceship(char* data, Spaceship_t* spaceships, uint16_t* nb_spaceships)
{
    if (data == NULL || spaceships == NULL || nb_spaceships == NULL) {
        while (1)
            ;
    }

    Spaceship_t* new_spaceship = &spaceships[*nb_spaceships];

    data++; // Ignore le premier caractère (type de données)
    data++; // Ignore l'espace
    new_spaceship->team_id = (uint8_t)atoi(data);
    while (*data != ' ')
        data++;
    data++;
    new_spaceship->ship_id = (int8_t)atoi(data);
    while (*data != ' ')
        data++;
    data++;
    new_spaceship->x = (uint16_t)atoi(data);
    while (*data != ' ')
        data++;
    data++;
    new_spaceship->y = (uint16_t)atoi(data);
    while (*data != ' ')
        data++;
    data++;
    new_spaceship->broken = (uint8_t)atoi(data);

    (*nb_spaceships)++;
}

/**
 * @brief Recherche un vaisseau dans la liste des vaisseaux par son ID de team et son ID de vaisseau.
 *
 * @param team_id    L'ID de l'équipe du vaisseau recherché.
 * @param ship_id    L'ID du vaisseau recherché.
 * @param spaceships Liste des vaisseaux existants.
 * @param nb_spaceships Nombre total de vaisseaux.
 *
 * @return Un pointeur vers le vaisseau trouvé, ou NULL si aucun vaisseau n'est trouvé.
 **/
Spaceship_t* find_spaceship(uint8_t team_id, int8_t ship_id, Spaceship_t* spaceships, uint16_t nb_spaceships)
{
    for (uint16_t i = 0; i < nb_spaceships; i++) {
        if (spaceships[i].team_id == team_id && spaceships[i].ship_id == ship_id)
            return &spaceships[i];
    }
    return NULL;
}

/**
 * @brief Calcule le temps écoulé si 1 seconde s'est passée.
 *
 * @param time_ecoule Pointeur vers la variable qui recevra le temps écoulé en ms.
 * @param time_start Temps de départ en ms.
 * @param time_actuel Temps actuel en ms.
 *
 * @return Rien.
 **/
void shoot_current_timeMs(uint32_t* time_ecoule, uint32_t time_start, uint32_t time_actuel)
{
    if ((time_actuel - time_start) >= 1000) {
        *time_ecoule = time_actuel - time_start;
    }
    return;
}
