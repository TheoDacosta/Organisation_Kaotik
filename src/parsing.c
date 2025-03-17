#include "parsing.h"
#include "base.h"
#include "planet.h"
#include "spaceship.h"
#include "trajectory.h"
#include <stdlib.h>

Mutex_t parsing_mutex;

void save_planets_data(Planet_t* planets_saved_datas, uint16_t nb_planets_saved);
void restore_planets_datas(Planet_t* planets_saved_datas, uint16_t nb_planets_saved);
void parse_data(char* data);

/**
 * @brief Récupération des données du jeu (planètes, vaisseaux, base).
 *
 * @param response Chaines de caractères contenant les données du jeu.
 * @param planets Liste des planètes.
 * @param nb_planets Nombre de planètes.
 * @param spaceships Liste des vaisseaux.
 * @param nb_spaceships Nombre de vaisseaux.
 * @param base Coordonnées de la base.
 */
void parse_response(const char* response)
{
    if (response == NULL || (response[0] == 'O' && response[1] == 'K' && response[2] == '\0')) {
        return;
    }

    get_mutex(parsing_mutex);
    uint16_t nb_planets_saved = nb_planets;
    Planet_t planets_saved_datas[NB_MAX_PLANETS];
    save_planets_data(planets_saved_datas, nb_planets_saved);
    nb_planets = 0;
    nb_spaceships = 0;
    uint16_t pos = 0;
    const char delimiter = ',';
    char token[MAX_DATA_SIZE];

    for (uint16_t i = 0; response[i] != '\0'; i++) {
        if (response[i] == delimiter) {
            token[pos] = '\0';
            parse_data(token);
            pos = 0;
        } else {
            token[pos] = response[i];
            pos++;
        }
    }
    token[pos] = '\0';
    parse_data(token);

    release_mutex(parsing_mutex);
}

/**
 * @brief Récupération des données d'une information de jeu.
 *
 * @param data Chaine de caractère contenant une donnée du jeu.
 */
void parse_data(char* data)
{
    if (data == NULL) {
        return;
    }
    switch (data[0]) {
    case DATA_TYPE_PLANET:
        parse_planet(data);
        break;
    case DATA_TYPE_SPACESHIP:
        parse_spaceship(data);
        break;
    case DATA_TYPE_BASE:
        data++;
        data++;
        base.x = atoi(data);
        while (*data != ' ')
            data++;
        data++;
        base.y = atoi(data);
        break;
    default:
        break;
    }
}

void save_planets_data(Planet_t* planets_saved_datas, uint16_t nb_planets_saved)
{
    for (uint16_t i = 0; i < nb_planets_saved; i++) {
        Planet_t planet_saved_data = { .planet_id = planets[i].planet_id, .focus = planets[i].focus };
        planets_saved_datas[i] = planet_saved_data;
    }
}

void restore_planets_datas(Planet_t* planets_saved_datas, uint16_t nb_planets_saved)
{
    for (uint16_t i = 0; i < nb_planets; i++) {
        Planet_t* planet_saved = find_planet(planets[i].planet_id, planets_saved_datas, nb_planets_saved);
        if (planet_saved != NULL)
            planets[i].focus = planet_saved->focus;
    }
}
