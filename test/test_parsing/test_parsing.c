#include "parsing.h"
#include <stdint.h>
#include <unity.h>

void setUp(void)
{
    response_mutex = create_mutex();
}

void test_parsing()
{

    parse_response("P 12 3217 4321 31 0,S 1 31 3217 4321 0,B 3217 4321");

    TEST_ASSERT_EQUAL(1, nb_planets);
    TEST_ASSERT_EQUAL(12, planets[0].planet_id);
    TEST_ASSERT_EQUAL(3217, planets[0].position.x);
    TEST_ASSERT_EQUAL(4321, planets[0].position.y);
    TEST_ASSERT_EQUAL(31, planets[0].ship_id);
    TEST_ASSERT_EQUAL(0, planets[0].saved);

    TEST_ASSERT_EQUAL(1, nb_spaceships);
    TEST_ASSERT_EQUAL(1, spaceships[0].team_id);
    TEST_ASSERT_EQUAL(31, spaceships[0].ship_id);
    TEST_ASSERT_EQUAL(3217, spaceships[0].position.x);
    TEST_ASSERT_EQUAL(4321, spaceships[0].position.y);
    TEST_ASSERT_EQUAL(0, spaceships[0].broken);

    TEST_ASSERT_EQUAL(3217, base.x);
    TEST_ASSERT_EQUAL(4321, base.y);
}

void test_parsing_keep_planets_infos()
{
    planets[0] = (Planet_t) { .planet_id = 12, .saved = 0, .position = { .x = 30, .y = 40 }, .focus = 1 };
    nb_planets = 1;

    parse_response("P 12 3217 4321 31 0,S 1 31 3217 4321 0,B 3217 4321");

    TEST_ASSERT_EQUAL(1, nb_planets);
    TEST_ASSERT_EQUAL(12, planets[0].planet_id);
    TEST_ASSERT_EQUAL(1, planets[0].focus);
}

void test_parsing_keep_spaceships_infos()
{
    spaceships[0] = (Spaceship_t) { .team_id = 0, .ship_id = 31, .position = { .x = 3217, .y = 4321 }, .broken = 0, .last_shoot_time = 1000, .last_radar_time = 500 };
    nb_spaceships = 1;

    parse_response("P 12 3217 4321 31 0,S 0 31 3217 4321 0,B 3217 4321");

    TEST_ASSERT_EQUAL(1, nb_spaceships);
    TEST_ASSERT_EQUAL(0, spaceships[0].team_id);
    TEST_ASSERT_EQUAL(31, spaceships[0].ship_id);
    TEST_ASSERT_EQUAL(1000, spaceships[0].last_shoot_time);
    TEST_ASSERT_EQUAL(500, spaceships[0].last_radar_time);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_parsing);
    RUN_TEST(test_parsing_keep_planets_infos);
    RUN_TEST(test_parsing_keep_spaceships_infos);
    return UNITY_END();
}
