#include "commands.h"
#include "planet.h"
#include "strategy.h"
#include "trajectory.h"
#include "unity.h"
#include <stdlib.h>

Planet_t planets[NB_MAX_PLANETS];
uint16_t nb_planets;
Spaceship_t spaceships[NB_MAX_SPACESHIPS];
uint16_t nb_spaceships = 0;
Spaceship_t spaceship;
Spaceship_t target_spaceship;
Base_t base = { .x = 10000, .y = 20000 };
char command[MAX_COMMAND_SIZE];

void setUp(void)
{
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
}

void test_manage_spaceship_radar_is_dead(void)
{
    spaceship.broken = 1;
    manage_spaceship_radar(&spaceship, &target_spaceship, 0, 0, &base, command);
    TEST_ASSERT_EQUAL_STRING("MOVE 1 90 2000\n", command);
}

void test_manage_spaceship_radar_is_not_dead(void)
{

    manage_spaceship_radar(&spaceship, &target_spaceship, 0, 0, &base, command);
    TEST_ASSERT_EQUAL_STRING("MOVE 1 0 2000\n", command);
}

void test_manage_spaceship_attacker_dead(void)
{
    spaceship.broken = 1;
    manage_spaceship_attacker(&spaceship, &target_spaceship, 0, 0, spaceships, nb_spaceships, &base, command);
    TEST_ASSERT_EQUAL_STRING("MOVE 1 90 3000\n", command);
}

void test_manage_spaceship_attacker_is_not_dead(void)
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

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_manage_spaceship_radar_is_dead);
    RUN_TEST(test_manage_spaceship_radar_is_not_dead);
    RUN_TEST(test_manage_spaceship_attacker_is_not_dead);
    RUN_TEST(test_manage_spaceship_attacker_dead);
    RUN_TEST(test_manage_spaceship_attacker_fire);
    return UNITY_END();
}
