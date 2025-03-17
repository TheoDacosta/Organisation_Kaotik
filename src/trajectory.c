#include "trajectory.h"
#include "base.h"
#include "spaceship.h"
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
uint16_t get_angle(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y)
{
    float dx = (float)(end_x - start_x);
    float dy = (float)(end_y - start_y);

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
 * @param pos_x1  Coordonnée X du premier point.
 * @param pos_y1  Coordonnée Y du premier point.
 * @param pos_x2  Coordonnée X du deuxième point.
 * @param pos_y2  Coordonnée Y du deuxième point.
 * @return    La distance entre les deux points.
 */
uint16_t get_distance(uint16_t pos_x1, uint16_t pos_y1, uint16_t pos_x2, uint16_t pos_y2)
{
    return (uint16_t)sqrt(pow(pos_x2 - pos_x1, 2) + pow(pos_y2 - pos_y1, 2));
}
/**
 * @brief Retourne l'angle vers le premier vaisseau ennemi à portée.
 *
 * @param attacker Vaisseau attaquant.
 * @param spaceships Liste des vaisseaux.
 * @param nb_spaceships Nombre de vaisseaux.
 * @return Angle vers la cible si trouvée, sinon NOT_FOUND.
 **/
uint16_t get_target_angle(Spaceship_t* attacker, Spaceship_t* spaceships, uint16_t nb_spaceships)
{
    for (uint8_t i = 0; i < nb_spaceships; i++) {
        uint16_t distance = get_distance(attacker->x, attacker->y, spaceships[i].x, spaceships[i].y);

        if (spaceships[i].team_id != 0 && distance <= FIRE_RANGE) {
            return get_angle(attacker->x, attacker->y, spaceships[i].x, spaceships[i].y);
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
    uint16_t nearest_distance = AREA_LENGTH;
    uint16_t distance;
    for (int i = 0; i < nb_planets; i++) {
        if (!planets[i].saved && planets[i].ship_id == -1 && (!planets[i].focus || planets[i].focus == spaceship->ship_id)) {
            distance = get_distance(spaceship->x, spaceship->y, planets[i].x, planets[i].y);
            if (distance < nearest_distance) {
                nearest_distance = distance;
                nearest_planet = &planets[i]; // Mise à jour correcte du pointeur
            }
        }
    }
    return nearest_planet;
}

/**
 * @brief Calcule la position du vaisseau suiveur avec un décalage par rapport au leader.
 *
 * @param follower Vaisseau suiveur.
 * @param target   Vaisseau à suivre.
 * @param offset_x Décalage en X par rapport au leader.
 * @param offset_y Décalage en Y par rapport au leader.
 */
uint16_t get_angle_to_follow(Spaceship_t* follower, Spaceship_t* target, int16_t offset_x, int16_t offset_y)
{
    int16_t x_target = target->x + offset_x;
    int16_t y_target = target->y + offset_y;
    if (x_target < 0 || x_target > AREA_LENGTH) {
        x_target = target->x;
    }
    if (y_target < 0 || y_target > AREA_LENGTH) {
        y_target = target->y;
    }
    return get_angle(follower->x, follower->y, (uint16_t)x_target, (uint16_t)y_target);
}
