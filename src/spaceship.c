#include "spaceship.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Crée et ajoute un vaisseau spatial à la liste des vaisseaux existants.
 *
 * Cette fonction initialise un vaisseau spatial avec les paramètres fournis
 * et l'ajoute à la liste, tout en vérifiant qu'il y a encore de la place.
 *
 * @param team_id      Identifiant de l'équipe du vaisseau.
 * @param ship_id      Identifiant unique du vaisseau.
 * @param pos_x            Position X du vaisseau dans l'espace.
 * @param pos_y            Position Y du vaisseau dans l'espace.
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

/**
 * @brief Recherche un vaisseau dans la liste des vaisseaux par son ID de team et son ID de vaisseau.
 *
 * Cette fonction parcourt la liste des vaisseaux pour trouver celui qui correspond
 * à l'ID de l'équipe et l'ID du vaisseau fournis. Si un vaisseau correspondant est trouvé,
 * elle retourne un pointeur vers ce vaisseau. Sinon, elle retourne NULL.
 *
 * @param team_id    L'ID de l'équipe du vaisseau recherché.
 * @param ship_id    L'ID du vaisseau recherché.
 * @param spaceships Liste des vaisseaux existants.
 *
 * @return Un pointeur vers le vaisseau trouvé, ou NULL si aucun vaisseau n'est trouvé.
 **/
Spaceship* find_spaceship_by_id(uint8_t team_id, int8_t ship_id, Spaceship* spaceships)
{
    for (uint16_t i = 0; i < NB_MAX_SPACESHIPS; i++) {
        // Vérifie si l'ID de l'équipe et l'ID du vaisseau correspondent
        if (spaceships[i].team_id == team_id && spaceships[i].ship_id == ship_id) {
            return &spaceships[i];
        }
    }

    return NULL; // Si aucun vaisseau correspondant n'est trouvé, retourne NULL
}

/**
 * @brief Réinitialise la liste des vaisseaux spatiaux.
 *
 * Cette fonction remet à zéro tous les vaisseaux du tableau et
 * réinitialise le compteur du nombre de vaisseaux.
 *
 * @param spaceships   Tableau des vaisseaux à réinitialiser.
 * @param nb_spaceships Pointeur vers le nombre total de vaisseaux.
 **/
void delete_all_spaceships(Spaceship* spaceships, uint16_t* nb_spaceships)
{
    if (spaceships == NULL || nb_spaceships == NULL) {
        return; // Eviter les erreurs de pointeur NULL
    }

    // Réinitialisation des données de chaque vaisseau
    for (uint16_t i = 0; i < *nb_spaceships; i++) {
        spaceships[i].team_id = 0;
        spaceships[i].ship_id = -1;

        spaceships[i].x = 0;
        spaceships[i].y = 0;
        spaceships[i].broken = 0;
    }

    // Réinitialisation du compteur
    *nb_spaceships = 0;
}
