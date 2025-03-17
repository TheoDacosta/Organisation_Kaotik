#include "base.h"
#include "planet.h"
#include "spaceship.h"
#include "trajectory.h"
#include <unity.h>

void test_get_angle_right(void)
{
    Point_t start_point = { .x = 100, .y = 100 };
    Point_t end_point = { .x = 200, .y = 100 };
    TEST_ASSERT_EQUAL(0, get_angle(start_point, end_point));
}

void test_get_angle_up(void)
{
    Point_t start_point = { .x = 100, .y = 100 };
    Point_t end_point = { .x = 100, .y = 200 };
    TEST_ASSERT_EQUAL(90, get_angle(start_point, end_point));
}

void test_get_angle_up_right(void)
{
    Point_t start_point = { .x = 100, .y = 200 };
    Point_t end_point = { .x = 200, .y = 100 };
    TEST_ASSERT_EQUAL(315, get_angle(start_point, end_point));
}

void test_calculate_distance_0(void)
{
    Point_t point1 = { .x = 2, .y = 3 };
    Point_t point2 = { .x = 2, .y = 3 };
    uint16_t result = get_distance(point1, point2);

    TEST_ASSERT_EQUAL(0, result);
}

void test_calculate_distance_positive_substract_result(void)
{
    Point_t point1 = { .x = 10, .y = 10 };
    Point_t point2 = { .x = 20, .y = 20 };
    uint16_t result = get_distance(point1, point2);

    TEST_ASSERT_EQUAL(14, result);
}

void test_calculate_distance_negative_substract_result(void)
{
    Point_t point1 = { .x = 20, .y = 20 };
    Point_t point2 = { .x = 10, .y = 10 };
    uint16_t result = get_distance(point1, point2);

    TEST_ASSERT_EQUAL(14, result);
}

void test_get_target_angle(void)
{

    Spaceship_t defender = { .team_id = 0, .ship_id = 9, .position = { .x = 11, .y = 12 } };

    Spaceship_t spaceships[NB_MAX_SPACESHIPS] = {
        { .team_id = 0, .ship_id = 9, .position = { .x = 11, .y = 12 } },
        { .team_id = 4, .ship_id = 2, .position = { .x = 50, .y = 100 } },
        { .team_id = 5, .ship_id = 1, .position = { .x = 70, .y = 150 } }
    };

    uint16_t target_angle = get_target_angle(&defender, spaceships, 3);
    TEST_ASSERT_EQUAL(66, target_angle);
}

void test_find_nearest_planet(void)
{
    // Création des données de test
    Planet_t planets[NB_MAX_PLANETS] = {
        { .planet_id = 12, .saved = 0, .focus = 0, .position = { .x = 30, .y = 400 }, .ship_id = -1 },
        { .planet_id = 13, .saved = 0, .focus = 0, .position = { .x = 0, .y = 0 }, .ship_id = -1 },
        { .planet_id = 14, .saved = 0, .focus = 0, .position = { .x = 30, .y = 40 }, .ship_id = -1 }
    };

    Spaceship_t spaceship = { .position = { .x = 40, .y = 500 }, .team_id = 0, .ship_id = 2, .broken = 0 };

    Planet_t* nearest_planet = find_nearest_planet(&spaceship, planets, 3);

    TEST_ASSERT_NOT_NULL(nearest_planet);
    TEST_ASSERT_EQUAL(12, nearest_planet->planet_id); // Le plus proche est la planète 12 (30, 400)
}

void test_find_nearest_unsaved_planet(void)
{
    // Création des données de test
    Planet_t planets[NB_MAX_PLANETS] = {
        { .planet_id = 12, .saved = 1, .focus = 0, .position = { .x = 30, .y = 400 }, .ship_id = -1 },
        { .planet_id = 13, .saved = 0, .focus = 0, .position = { .x = 0, .y = 0 }, .ship_id = -1 },
        { .planet_id = 14, .saved = 0, .focus = 0, .position = { .x = 30, .y = 40 }, .ship_id = -1 }
    };

    Spaceship_t spaceship = { .position = { .x = 40, .y = 500 }, .team_id = 0, .ship_id = 2, .broken = 0 };

    Planet_t* nearest_planet = find_nearest_planet(&spaceship, planets, 3);

    TEST_ASSERT_NOT_NULL(nearest_planet);
    TEST_ASSERT_EQUAL(14, nearest_planet->planet_id); // Le plus proche est la planète 14 (30, 40)
}

void test_find_nearest_untaken_planet(void)
{
    // Création des données de test
    Planet_t planets[NB_MAX_PLANETS] = {
        { .planet_id = 12, .saved = 0, .focus = 0, .position = { .x = 30, .y = 400 }, .ship_id = 5 },
        { .planet_id = 13, .saved = 0, .focus = 0, .position = { .x = 0, .y = 0 }, .ship_id = -1 },
        { .planet_id = 14, .saved = 0, .focus = 0, .position = { .x = 30, .y = 40 }, .ship_id = -1 }
    };

    Spaceship_t spaceship = { .position = { .x = 40, .y = 500 }, .team_id = 0, .ship_id = 2, .broken = 0 };

    Planet_t* nearest_planet = find_nearest_planet(&spaceship, planets, 3);

    TEST_ASSERT_NOT_NULL(nearest_planet);
    TEST_ASSERT_EQUAL(14, nearest_planet->planet_id); // Le plus proche est la planète 14 (30, 40)
}

void test_find_nearest_unfocus_planet(void)
{
    // Création des données de test
    Planet_t planets[NB_MAX_PLANETS] = {
        { .planet_id = 12, .saved = 0, .focus = 3, .position = { .x = 30, .y = 400 }, .ship_id = -1 },
        { .planet_id = 13, .saved = 0, .focus = 0, .position = { .x = 0, .y = 0 }, .ship_id = -1 },
        { .planet_id = 14, .saved = 0, .focus = 2, .position = { .x = 30, .y = 40 }, .ship_id = -1 }
    };

    Spaceship_t spaceship = { .position = { .x = 40, .y = 500 }, .team_id = 0, .ship_id = 2, .broken = 0 };

    Planet_t* nearest_planet = find_nearest_planet(&spaceship, planets, 3);

    TEST_ASSERT_NOT_NULL(nearest_planet);
    TEST_ASSERT_EQUAL(14, nearest_planet->planet_id); // Le plus proche est la planète 14 (30, 40)
}

void test_get_point_with_offset(void)
{
    Point_t point = { .x = 10, .y = 20 };
    Point_t point_with_offset;
    get_point_with_offset(point, 5, 10, &point_with_offset);
    // Vérifications
    TEST_ASSERT_EQUAL(15, point_with_offset.x);
    TEST_ASSERT_EQUAL(30, point_with_offset.y);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_get_angle_right);
    RUN_TEST(test_get_angle_up);
    RUN_TEST(test_get_angle_up_right);
    RUN_TEST(test_calculate_distance_0);
    RUN_TEST(test_calculate_distance_positive_substract_result);
    RUN_TEST(test_calculate_distance_negative_substract_result);
    RUN_TEST(test_find_nearest_planet);
    RUN_TEST(test_find_nearest_unsaved_planet);
    RUN_TEST(test_find_nearest_untaken_planet);
    RUN_TEST(test_find_nearest_unfocus_planet);
    RUN_TEST(test_get_point_with_offset);
    return UNITY_END();
}
