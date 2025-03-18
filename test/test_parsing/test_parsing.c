#include "parsing.h"
#include <stdint.h>
#include <unity.h>

void setUp(void)
{
    parsing_mutex = create_mutex();
    Planet_t planet = { .planet_id = 15, .saved = 0, .position = { .x = 30, .y = 40 } };
    planets[0] = planet;
    nb_planets = 3;
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

void test_parsing_keep_focus()
{

    parse_response("P 12 3217 4321 31 0,S 1 31 3217 4321 0,B 3217 4321");

    TEST_ASSERT_EQUAL(1, nb_planets);
    TEST_ASSERT_EQUAL(12, planets[0].planet_id);
    TEST_ASSERT_EQUAL(0, planets[0].focus);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_parsing);
    RUN_TEST(test_parsing_keep_focus);
    return UNITY_END();
}
