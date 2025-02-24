#include "spaceship.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Ajoute ou met à jour un vaisseau à partir des données reçues.
 *
 * Extrait les informations d'un vaisseau à partir d'un tableau de chaînes de caractères.
 * Si le vaisseau existe déjà, il est mis à jour. Sinon, il est créé et ajouté à la liste.
 *
 * @param params       Tableau contenant les informations du vaisseau sous forme de chaînes de caractères.
 *                     Format attendu : ["", team_id, ship_id, x, y, broken]
 * @param spaceships   Liste des vaisseaux existants.
 * @param nb_spaceships Pointeur sur le nombre total de vaisseaux (mis à jour si un nouveau vaisseau est ajouté).
 **/
void parse_spaceship(char** params, Spaceship* spaceships, uint16_t* nb_spaceships)
{
    if (params == NULL || spaceships == NULL || nb_spaceships == NULL) {
        return; // Vérification pour éviter les erreurs
    }

    // Extraction et conversion des données du vaisseau
    uint8_t team_id = (uint8_t)atoi(params[1]);
    int8_t ship_id = (int8_t)atoi(params[2]);
    uint16_t pos_x = (uint16_t)atoi(params[3]);
    uint16_t pos_y = (uint16_t)atoi(params[4]);
    uint8_t broken = (uint8_t)atoi(params[5]);

    // Recherche du vaisseau existant
    Spaceship* spaceship = find_spaceship_by_id(team_id, ship_id, spaceships);

    if (spaceship == NULL) {
        // Création du vaisseau s'il n'existe pas
        create_spaceship(team_id, ship_id, pos_x, pos_y, broken, spaceships, nb_spaceships);
    } else {
        // Mise à jour des attributs du vaisseau existant
        spaceship->x = pos_x;
        spaceship->y = pos_y;
        spaceship->broken = broken;
    }
}

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
 * @brief Met à jour les informations d'un vaisseau existant.
 *
 * Cette fonction recherche un vaisseau spécifique à l'aide de son team_id et ship_id.
 * Si le vaisseau est trouvé, elle met à jour ses coordonnées (x, y) et son état (broken).
 * Si le vaisseau n'existe pas, la fonction ne fait rien.
 *
 * @param team_id    Identifiant de l'équipe du vaisseau.
 * @param ship_id    Identifiant unique du vaisseau au sein de l'équipe.
 * @param pos_x          Nouvelle coordonnée X du vaisseau.
 * @param pos_y          Nouvelle coordonnée Y du vaisseau.
 * @param broken     Indicateur de l'état du vaisseau (cassé ou non).
 * @param spaceships Liste des vaisseaux disponibles.
 */
void set_spaceship(uint8_t team_id, int8_t ship_id, uint16_t pos_x, uint16_t pos_y,
    uint8_t broken, Spaceship* spaceships)
{
    // Recherche du vaisseau à mettre à jour
    Spaceship* spaceship = find_spaceship_by_id(team_id, ship_id, spaceships);

    // Si le vaisseau n'existe pas, on ne fait rien
    if (spaceship == NULL) {
        return;
    }

    // Mise à jour des informations du vaisseau
    spaceship->x = pos_x;
    spaceship->y = pos_y;
    spaceship->broken = broken;
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
