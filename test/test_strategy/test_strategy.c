#include "commands.h"
#include "planet.h"
#include "strategy.h"
#include "trajectory.h"
#include "unity.h"
#include <stdlib.h>

Planet_t planets[NB_MAX_PLANETS];
uint16_t nb_planets;

void test_manage_spaceship_radar_is_dead(void)
{
    Spaceship_t spaceships = { .broken = 1, .x = 0, .y = 0 };
    Spaceship_t spaceships_ref = { .broken = 1, .x = 0, .y = 0 };
    Base_t base = { .x = 10, .y = 10 };
    char cmd_1[MAX_COMMAND_SIZE];
    manage_spaceship_radar(&spaceships, &spaceships_ref, &base, cmd_1);
    TEST_ASSERT_EQUAL_STRING("MOVE 0 45 2000\n", cmd_1);
}

void test_manage_spaceship_radar_is_not_dead(void)
{
    Spaceship_t spaceships = { .broken = 0, .x = 0, .y = 0 };
    Spaceship_t spaceships_ref = { .broken = 0, .x = 0, .y = 0 };
    Base_t base = { .x = 10, .y = 10 };
    char cmd_1[MAX_COMMAND_SIZE];
    manage_spaceship_radar(&spaceships, &spaceships_ref, &base, cmd_1);
    TEST_ASSERT_EQUAL_STRING("MOVE 0 0 2000\n", cmd_1);
}

void test_manage_spaceship_attacker_is_not_dead(void)
{
    Spaceship_t spaceships = { .broken = 0, .x = 0, .y = 0 };
    Spaceship_t spaceships_ref = { .broken = 0, .x = 0, .y = 0 };
    Base_t base = { .x = 10, .y = 10 };
    char cmd_1[MAX_COMMAND_SIZE];
    manage_spaceship_radar(&spaceships, &spaceships_ref, &base, cmd_1);
    TEST_ASSERT_EQUAL_STRING("MOVE 0 0 2000\n", cmd_1);
}

void test_manage_spaceship_attacker_dead(void)
{
    Spaceship_t spaceships = { .broken = 1, .x = 0, .y = 0 };
    Spaceship_t spaceships_ref = { .broken = 1, .x = 0, .y = 0 };
    Base_t base = { .x = 10, .y = 10 };
    char cmd_1[MAX_COMMAND_SIZE];
    manage_spaceship_radar(&spaceships, &spaceships_ref, &base, cmd_1);
    TEST_ASSERT_EQUAL_STRING("MOVE 0 45 2000\n", cmd_1);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_manage_spaceship_radar_is_dead);
    RUN_TEST(test_manage_spaceship_radar_is_not_dead);
    RUN_TEST(test_manage_spaceship_attacker_is_not_dead);
    RUN_TEST(test_manage_spaceship_attacker_dead);
    return UNITY_END();
}
