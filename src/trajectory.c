#include "trajectory.h"
#include <stdlib.h>

/**
 * @brief Calcule l'angle de déplacement entre deux points.
 *
 * @param start_x  Coordonnée X de départ.
 * @param start_y  Coordonnée Y de départ.
 * @param end_x    Coordonnée X d'arrivée.
 * @param end_y    Coordonnée Y d'arrivée.
 * @return         Angle de déplacement en degrés (0-359).
 **/
uint16_t get_travel_angle(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y)
{
    float dx = (float)(end_x - start_x);
    float dy = (float)(end_y - start_y);

    // Calcul de l'angle en radians
    float angle_rad = atan2(dy, dx);

    // Conversion de l'angle en degrés
    float angle_deg = angle_rad * (180.0f / M_PI);

    // Ajustement pour obtenir un angle entre 0 et 359°
    if (angle_deg < 0) {
        angle_deg += 360.0f;
    }

    return (uint16_t)angle_deg;
}

/**
 * @brief Calcule la distance euclidienne entre deux points dans un plan 2D.
 *
 * @param pos_x1  Coordonnée X du premier point.
 * @param pos_y1  Coordonnée Y du premier point.
 * @param pos_x2  Coordonnée X du deuxième point.
 * @param pos_y2  Coordonnée Y du deuxième point.
 * @return    La distance entre les deux points.
 */
float calculate_distance(float pos_x1, float pos_y1, float pos_x2, float pos_y2)
{
    float distance_x = pos_x2 - pos_x1;
    float distance_y = pos_y2 - pos_y1;

    float distance = sqrt(pow(distance_x, 2) + pow(distance_y, 2));

    return round(distance);
}

/**
 * @brief Assigne à chaque collecteur la planète la plus proche.
 *
 * @param collector1     Premier collecteur.
 * @param collector2     Deuxième collecteur.
 * @param planets        Liste des planètes.
 * @param nb_planets     Nombre total de planètes.
 * @param results        Tableau des résultats [vaisseau][planète assignée].
 */
void determine_target_planets(Spaceship_t collector1, Spaceship_t collector2,
    Planet_t* planets, uint8_t nb_planets, Planet_t* target_planet1, Planet_t* target_planet2)
{

    uint16_t min_dist1 = AREA_LENGTH, min_dist2 = AREA_LENGTH;
    Planet_t* closest_planet1 = NULL;
    Planet_t* closest_planet2 = NULL;

    for (uint8_t i = 0; i < nb_planets; i++) {
        if (!planets[i].saved) {
            uint16_t dist_to_col1 = calculate_distance(collector1.x, collector1.y, planets[i].x, planets[i].y);
            uint16_t dist_to_col2 = calculate_distance(collector2.x, collector2.y, planets[i].x, planets[i].y);

            if (dist_to_col1 < min_dist1) {
                min_dist1 = dist_to_col1;
                closest_planet1 = &planets[i];
            }

            if (dist_to_col2 < min_dist2 && (closest_planet1 != NULL && planets[i].ship_id != closest_planet1->ship_id)) {
                min_dist2 = dist_to_col2;
                closest_planet2 = &planets[i];
            }
        }
    }

    target_planet1 = closest_planet1;
    target_planet2 = closest_planet2;
}

/**
 * @brief Retourne l'angle vers le premier vaisseau ennemi à portée.
 *
 * Parcourt la liste des vaisseaux et retourne l'angle vers la première cible
 * ennemie détectée dans la portée de tir.
 *
 * @param attacker Vaisseau attaquant.
 * @param spaceships Liste des vaisseaux.
 * @return Angle vers la cible si trouvée, sinon NOT_FOUND.
 **/
uint16_t get_target_angle(Spaceship_t attacker, Spaceship_t* spaceships)
{
    for (uint8_t i = 0; i < NB_MAX_SPACESHIPS; i++) {
        uint16_t distance = calculate_distance(attacker.x, attacker.y, spaceships[i].x, spaceships[i].y);

        if (distance < FIRE_RANGE && spaceships[i].team_id != 0) {
            return get_travel_angle(attacker.x, attacker.y, spaceships[i].x, spaceships[i].y);
        }
    }
    return NOT_FOUND;
}
