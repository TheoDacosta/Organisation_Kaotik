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
void parse_spaceship(char* data, Spaceship_t* spaceships, uint16_t* nb_spaceships)
{
    if (data == NULL) {
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
    new_spaceship->position.x = (uint16_t)atoi(data);
    while (*data != ' ')
        data++;
    data++;
    new_spaceship->position.y = (uint16_t)atoi(data);
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
 *
 * @return Un pointeur vers le vaisseau trouvé, ou NULL si aucun vaisseau n'est trouvé.
 **/
Spaceship_t* find_spaceship(uint8_t team_id, int8_t ship_id)
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
 * @param spaceship Le vaisseau qui doit tirer.
 * @param command   La commande à envoyer.
 **/
void shoot(Spaceship_t* spaceship, char* command)
{
    uint16_t angle_to_enemy = get_target_angle(spaceship);
    create_fire_command(spaceship->ship_id, angle_to_enemy, command);
    spaceship->last_shoot_time = get_current_timeMs();
}

/**
 * @brief
 *
 * @param spaceship Le vaisseau qui doit tirer.
 * @return Si le vaisseau peut tirer.
 */
uint8_t can_shoot(Spaceship_t* spaceship)
{
    return ((get_current_timeMs() - spaceship->last_shoot_time) > SHOOT_COOLDOWN);
}

/**
 * @brief
 *
 * @param spaceship Le vaisseau qui doit scanner.
 * @param command   La commande à envoyer.
 */
void scan(Spaceship_t* spaceship, char* command)
{
    create_radar_command(spaceship->ship_id, command);
    spaceship->last_radar_time = get_current_timeMs();
}

/**
 * @brief
 *
 * @param spaceship Le vaisseau qui doit scanner.
 * @return Si le vaisseau peut scanner.
 */
uint8_t can_scan(Spaceship_t* spaceship)
{
    return ((get_current_timeMs() - spaceship->last_radar_time) > SCAN_COOLDOWN);
}

/**
 * @brief Initialise un tableau de vaisseaux avec des valeurs par défaut.
 *
 * Cette fonction parcourt un tableau de vaisseaux et initialise chaque élément
 * avec une valeur par défaut définie par la constante DEFAULT_SPACESHIP.
 *
 * @param spaceships Tableau de vaisseaux à initialiser.
 */
void init_spaceships(Spaceship_t spaceships[])
{
    for (int i = 0; i < NB_MAX_SPACESHIPS; i++) {
        spaceships[i] = DEFAULT_SPACESHIP;
    }
}
