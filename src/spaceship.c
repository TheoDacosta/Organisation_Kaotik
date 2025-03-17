#include "spaceship.h"
#include "commands.h"
#include "os_manager.h"
#include "trajectory.h"
#include <stdint.h>
#include <stdlib.h>

Spaceship_t spaceships[NB_MAX_SPACESHIPS];
uint16_t nb_spaceships = 0;

/**
 * @brief Transforme les données reçues en informations sur un vaisseau.
 *
 * @param data       Tableau contenant les informations du vaisseau sous forme de chaîne de caractère.
 * @param spaceships   Liste des vaisseaux existants.
 * @param nb_spaceships Pointeur sur le nombre total de vaisseaux (mis à jour si un nouveau vaisseau est ajouté).
 **/
void parse_spaceship(char* data)
{
    if (data == NULL) {
        while (1)
            ;
    }

    Spaceship_t* new_spaceship = &spaceships[nb_spaceships];

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
    new_spaceship->position.x = (uint16_t)atoi(data);
    while (*data != ' ')
        data++;
    data++;
    new_spaceship->position.y = (uint16_t)atoi(data);
    while (*data != ' ')
        data++;
    data++;
    new_spaceship->broken = (uint8_t)atoi(data);

    nb_spaceships++;
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
 * @param elapsed_time Pointeur vers la variable qui recevra le temps écoulé en ms.
 * @param time_start Temps de départ en ms.
 * @param time_actuel Temps actuel en ms.
 *
 * @return Rien.
 **/
void shoot_current_timeMs(uint32_t* elapsed_time, uint32_t start_time, uint32_t current_time, Spaceship_t* my_spaceship, Spaceship_t* spaceships, uint16_t nb_spaceships, char* commande)
{
    if ((current_time - start_time) >= 1000) {
        uint16_t angle_to_enemy = get_target_angle(my_spaceship, spaceships, nb_spaceships);
        create_fire_command(my_spaceship->ship_id, angle_to_enemy, commande);

        *elapsed_time = current_time - start_time;
    }
    return;
}
