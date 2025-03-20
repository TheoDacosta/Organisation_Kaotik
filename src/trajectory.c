#include "trajectory.h"
#include "base.h"
#include "spaceship.h"
#include <stdlib.h>

/**
 * @brief Calcule l'angle de déplacement entre deux points.
 *
 * @param start_point  Coordonnées de départ.
 * @param end_point    Coordonnées d'arrivée.
 * @return         Angle de déplacement en degrés (0-359).
 **/
uint16_t get_angle(Point_t start_point, Point_t end_point)
{
    float dx = (float)(end_point.x - start_point.x);
    float dy = (float)(end_point.y - start_point.y);

    // Calcul de l'angle en radians
    float angle_rad = atan2(dy, dx);

    // Conversion de l'angle en degrés
    float angle_deg = angle_rad * (180.0f / M_PI);

    if (angle_deg < 0) {
        angle_deg += MAX_ANGLE;
    }

    return (uint16_t)angle_deg;
}

/**
 * @brief Calcule la distance entre deux points dans un plan 2D.
 *
 * @param point1  Coordonnées du premier point.
 * @param point2  Coordonnées du deuxième point.
 * @return    La distance entre les deux points.
 */
uint16_t get_distance(Point_t point1, Point_t point2)
{
    return (uint16_t)sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
}
/**
 * @brief Retourne l'angle vers le premier vaisseau ennemi à portée.
 *
 * @param attacker Vaisseau attaquant.
 * @param spaceships Liste des vaisseaux.
 * @param nb_spaceships Nombre de vaisseaux.
 * @return Angle vers la cible si trouvée, sinon NOT_FOUND.
 **/
uint16_t get_target_angle(Spaceship_t* attacker)
{
    for (uint8_t i = 0; i < nb_spaceships; i++) {
        uint16_t distance = get_distance(attacker->position, spaceships[i].position);

        if (spaceships[i].team_id != 0 && distance <= FIRE_RANGE) {
            return get_angle(attacker->position, spaceships[i].position);
        }
    }
    return NOT_FOUND;
}

/**
 * @brief Trouve la planète la plus proche d'un vaisseau.
 *
 * @param spaceship Vaisseau dont on cherche la planète la plus proche.
 * @param planets Liste des planètes.
 * @return Pointeur vers la planète la plus proche ou NULL si aucune planète n'est trouvée.
 */
Planet_t* find_nearest_planet(Spaceship_t* spaceship, Planet_t* planets, uint16_t nb_planets)
{
    Planet_t* nearest_planet = NULL;
    uint16_t nearest_distance = AREA_LENGTH * 2;
    uint16_t distance;
    for (int i = 0; i < nb_planets; i++) {
        if (!planets[i].saved && planets[i].ship_id == -1) {
            distance = get_distance(spaceship->position, planets[i].position);
            if (distance < nearest_distance) {
                nearest_distance = distance;
                nearest_planet = &planets[i];
            }
        }
    }
    return nearest_planet;
}

/**
 * @brief Calcule la position d'un point avec décalage.
 *
 * @param point   Point à décaler.
 * @param offset_x Décalage en X.
 * @param offset_y Décalage en Y.
 * @param point_with_offset Pointeur vers le point avec décalage.
 */
void get_point_with_offset(Point_t point, int16_t offset_x, int16_t offset_y, Point_t* point_with_offset)
{
    int16_t x_point = point.x + offset_x;
    int16_t y_point = point.y + offset_y;
    if (x_point < 0 || x_point > AREA_LENGTH) {
        x_point = point.x;
    }
    if (y_point < 0 || y_point > AREA_LENGTH) {
        y_point = point.y;
    }
    point_with_offset->x = (uint16_t)x_point;
    point_with_offset->y = (uint16_t)y_point;
}
