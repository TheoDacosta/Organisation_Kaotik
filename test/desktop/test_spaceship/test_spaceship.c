#include "spaceship.h"
#include "unity.h"

// Définition d'un tableau statique de vaiseau pour les tests
Spaceship spaceships[NB_MAX_SPACESHIPS];
uint16_t nb_spaceships = 0;

void test_create_spaceship(void)
{

    // Données de test
    uint8_t team_id = 1;
    int8_t ship_id = 3;

    uint16_t pos_x = 10000;
    uint16_t pos_y = 11200;
    uint8_t broken = 1;

    // Création du vaisseau
    create_spaceship(team_id, ship_id, pos_x, pos_y, broken, spaceships, &nb_spaceships);

    // Vérifications
    TEST_ASSERT_EQUAL(1, nb_spaceships);
    Spaceship* last_ship = &spaceships[nb_spaceships - 1];

    TEST_ASSERT_EQUAL(team_id, last_ship->team_id);
    TEST_ASSERT_EQUAL(ship_id, last_ship->ship_id);

    TEST_ASSERT_EQUAL(pos_x, last_ship->x);
    TEST_ASSERT_EQUAL(pos_y, last_ship->y);
    TEST_ASSERT_EQUAL(broken, last_ship->broken);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_create_spaceship);
    return UNITY_END();
}
