#include "commands.h"
#include "planet.h"
#include "stdio.h"
#include "strategie.h"
#include "trajectory.h"
#include "unity.h"
#include <stdlib.h>

Planet_t planets[NB_MAX_PLANETS];
uint16_t nb_planets;

void test_manage_spaceship_radar_is_dead(void)
{
    Spaceship_t spaceships[NB_MAX_SPACESHIPS] = { { .broken = 1, .x = 0, .y = 0 } };
    Base_t base = { .x = 10, .y = 10 };
    char cmd_1[MAX_COMMAND_SIZE];
    manage_spaceship_radar(0, 1, spaceships, &base, cmd_1);
    TEST_ASSERT_EQUAL_STRING("MOVE 0 45 2000\n", cmd_1);
}

void test_manage_spaceship_radar_is_not_dead(void)
{
    Spaceship_t spaceships[NB_MAX_SPACESHIPS] = { 0 };
    Base_t base = { 0 };
    char execpt[MAX_COMMAND_SIZE];
    char cmd_1[MAX_COMMAND_SIZE];
    spaceships[0].broken = 0;
    spaceships[0].x = 0;
    spaceships[0].y = 0;
    base.x = 10;
    base.y = 10;
    // TEST A MODIFIER CAR  LA FONCTION N'EST PAS CONFORME DOIS REROURNER UN CHAINE DE CARTACTERE
    TEST_ASSERT_EQUAL(10, 10);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_manage_spaceship_radar_is_dead);
    return UNITY_END();
}
