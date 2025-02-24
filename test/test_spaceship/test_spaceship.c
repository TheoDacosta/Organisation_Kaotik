#include "spaceship.h"
#include "unity.h"

// Définition d'un tableau statique de vaiseau pour les tests
Spaceship_t spaceships[NB_MAX_SPACESHIPS];
uint16_t nb_spaceships = 0;

void setUp(void)
{
    // Initialisation de la liste des vaisseaux
    create_spaceship(0, 1, 12000, 13000, 0, spaceships, &nb_spaceships);
    create_spaceship(1, 2, 11000, 12500, 1, spaceships, &nb_spaceships);

    create_spaceship(2, 3, 10000, 11200, 1, spaceships, &nb_spaceships);
    create_spaceship(3, 4, 9000, 11000, 0, spaceships, &nb_spaceships);
    create_spaceship(4, 5, 8000, 10000, 1, spaceships, &nb_spaceships);
}

void tearDown(void)
{
    // Réinitialise la liste des vaisseaux
    delete_all_spaceships(spaceships, &nb_spaceships);
}

void test_parse_spaceship(void)
{
    // Exemple de donnee de test
    char* data[] = { "", "12", "3", "30000", "22000", "1" };

    parse_spaceship(data, spaceships, &nb_spaceships);

    // Vérification que le vaisseau a été ajoutée
    TEST_ASSERT_EQUAL(6, nb_spaceships);
    Spaceship_t* new_ship = &spaceships[nb_spaceships - 1];

    TEST_ASSERT_EQUAL(12, new_ship->team_id);

    TEST_ASSERT_EQUAL(3, new_ship->ship_id);
    TEST_ASSERT_EQUAL(30000, new_ship->x);

    TEST_ASSERT_EQUAL(22000, new_ship->y);
    TEST_ASSERT_EQUAL(1, new_ship->broken);
}

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
    TEST_ASSERT_EQUAL(6, nb_spaceships);
    Spaceship_t* last_ship = &spaceships[nb_spaceships - 1];

    TEST_ASSERT_EQUAL(team_id, last_ship->team_id);
    TEST_ASSERT_EQUAL(ship_id, last_ship->ship_id);

    TEST_ASSERT_EQUAL(pos_x, last_ship->x);
    TEST_ASSERT_EQUAL(pos_y, last_ship->y);
    TEST_ASSERT_EQUAL(broken, last_ship->broken);
}

void test_find_spaceship_not_found(void)
{
    // Cherche un vaisseau qui n'existe pas
    Spaceship_t* found_spaceship = find_spaceship_by_id(5, 1, spaceships);

    // Vérifie que le vaisseau n'a pas été trouvé (doit être NULL)
    TEST_ASSERT_NULL(found_spaceship);
}

void test_find_spaceship_found(void)
{
    // Cherche un vaisseau existant avec team_id=4 et ship_id=5
    Spaceship_t* found_spaceship = find_spaceship_by_id(4, 5, spaceships);

    // Vérifie que le vaisseau est trouvé et les données sont correctes
    TEST_ASSERT_EQUAL(5, nb_spaceships);
    TEST_ASSERT_NOT_NULL(found_spaceship);

    TEST_ASSERT_EQUAL(4, found_spaceship->team_id);
    TEST_ASSERT_EQUAL(5, found_spaceship->ship_id);

    TEST_ASSERT_EQUAL(8000, found_spaceship->x);
    TEST_ASSERT_EQUAL(10000, found_spaceship->y);
    TEST_ASSERT_EQUAL(1, found_spaceship->broken);
}

void test_set_invalid_spaceship(void)
{
    // Modification un vaisseau inexistant (team_id = 2, ship_id = 5)
    set_spaceship(2, 5, 8000, 10000, 1, spaceships);

    // Vérifie que le vaisseau existant (team_id = 5, ship_id = 1)
    Spaceship_t* spaceship = find_spaceship_by_id(2, 3, spaceships);
    TEST_ASSERT_NOT_NULL(spaceship);

    TEST_ASSERT_EQUAL(10000, spaceship->x);
    TEST_ASSERT_EQUAL(11200, spaceship->y);
    TEST_ASSERT_EQUAL(1, spaceship->broken);
}

void test_update_spaceship(void)
{
    // Modifier un vaisseau existant
    set_spaceship(2, 3, 8000, 10000, 1, spaceships);

    // Vérifier la mise à jour
    Spaceship_t* updated_spaceship = find_spaceship_by_id(2, 3, spaceships);
    TEST_ASSERT_NOT_NULL(updated_spaceship);

    TEST_ASSERT_EQUAL(8000, updated_spaceship->x);
    TEST_ASSERT_EQUAL(10000, updated_spaceship->y);
    TEST_ASSERT_EQUAL(1, updated_spaceship->broken);
}

void test_delete_all_spaceships(void)
{
    // Suppression de tous les vaisseaux
    delete_all_spaceships(spaceships, &nb_spaceships);

    // Vérifie que le nombre total de vaisseaux est bien remis à zéro
    TEST_ASSERT_EQUAL(0, nb_spaceships);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_parse_spaceship);
    RUN_TEST(test_create_spaceship);
    RUN_TEST(test_find_spaceship_not_found);
    RUN_TEST(test_find_spaceship_found);
    RUN_TEST(test_set_invalid_spaceship);
    RUN_TEST(test_update_spaceship);
    RUN_TEST(test_delete_all_spaceships);
    return UNITY_END();
}
