#include "parsing.h"
#include <stdint.h>
#include <unity.h>

void setUp(void)
{
    parsing_mutex = create_mutex();
}

void test_parsing()
{

    parse_response("P 12 3217 4321 31 0,S 1 31 3217 4321 0,B 3217 4321");

    TEST_ASSERT_EQUAL(1, nb_planets);
    TEST_ASSERT_EQUAL(12, planets[0].planet_id);
    TEST_ASSERT_EQUAL(3217, planets[0].x);
    TEST_ASSERT_EQUAL(4321, planets[0].y);
    TEST_ASSERT_EQUAL(31, planets[0].ship_id);
    TEST_ASSERT_EQUAL(0, planets[0].saved);

    TEST_ASSERT_EQUAL(1, nb_spaceships);
    TEST_ASSERT_EQUAL(1, spaceships[0].team_id);
    TEST_ASSERT_EQUAL(31, spaceships[0].ship_id);
    TEST_ASSERT_EQUAL(3217, spaceships[0].x);
    TEST_ASSERT_EQUAL(4321, spaceships[0].y);
    TEST_ASSERT_EQUAL(0, spaceships[0].broken);

    TEST_ASSERT_EQUAL(3217, base.x);
    TEST_ASSERT_EQUAL(4321, base.y);
}

void test_parsing_keep_focus()
{
    planets[0] = (Planet_t) { .planet_id = 12, .saved = 0, .x = 30, .y = 400, .focus = 1 };
    planets[1] = (Planet_t) { .planet_id = 13, .saved = 0, .x = 0, .y = 0, .focus = 0 };
    planets[2] = (Planet_t) { .planet_id = 14, .saved = 0, .x = 30, .y = 40 };
    nb_planets = 3;

    parse_response("P 12 3217 4321 31 0,S 1 31 3217 4321 0,B 3217 4321");

    TEST_ASSERT_EQUAL(1, nb_planets);
    TEST_ASSERT_EQUAL(12, planets[0].planet_id);
    TEST_ASSERT_EQUAL(1, planets[0].focus);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_parsing);
    RUN_TEST(test_parsing_keep_focus);
    return UNITY_END();
}
