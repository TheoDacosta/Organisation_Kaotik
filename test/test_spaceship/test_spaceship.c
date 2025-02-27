#include "base.h"
#include "commands.h"
#include "spaceship.h"
#include "unity.h"

// Définition d'un tableau statique de vaiseau pour les tests
Spaceship_t spaceships[NB_MAX_SPACESHIPS];
uint16_t nb_spaceships = 0;

void setUp(void)
{
    Spaceship_t new_spaceship = { 0, 4, 10000, 11200, 0 };
    spaceships[0] = new_spaceship;
    nb_spaceships++;
}

void tearDown(void)
{
    nb_spaceships = 0;
}

void test_parse_spaceship(void)
{
    // Exemple de donnee de test
    char* data = "S 1 31 3217 4321 0";

    parse_spaceship(data, spaceships, &nb_spaceships);

    // Vérification que le vaisseau a été ajoutée
    TEST_ASSERT_EQUAL(2, nb_spaceships);

    Spaceship_t* new_ship = &spaceships[nb_spaceships - 1];
    TEST_ASSERT_EQUAL(1, new_ship->team_id);
    TEST_ASSERT_EQUAL(31, new_ship->ship_id);

    TEST_ASSERT_EQUAL(3217, new_ship->x);
    TEST_ASSERT_EQUAL(4321, new_ship->y);

    TEST_ASSERT_EQUAL(0, new_ship->broken);
}

void test_find_spaceship_not_found_team_id(void)
{
    // Act
    Spaceship_t* found_spaceship = find_spaceship(5, 1, spaceships, nb_spaceships);

    // Assert
    TEST_ASSERT_NULL(found_spaceship);
}

void test_find_spaceship_not_found_ship_id(void)
{
    // Act
    Spaceship_t* found_spaceship = find_spaceship(1, 5, spaceships, nb_spaceships);

    // Assert
    TEST_ASSERT_NULL(found_spaceship);
}

void test_find_spaceship_found(void)
{
    // Act
    Spaceship_t* found_spaceship = find_spaceship(0, 4, spaceships, nb_spaceships);

    TEST_ASSERT_NOT_NULL(found_spaceship);

    TEST_ASSERT_EQUAL(0, found_spaceship->team_id);
    TEST_ASSERT_EQUAL(4, found_spaceship->ship_id);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_parse_spaceship);
    RUN_TEST(test_find_spaceship_not_found_team_id);
    RUN_TEST(test_find_spaceship_not_found_ship_id);
    RUN_TEST(test_find_spaceship_found);
    return UNITY_END();
}
