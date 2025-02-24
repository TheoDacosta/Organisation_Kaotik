#include "planet.h"
#include "unity.h"
#include <stdio.h>

// Définition d'un tableau statique de planètes pour les tests
Planet_t planets[NB_MAX_PLANETS];
uint16_t nb_planets = 0;

void setUp(void)
{
    // Préparation des données de test : création de 5 planètes avec des valeurs differente.
    create_planet(1000, 15000, 20000, 5, 0, planets, &nb_planets);
    create_planet(1001, 12000, 14000, -1, 1, planets, &nb_planets);
    create_planet(1002, 8000, 9500, 10, 0, planets, &nb_planets);
    create_planet(1003, 13000, 18000, 3, 0, planets, &nb_planets);
    create_planet(1004, 9000, 11000, -2, 1, planets, &nb_planets);
}

void tearDown(void)
{
    // Nettoyage des planètes
    delete_all_planets(planets, &nb_planets);
}

void test_parse_planet(void)
{
    // Exemple de donnee de test
    char* data[] = { "", "1500", "1200", "3000", "2", "1" };

    // Fonction pour parser et ajouter la planète
    parse_planet(data, planets, &nb_planets);

    // Vérification que la planète a été ajoutée
    TEST_ASSERT_EQUAL(6, nb_planets);
    TEST_ASSERT_EQUAL(1500, planets[5].planet_id);

    TEST_ASSERT_EQUAL(1200, planets[5].x);
    TEST_ASSERT_EQUAL(3000, planets[5].y);

    TEST_ASSERT_EQUAL(2, planets[5].ship_id);
    TEST_ASSERT_EQUAL(1, planets[5].saved);
}

void test_create_planet(void)
{
    // Définition des valeurs de test
    uint16_t planet_id = 352;
    uint16_t pos_x = 10000;
    uint16_t pos_y = 11200;
    int8_t ship_id = 3;
    uint8_t saved = 1;

    // Teste dfonction à tester
    create_planet(planet_id, pos_x, pos_y, ship_id, saved, planets, &nb_planets);

    // Vérification des résultats attendus
    TEST_ASSERT_EQUAL(6, nb_planets);
    TEST_ASSERT_LESS_THAN_UINT16(NB_MAX_PLANETS, nb_planets);

    // position de planète ajoutée est correcte
    TEST_ASSERT_EQUAL(planet_id, planets[nb_planets - 1].planet_id);

    TEST_ASSERT_EQUAL(pos_x, planets[nb_planets - 1].x);
    TEST_ASSERT_EQUAL(pos_y, planets[nb_planets - 1].y);

    TEST_ASSERT_EQUAL(ship_id, planets[nb_planets - 1].ship_id);
    TEST_ASSERT_EQUAL(saved, planets[nb_planets - 1].saved);
}

void test_find_planet_null(void)
{

    // Recherche d'une planète qui n'existe pas dans la liste
    Planet_t* planet = find_planet(490, planets);

    // Vérification que la fonction retourne NULL si la planète n'est pas trouvée
    TEST_ASSERT_NULL(planet);
}

void test_find_planet(void)
{
    // Recherche d'une planète existante dans la liste avec un planet_id
    Planet_t* planet = find_planet(1003, planets);

    // Vérification du nombre de planètes dans la liste après la recherche
    TEST_ASSERT_EQUAL(5, nb_planets);

    // Planète est bien trouvée
    TEST_ASSERT_NOT_NULL(planet);
    TEST_ASSERT_EQUAL(1003, planet->planet_id);

    TEST_ASSERT_EQUAL(13000, planet->x);
    TEST_ASSERT_EQUAL(18000, planet->y);

    TEST_ASSERT_EQUAL(3, planet->ship_id);
    TEST_ASSERT_EQUAL(0, planet->saved);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_create_planet);
    RUN_TEST(test_find_planet_null);
    RUN_TEST(test_find_planet);
    RUN_TEST(test_parse_planet);
    return UNITY_END();
}
