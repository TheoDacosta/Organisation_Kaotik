#include "planet.h"
#include "unity.h"
#include <stdlib.h>

void setUp(void)
{
    Planet_t new_planet = { .planet_id = 1001, .saved = 0, .position = { .x = 3217, .y = 4321 }, .ship_id = -1 };
    planets[0] = new_planet;
    nb_planets = 1;
}

void test_parse_planet(void)
{
    // Arrange
    char* data = "P 12 3217 4321 31 0";

    // Act
    parse_planet(data, planets, &nb_planets);

    // Assert
    TEST_ASSERT_EQUAL(2, nb_planets);

    Planet_t* new_planet = &planets[nb_planets - 1];
    TEST_ASSERT_EQUAL(12, new_planet->planet_id);

    TEST_ASSERT_EQUAL(3217, new_planet->position.x);
    TEST_ASSERT_EQUAL(4321, new_planet->position.y);

    TEST_ASSERT_EQUAL(31, new_planet->ship_id);
    TEST_ASSERT_EQUAL(0, new_planet->saved);
}

void test_find_planet_not_found(void)
{

    // Recherche d'une planète qui n'existe pas dans la liste
    Planet_t* planet = find_planet(490);

    // Vérification que la fonction retourne NULL si la planète n'est pas trouvée
    TEST_ASSERT_NULL(planet);
}

void test_find_planet_found(void)
{
    // Recherche d'une planète existante dans la liste avec un planet_id
    Planet_t* planet = find_planet(1001);

    // Planète est bien trouvée
    TEST_ASSERT_NOT_NULL(planet);
    TEST_ASSERT_EQUAL(1001, planet->planet_id);
}

void test_init_planet(void)
{
    Planet_t planets[NB_MAX_PLANETS];
    init_planets(planets);

    for (int i = 0; i < NB_MAX_PLANETS; i++) {
        TEST_ASSERT_EQUAL(0, planets[i].planet_id);
        TEST_ASSERT_EQUAL(-1, planets[i].ship_id);
        TEST_ASSERT_EQUAL(0, planets[i].position.x);
        TEST_ASSERT_EQUAL(0, planets[i].position.y);
        TEST_ASSERT_EQUAL(0, planets[i].saved);
    }
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_find_planet_not_found);
    RUN_TEST(test_find_planet_found);
    RUN_TEST(test_parse_planet);
    RUN_TEST(test_init_planet);
    return UNITY_END();
}
