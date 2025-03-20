#include "commands.h"
#include "planet.h"
#include "strategy.h"
#include "trajectory.h"
#include "unity.h"
#include <stdlib.h>

Spaceship_t spaceship[NB_MAX_SPACESHIPS];
// Spaceship_t target_spaceship;
Planet_t planet[NB_MAX_PLANETS];
char command[MAX_COMMAND_SIZE];
Point_t target;

void setUp(void)
{
    nb_planets = 0;
    nb_spaceships = 0;
    Spaceship_t spaceship_1 = { .team_id = 0, .ship_id = 1, .broken = 0, .position = { .x = 10000, .y = 10000 }, .last_radar_time = 0 };
    Spaceship_t spaceship_2 = { .team_id = 0, .ship_id = 6, .broken = 0, .position = { .x = 10000, .y = 10000 }, .last_radar_time = 20000 };
    Spaceship_t target_spaceship = { .team_id = 1, .ship_id = 3, .broken = 0, .position = { .x = 20000, .y = 10000 } };
    Planet_t planet_1 = { .planet_id = 1, .position = { .x = 0, .y = 10000 }, .ship_id = -1, .saved = 0 };
    Planet_t planet_2 = { .planet_id = 1, .position = { .x = 0, .y = 20000 }, .ship_id = 1, .saved = 0 };
    spaceship[0] = spaceship_1;
    spaceship[1] = spaceship_2;
    spaceship[2] = target_spaceship;
    planet[0] = planet_1;
    planet[1] = planet_2;
    base.x = 10000;
    base.y = 20000;
    target.x = 20000;
    target.y = 10000;
}


void test_return_base_spaceship_broken(void)
{
    spaceship[0].broken = 1;
    return_to_base(spaceship, 1000, command);
    TEST_ASSERT_EQUAL_STRING("MOVE 1 90 1000\n", command);
}

void test_manage_spaceship_radar_follow_target(void)
{
    manage_spaceship_radar(spaceship, target, command);
    TEST_ASSERT_EQUAL_STRING("MOVE 1 0 2000\n", command);
}

void test_manage_spaceship_attacker_follow_target(void)
{
    nb_planets = 1;
    manage_spaceship_attacker(spaceship, target, command);
    TEST_ASSERT_EQUAL_STRING("MOVE 1 0 3000\n", command);
}

void test_manage_spaceship_attacker_fire(void)
{
    Spaceship_t enemy_spaceship = { .team_id = 1, .ship_id = 3, .broken = 0, .position = { .x = 8000, .y = 10000 } };
    spaceships[0] = enemy_spaceship;
    nb_spaceships = 1;
    manage_spaceship_attacker(spaceship, target, command);
    TEST_ASSERT_EQUAL_STRING("FIRE 1 180\n", command);
}

void test_manage_spaceship_collector_go_to_planet(void)
{
    manage_spaceship_collector(spaceship, command);
    TEST_ASSERT_EQUAL_STRING("MOVE 1 0 1000\n", command);
}

void test_manage_spaceship_collector_no_planet(void)
{
    manage_spaceship_collector(spaceship, command);
    TEST_ASSERT_EQUAL_STRING("MOVE 1 0 1000\n", command);
}

void test_manage_strategy_can_scan(void)
{
    nb_spaceships = 1;
    manage_spaceship_radar(&spaceship[1], target, command);
    TEST_ASSERT_EQUAL_STRING("RADAR 6\n", command);
}

void test_mannage_planet_collect_return_to_base(void)
{
    nb_planets = 1;
    manage_spaceship_collector(spaceship, command);
    TEST_ASSERT_EQUAL_STRING("MOVE 1 0 1000\n", command);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_return_base_spaceship_broken);
    RUN_TEST(test_manage_spaceship_radar_follow_target);
    RUN_TEST(test_manage_spaceship_attacker_follow_target);
    RUN_TEST(test_manage_spaceship_attacker_fire);
    RUN_TEST(test_manage_spaceship_collector_go_to_planet);
    RUN_TEST(test_manage_spaceship_collector_no_planet);
    RUN_TEST(test_mannage_planet_collect_return_to_base);
    RUN_TEST(test_manage_strategy_can_scan);

    return UNITY_END();
}
