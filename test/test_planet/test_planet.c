#include "planet.h"
#include "unity.h"
#include <stdlib.h>

Planet_t planets[NB_MAX_PLANETS];
uint16_t nb_planets;

void setUp(void)
{
    Planet_t new_planet = { 1001, 1000, 2000, 1, 0, 0 };
    planets[0] = new_planet;
    nb_planets++;
}

void tearDown(void)
{
    nb_planets = 0;
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

    TEST_ASSERT_EQUAL(3217, new_planet->x);
    TEST_ASSERT_EQUAL(4321, new_planet->y);

    TEST_ASSERT_EQUAL(31, new_planet->ship_id);
    TEST_ASSERT_EQUAL(0, new_planet->saved);
}

void test_find_planet_not_found(void)
{

    // Recherche d'une planète qui n'existe pas dans la liste
    Planet_t* planet = find_planet(490, planets, nb_planets);

    // Vérification que la fonction retourne NULL si la planète n'est pas trouvée
    TEST_ASSERT_NULL(planet);
}

void test_find_planet_found(void)
{
    // Recherche d'une planète existante dans la liste avec un planet_id
    Planet_t* planet = find_planet(1001, planets, nb_planets);

    // Planète est bien trouvée
    TEST_ASSERT_NOT_NULL(planet);
    TEST_ASSERT_EQUAL(1001, planet->planet_id);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_find_planet_not_found);
    RUN_TEST(test_find_planet_found);
    RUN_TEST(test_parse_planet);
    return UNITY_END();
}
