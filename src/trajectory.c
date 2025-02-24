#include "trajectory.h"
#include "planet.h"
#include "spaceship.h"

/**
 * @brief Calcule l'angle de déplacement entre deux points.
 *
 * Utilise la fonction atan2 pour déterminer l'angle en radians,
 * puis le convertit en degrés et ajuste la valeur pour qu'elle soit comprise entre 0 et 359°.
 *
 * @param start_x  Coordonnée X de départ.
 * @param start_y  Coordonnée Y de départ.
 * @param end_x    Coordonnée X d'arrivée.
 * @param end_y    Coordonnée Y d'arrivée.
 * @return         Angle de déplacement en degrés (0-359).
 **/
uint16_t get_travel_angle(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y)
{
    // Calcul des différences de coordonnées
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

    // Conversion en uint16_t (valeur entière)
    return (uint16_t)angle_deg;
}

/**
 * @brief Calcule la distance euclidienne entre deux points dans un plan 2D.
 *
 * Cette fonction utilise le théorème de Pythagore pour calculer la distance
 * entre deux points (x1, y1) et (x2, y2) dans un espace à deux dimensions.
 * Elle renvoie le résultat arrondi à l'entier le plus proche.
 *
 * @param pos_x1  Coordonnée X du premier point.
 * @param pos_y1  Coordonnée Y du premier point.
 * @param pos_x2  Coordonnée X du deuxième point.
 * @param pos_y2  Coordonnée Y du deuxième point.
 * @return    La distance euclidienne entre les deux points, arrondie à l'entier le plus proche.
 */
float calculate_distance(float pos_x1, float pos_y1, float pos_x2, float pos_y2)
{
    // Calcul des différences de coordonnées
    float distance_x = pos_x2 - pos_x1;
    float distance_y = pos_y2 - pos_y1;

    // Calcul de la distance euclidienne avec la formule de Pythagore
    float distance = sqrt(pow(distance_x, 2) + pow(distance_y, 2));

    // Retourne la distance arrondie à l'entier le plus proche
    return round(distance);
}

/**
 * @brief Assigne à chaque vaisseau collecteur la planète la plus proche.
 *
 * @param collector1     Premier vaisseau collecteur.
 * @param collector2     Deuxième vaisseau collecteur.
 * @param planets        Liste des planètes.
 * @param nb_planets     Nombre total de planètes.
 * @param results        Tableau des résultats [vaisseau][planète assignée].
 */
void determine_target_planets(Spaceship_t collector1, Spaceship_t collector2,
    Planet_t* planets, uint8_t nb_planets, uint16_t results[2][2])
{
    results[0][0] = collector1.ship_id;
    results[1][0] = collector2.ship_id;

    uint16_t min_dist1 = AREA_LENGTH, min_dist2 = AREA_LENGTH;
    uint8_t closest_planet1 = 0, closest_planet2 = 0;

    for (uint8_t i = 0; i < nb_planets; i++) {
        if (!planets[i].saved) {
            uint16_t dist_to_col1 = calculate_distance(collector1.x, collector1.y, planets[i].x, planets[i].y);
            uint16_t dist_to_col2 = calculate_distance(collector2.x, collector2.y, planets[i].x, planets[i].y);

            if (dist_to_col1 < min_dist1) {
                min_dist1 = dist_to_col1;
                closest_planet1 = i;
            }

            if (dist_to_col2 < min_dist2 && i != closest_planet1) {
                min_dist2 = dist_to_col2;
                closest_planet2 = i;
            }
        }
    }

    results[0][1] = closest_planet1;
    results[1][1] = closest_planet2;
}
