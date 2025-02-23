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
