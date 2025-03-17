#include "commands.h"
#include "planet.h"
#include "strategy.h"
#include "trajectory.h"
#include "unity.h"
#include <stdlib.h>

Spaceship_t spaceship;
Spaceship_t target_spaceship;
char command[MAX_COMMAND_SIZE];

void setUp(void)
{
    nb_planets = 0;
    nb_spaceships = 0;
    spaceship.team_id = 0;
    spaceship.ship_id = 1;
    spaceship.broken = 0;
    spaceship.x = 10000;
    spaceship.y = 10000;
    target_spaceship.team_id = 1;
    target_spaceship.ship_id = 3;
    target_spaceship.broken = 0;
    target_spaceship.x = 20000;
    target_spaceship.y = 10000;
    base.x = 10000;
    base.y = 20000;
}

void test_return_base_spaceship_not_broken(void)
{
    uint8_t result = return_to_base(&spaceship, 1000, command);
    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL_STRING("", command);
}

void test_return_base_spaceship_broken(void)
{
    spaceship.broken = 1;
    uint8_t result = return_to_base(&spaceship, 1000, command);
    TEST_ASSERT_EQUAL(1, result);
    TEST_ASSERT_EQUAL_STRING("MOVE 1 90 1000\n", command);
}

void test_manage_spaceship_radar_follow_target(void)
{

    manage_spaceship_radar(&spaceship, &target_spaceship, 0, 0, command);
    TEST_ASSERT_EQUAL_STRING("MOVE 1 0 2000\n", command);
}

void test_manage_spaceship_attacker_follow_target(void)
{

    manage_spaceship_attacker(&spaceship, &target_spaceship, 0, 0, spaceships, nb_spaceships, &base, command);
    TEST_ASSERT_EQUAL_STRING("MOVE 1 0 3000\n", command);
}

void test_manage_spaceship_attacker_fire(void)
{
    Spaceship_t enemy_spaceship = { .team_id = 1, .ship_id = 3, .broken = 0, .x = 8000, .y = 10000 };
    spaceships[0] = enemy_spaceship;
    nb_spaceships = 1;
    manage_spaceship_attacker(&spaceship, &target_spaceship, 0, 0, spaceships, nb_spaceships, &base, command);
    TEST_ASSERT_EQUAL_STRING("FIRE 1 180\n", command);
}

void test_manage_spaceship_collector_go_to_planet(void)
{
    Planet_t planet = { .planet_id = 1, .x = 0, .y = 10000, .ship_id = 0, .saved = 0 };
    planets[0] = planet;
    nb_planets = 1;
    manage_spaceship_collector(&spaceship, command);
    TEST_ASSERT_EQUAL_STRING("MOVE 1 180 1000\n", command);
}

void test_manage_spaceship_collector_no_planet(void)
{
    manage_spaceship_collector(&spaceship, command);
    TEST_ASSERT_EQUAL_STRING("MOVE 1 0 1000\n", command);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_return_base_spaceship_not_broken);
    RUN_TEST(test_return_base_spaceship_broken);
    RUN_TEST(test_manage_spaceship_radar_follow_target);
    RUN_TEST(test_manage_spaceship_attacker_follow_target);
    RUN_TEST(test_manage_spaceship_attacker_fire);
    RUN_TEST(test_manage_spaceship_collector_go_to_planet);
    RUN_TEST(test_manage_spaceship_collector_no_planet);
    return UNITY_END();
}
