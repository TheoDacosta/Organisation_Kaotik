#include "spaceship.h"
#include <stdint.h>

/**
 * @brief Crée et ajoute un vaisseau spatial à la liste des vaisseaux existants.
 *
 * Cette fonction initialise un vaisseau spatial avec les paramètres fournis
 * et l'ajoute à la liste, tout en vérifiant qu'il y a encore de la place.
 *
 * @param team_id      Identifiant de l'équipe du vaisseau.
 * @param ship_id      Identifiant unique du vaisseau.
 * @param x            Position X du vaisseau dans l'espace.
 * @param y            Position Y du vaisseau dans l'espace.
 * @param broken       Indique si le vaisseau est endommagé (1 = oui, 0 = non).
 * @param spaceships   Tableau contenant la liste des vaisseaux.
 * @param nb_spaceships Pointeur sur le nombre actuel de vaisseaux.
 **/
void create_spaceship(uint8_t team_id, int8_t ship_id, uint16_t pos_x, uint16_t pos_y,
    uint8_t broken, Spaceship* spaceships, uint16_t* nb_spaceships)
{

    if (*nb_spaceships >= NB_MAX_SPACESHIPS) {
        return; // Évite un dépassement de tableau
    }

    // Création et assignation des valeurs du vaisseau
    Spaceship* new_spaceship = &spaceships[*nb_spaceships];
    new_spaceship->team_id = team_id;

    new_spaceship->ship_id = ship_id;
    new_spaceship->x = pos_x;

    new_spaceship->y = pos_y;
    new_spaceship->broken = broken;

    // Incrémente le compteur de vaisseaux
    (*nb_spaceships)++;
}
