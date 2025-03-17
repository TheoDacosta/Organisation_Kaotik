#include "base.h"
#include "commands.h"
#include "os_manager.h"
#include "spaceship.h"
#include "unity.h"

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

void test_shoot_current_timeMs(void)
{
    Spaceship_t spaceship = { .team_id = 0, .ship_id = 8, .x = 100, .y = 100 };
    Spaceship_t spaceships[NB_MAX_SPACESHIPS] = {
        { .team_id = 2, .ship_id = 10, .x = 100, .y = 100 },
        { .team_id = 2, .ship_id = 12, .x = 200, .y = 200 }
    };

    char command[MAX_COMMAND_SIZE];

    uint32_t start_time = 0;

    uint32_t current_time = 1200;
    uint32_t elapsed_time = 0;

    shoot_current_timeMs(&elapsed_time, start_time, current_time, &spaceship, spaceships, nb_spaceships, command);

    TEST_ASSERT_GREATER_OR_EQUAL(1000, elapsed_time);
    TEST_ASSERT_EQUAL_STRING("FIRE 8 0\n", command);
}

void test_shut_current_timeMs_no_1s(void)
{
    Spaceship_t spaceship = { .team_id = 0, .ship_id = 8, .x = 100, .y = 100 };
    Spaceship_t spaceships[NB_MAX_SPACESHIPS] = {
        { .team_id = 2, .ship_id = 10, .x = 100, .y = 100 },
        { .team_id = 2, .ship_id = 12, .x = 200, .y = 200 }
    };

    char command[MAX_COMMAND_SIZE] = "";

    uint32_t start_time = 0;
    uint32_t current_time = 700;
    uint32_t elapsed_time = 0;

    shoot_current_timeMs(&elapsed_time, start_time, current_time, &spaceship, spaceships, nb_spaceships, command);

    TEST_ASSERT_LESS_THAN(1000, elapsed_time);
    TEST_ASSERT_EQUAL_STRING("", command);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_parse_spaceship);
    RUN_TEST(test_find_spaceship_not_found_team_id);
    RUN_TEST(test_find_spaceship_not_found_ship_id);
    RUN_TEST(test_find_spaceship_found);
    RUN_TEST(test_shoot_current_timeMs);
    RUN_TEST(test_shut_current_timeMs_no_1s);
    return UNITY_END();
}
