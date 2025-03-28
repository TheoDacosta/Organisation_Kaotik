#include "base.h"
#include "commands.h"
#include "os_manager.h"
#include "spaceship.h"
#include "unity.h"

void setUp(void)
{
    reset_time();
    Spaceship_t new_spaceship = { .team_id = 0, .ship_id = 4, .position = { .x = 3217, .y = 4321 }, .broken = 0 };
    Spaceship_t new_spaceship_current = { .last_shoot_time = get_current_timeMs(), .last_radar_time = get_current_timeMs() };
    spaceships[0] = new_spaceship;
    spaceships[1] = new_spaceship_current;
    nb_spaceships = 2;
}

void test_parse_spaceship(void)
{
    // Exemple de donnee de test
    char* data = "S 1 31 3217 4321 0";

    parse_spaceship(data, spaceships, &nb_spaceships);

    // Vérification que le vaisseau a été ajoutée
    TEST_ASSERT_EQUAL(3, nb_spaceships);

    Spaceship_t* new_ship = &spaceships[nb_spaceships - 1];
    TEST_ASSERT_EQUAL(1, new_ship->team_id);
    TEST_ASSERT_EQUAL(31, new_ship->ship_id);

    TEST_ASSERT_EQUAL(3217, new_ship->position.x);
    TEST_ASSERT_EQUAL(4321, new_ship->position.y);

    TEST_ASSERT_EQUAL(0, new_ship->broken);
}

void test_find_spaceship_not_found_team_id(void)
{
    // Act
    Spaceship_t* found_spaceship = find_spaceship(5, 1);

    // Assert
    TEST_ASSERT_NULL(found_spaceship);
}

void test_find_spaceship_not_found_ship_id(void)
{
    // Act
    Spaceship_t* found_spaceship = find_spaceship(1, 5);

    // Assert
    TEST_ASSERT_NULL(found_spaceship);
}

void test_find_spaceship_found(void)
{
    // Act
    Spaceship_t* found_spaceship = find_spaceship(0, 4);

    TEST_ASSERT_NOT_NULL(found_spaceship);

    TEST_ASSERT_EQUAL(0, found_spaceship->team_id);
    TEST_ASSERT_EQUAL(4, found_spaceship->ship_id);
}

void test_can_shoot_after_long_pause()
{
    // Spaceship_t spaceship = { .last_shoot_time = get_current_timeMs() };
    os_delayMs(1100);

    TEST_ASSERT_TRUE(can_shoot(&spaceships[1]));
}

void test_can_not_shoot_after_short_pause()
{
    // Spaceship_t spaceship = { .last_shoot_time = get_current_timeMs() };

    os_delayMs(900);

    TEST_ASSERT_FALSE(can_shoot(&spaceships[1]));
}

void test_init_spaceships(void)
{
    Spaceship_t spaceships[NB_MAX_SPACESHIPS];
    init_spaceships(spaceships);
    TEST_ASSERT_EQUAL(0, spaceships[0].team_id);
    TEST_ASSERT_EQUAL(-1, spaceships[0].ship_id);
    TEST_ASSERT_EQUAL(0, spaceships[0].position.x);
    TEST_ASSERT_EQUAL(0, spaceships[0].position.y);
    TEST_ASSERT_EQUAL(0, spaceships[0].broken);
    TEST_ASSERT_EQUAL(0, spaceships[0].last_shoot_time);
    TEST_ASSERT_EQUAL(0, spaceships[0].last_radar_time);
}

void test_can_scan_after_long_pause()
{
    os_delayMs(SCAN_COOLDOWN + 100);
    TEST_ASSERT_TRUE(can_scan(&spaceships[1]));
}

void test_can_not_scan_after_short_pause()
{
    os_delayMs(SCAN_COOLDOWN - 100);
    TEST_ASSERT_FALSE(can_scan(&spaceships[1]));
}

void test_shoot(void)
{
    char command[MAX_COMMAND_SIZE];
    spaceships[nb_spaceships] = (Spaceship_t) { .team_id = 1, .ship_id = 4, .position = { .x = 3217, .y = 4321 }, .broken = 0 };
    nb_spaceships++;
    shoot(&spaceships[0], command);
    TEST_ASSERT_EQUAL_STRING("FIRE 4 0\n", command);
}

void test_scan(void)
{
    char command[MAX_COMMAND_SIZE];
    scan(&spaceships[0], command);
    TEST_ASSERT_EQUAL_STRING("RADAR 4\n", command);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_parse_spaceship);
    RUN_TEST(test_find_spaceship_not_found_team_id);
    RUN_TEST(test_find_spaceship_not_found_ship_id);
    RUN_TEST(test_find_spaceship_found);
    RUN_TEST(test_can_shoot_after_long_pause);
    RUN_TEST(test_can_not_shoot_after_short_pause);
    RUN_TEST(test_init_spaceships);
    RUN_TEST(test_can_scan_after_long_pause);
    RUN_TEST(test_can_not_scan_after_short_pause);
    RUN_TEST(test_shoot);
    RUN_TEST(test_scan);
    return UNITY_END();
}
