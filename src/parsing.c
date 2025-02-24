#include "parsing.h"
#include <stdlib.h>

void parse_data(char* data, Planet_t* planets, uint16_t* nb_planets, Spaceship_t* spaceships, uint16_t* nb_spaceships, Base_t* base);

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
void parse_response(const char* response, Planet_t* planets, uint16_t* nb_planets, Spaceship_t* spaceships, uint16_t* nb_spaceships, Base_t* base)
{
    uint16_t pos = 0;
    const char delimiter = ',';
    char token[MAX_DATA_SIZE];
    for (uint16_t i = 0; response[i] != '\0'; i++) {
        if (response[i] == delimiter) {
            token[pos] = '\0';
            parse_data(token, planets, nb_planets, spaceships, nb_spaceships, base);
            pos = 0;
        } else {
            token[pos] = response[i];
            pos++;
        }
    }
    token[pos] = '\0';
    parse_data(token, planets, nb_planets, spaceships, nb_spaceships, base);
}

/**
 * @brief Récupération des données d'une information de jeu.
 *
 * @param data Chaine de caractère contenant une donnée du jeu.
 * @param planets Liste des planètes.
 * @param nb_planets Nombre de planètes.
 * @param spaceships Liste des vaisseaux.
 * @param nb_spaceships Nombre de vaisseaux.
 * @param base Coordonnées de la base.
 */
void parse_data(char* data, Planet_t* planets, uint16_t* nb_planets, Spaceship_t* spaceships, uint16_t* nb_spaceships, Base_t* base)
{
    if (data == NULL) {
        return;
    }
    switch (data[0]) {
    case DATA_TYPE_PLANET:
        parse_planet(data, planets, nb_planets);
        break;
    case DATA_TYPE_SPACESHIP:
        parse_spaceship(data, spaceships, nb_spaceships);
        break;
    case DATA_TYPE_BASE:
        data++;
        data++;
        base->x = atoi(data);
        while (*data != ' ')
            data++;
        data++;
        base->y = atoi(data);
        break;
    default:
        break;
    }
}
