#include "parsing.h"
#include "base.h"
#include "planet.h"
#include "spaceship.h"
#include "trajectory.h"
#include <stdlib.h>

void parse_data(char* data, Planet_t* planets_parsed, uint16_t* nb_planets_parsed, Spaceship_t* spaceships_parsed, uint16_t* nb_spaceships_parsed);
void save_datas(Planet_t* planets_parsed, uint16_t nb_planets_parsed, Spaceship_t* spaceships_parsed, uint16_t nb_spaceships_parsed);

/**
 * @brief Récupération des données du jeu (planètes, vaisseaux, base).
 *
 * @param response Chaines de caractères contenant les données du jeu.
 */
void parse_response(const char* response)
{
    get_mutex(response_mutex);
    if (response == NULL || (response[0] == 'O' && response[1] == 'K' && response[2] == '\0')) {
        return;
    }
    uint16_t nb_planets_parsed = 0;
    Planet_t planets_parsed[NB_MAX_PLANETS];
    uint16_t nb_spaceships_parsed = 0;
    Spaceship_t spaceships_parsed[NB_MAX_SPACESHIPS];

    uint16_t pos = 0;
    const char delimiter = ',';
    char token[MAX_DATA_SIZE];

    for (uint16_t i = 0; response[i] != '\0'; i++) {
        if (response[i] == delimiter) {
            token[pos] = '\0';
            parse_data(token, planets_parsed, &nb_planets_parsed, spaceships_parsed, &nb_spaceships_parsed);
            pos = 0;
        } else {
            token[pos] = response[i];
            pos++;
        }
    }
    token[pos] = '\0';
    parse_data(token, planets_parsed, &nb_planets_parsed, spaceships_parsed, &nb_spaceships_parsed);
    save_datas(planets_parsed, nb_planets_parsed, spaceships_parsed, nb_spaceships_parsed);
    release_mutex(response_mutex);
}

/**
 * @brief Récupération des données d'une information de jeu.
 *
 * @param data Chaine de caractère contenant une donnée du jeu.
 * @param planets_parsed Liste des planètes parsées.
 * @param nb_planets_parsed Nombre de planètes parsées.
 * @param spaceships_parsed Liste des vaisseaux parsés.
 * @param nb_spaceships_parsed Nombre de vaisseaux parsés.
 */
void parse_data(char* data, Planet_t* planets_parsed, uint16_t* nb_planets_parsed, Spaceship_t* spaceships_parsed, uint16_t* nb_spaceships_parsed)
{
    if (data == NULL) {
        return;
    }
    switch (data[0]) {
    case DATA_TYPE_PLANET:
        parse_planet(data, planets_parsed, nb_planets_parsed);
        break;
    case DATA_TYPE_SPACESHIP:
        parse_spaceship(data, spaceships_parsed, nb_spaceships_parsed);
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

/**
 * @brief Sauvegarde des données parsées.
 *
 * @param planets_parsed Liste des planètes parsées.
 * @param nb_planets_parsed Nombre de planètes parsées.
 * @param spaceships_parsed Liste des vaisseaux parsés.
 * @param nb_spaceships_parsed Nombre de vaisseaux parsés.
 */
void save_datas(Planet_t* planets_parsed, uint16_t nb_planets_parsed, Spaceship_t* spaceships_parsed, uint16_t nb_spaceships_parsed)
{
    for (uint16_t i = 0; i < nb_planets_parsed; i++) {
        Planet_t* planet = find_planet(planets_parsed[i].planet_id);
        if (planet == NULL) {
            planets[nb_planets] = DEFAULT_PLANET;
            planets[nb_planets] = planets_parsed[i];
            nb_planets++;
        } else {
            if (planets_parsed[i].ship_id != -1) {
                Spaceship_t* spaceship = find_spaceship(0, planets_parsed[i].ship_id);
                if (spaceship != NULL) {
                    (*spaceship).planet_id = planets_parsed[i].planet_id;
                }
            }
            (*planet).planet_id = planets_parsed[i].planet_id;
            (*planet).position.x = planets_parsed[i].position.x;
            (*planet).position.y = planets_parsed[i].position.y;
            (*planet).ship_id = planets_parsed[i].ship_id;
            (*planet).saved = planets_parsed[i].saved;
            // On garde le focus courant
        }
    }
    for (uint16_t i = 0; i < nb_spaceships_parsed; i++) {
        Spaceship_t* spaceship = find_spaceship(spaceships_parsed[i].team_id, spaceships_parsed[i].ship_id);
        if (spaceship == NULL) {
            spaceships[nb_spaceships] = DEFAULT_SPACESHIP;
            spaceships[nb_spaceships] = spaceships_parsed[i];
            nb_spaceships++;
        } else {
            (*spaceship).team_id = spaceships_parsed[i].team_id;
            (*spaceship).ship_id = spaceships_parsed[i].ship_id;
            (*spaceship).position.x = spaceships_parsed[i].position.x;
            (*spaceship).position.y = spaceships_parsed[i].position.y;
            (*spaceship).broken = spaceships_parsed[i].broken;
            // On garde le dernier tir/scan courant
        }
    }
    nb_planets = nb_planets_parsed;
    nb_spaceships = nb_spaceships_parsed;
}
