#include "planet.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Met à jour ou ajoute une planète à partir des données reçues.
 *
 * Cette fonction extrait les informations d'une planète depuis un tableau de chaînes de caractères
 * et met à jour la structure correspondante dans la liste des planètes.
 * Si la planète existe déjà, ses informations sont mises à jour.
 * Sinon, elle est créée et ajoutée à la liste des planètes.
 *
 * @param data        Tableau contenant les informations de la planète sous forme de chaînes de caractères.
 *                    Format attendu : ["", ID, X, Y, ShipID, Saved]
 * @param planet Liste des planètes existantes.
 * @param nb_planets  Pointeur vers le nombre total de planètes (sera mis à jour si une nouvelle planète est ajoutée).
 **/
void parse_planet(char** data, Planet* planets, uint16_t* nb_planets)
{
    if (data == NULL || planets == NULL || nb_planets == NULL) {
        return; // Eviter les erreurs
    }

    // Extraction et conversion des données de la planète
    uint16_t planet_id = (uint16_t)atoi(data[1]);
    uint16_t pos_x = (uint16_t)atoi(data[2]);
    uint16_t pos_y = (uint16_t)atoi(data[3]);
    int8_t ship_id = (int8_t)atoi(data[4]);
    uint8_t is_saved = (uint8_t)atoi(data[5]);

    // Recherche de la planète
    Planet* planet = find_planet(planet_id, planets);

    if (planet == NULL) {
        // Si la planète n'existe pas, la créer et l'ajoute
        create_planet(planet_id, pos_x, pos_y, ship_id, is_saved, planet, nb_planets);
        return;
    }

    // Mise à jour des informations de la planète existante
    planet->x = pos_x;
    planet->y = pos_y;
    planet->ship_id = ship_id;
    planet->saved = is_saved;
}

/**
 * @brief Recherche une planète dans la liste à partir de son identifiant unique.
 *
 * Cette fonction parcourt la liste des planètes et retourne un pointeur vers
 * la planète correspondant à l'identifiant fourni. Si aucune planète n'est trouvée,
 * la fonction retourne NULL.
 *
 * @param planet_id    Identifiant unique de la planète recherchée.
 * @param planet  Tableau contenant toutes les planètes existantes.
 *
 * @return Planet*     Pointeur vers la planète trouvée, ou NULL si aucune correspondance.
 **/
Planet* find_planet(uint16_t planet_id, Planet* planet)
{
    // Parcourt chaque planète dans la liste
    for (Planet* current_planet = planet; current_planet < planet + NB_MAX_PLANETS; current_planet++) {
        // Vérifie si l'identifiant de la planète correspond à celui recherché
        if (current_planet->planet_id == planet_id) {
            return current_planet; // Retourne un pointeur vers la planète trouvée
        }
    }
    return NULL; // Retourne NULL si aucune planète ne correspond à l'ID
}

/**
 * @brief Crée une nouvelle planète et l'ajoute à la liste des planètes existantes.
 *
 * Cette fonction initialise une planète avec les paramètres fournis (ID, coordonnées,
 * ID du vaisseau associé, état de sauvegarde) et l'ajoute au tableau `planet_list`.
 * Elle met également à jour le compteur `total_planets`.
 *
 * @param planet_id     Identifiant unique de la planète.
 * @param pos_x         Position X de la planète.
 * @param pos_y         Position Y de la planète.
 * @param associated_ship_id ID du vaisseau associé (-1 si aucun).
 * @param is_saved      Indique si la planète est sauvegardée (1 = oui, 0 = non).
 * @param planet   Tableau contenant toutes les planètes existantes.
 * @param nb_planets Pointeur vers le compteur du nombre total de planètes.
 **/
void create_planet(uint16_t planet_id, uint16_t pos_x, uint16_t pos_y, int8_t ship_id,
    uint8_t is_saved, Planet* planet, uint16_t* nb_planets)
{
    Planet new_planet;
    new_planet.planet_id = planet_id;

    new_planet.x = pos_x;
    new_planet.y = pos_y;

    new_planet.ship_id = ship_id;
    new_planet.saved = is_saved;

    // Ajoute la nouvelle planète dans la liste à l'index actuel de total_planets
    planet[*nb_planets] = new_planet;

    // Incrémente le compteur du nombre total de planètes
    (*nb_planets)++;
}

/**
 * @brief Supprime toutes les planètes de la liste.
 *
 * Cette fonction réinitialise toutes les propriétés des planètes dans la liste des planètes
 * à leurs valeurs par défaut (0 pour chaque attribut). Le nombre de planètes est également réinitialisé à zéro.
 *
 * @param planet Liste des planètes à réinitialiser.
 * @param nb_planets Pointeur vers le nombre total de planètes, qui sera mis à zéro après la suppression.
 **/
void delete_all_planets(Planet* planet, uint16_t* nb_planets)
{
    if (planet == NULL || nb_planets == NULL) {
        return; // Eviter les erreurs si la liste ou le compteur est NULL
    }

    // Parcours de chaque planète et réinitialisation de ses attributs
    for (uint16_t i = 0; i < NB_MAX_PLANETS; i++) {
        planet[i].planet_id = 0;
        planet[i].x = 0;

        planet[i].y = 0;
        planet[i].ship_id = 0;
        planet[i].saved = 0;
    }

    // Réinitialisation du nombre total de planètes
    *nb_planets = 0;
}
