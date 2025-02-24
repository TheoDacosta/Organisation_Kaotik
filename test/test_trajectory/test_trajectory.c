#include "planet.h"
#include "spaceship.h"
#include "trajectory.h"
#include <unity.h>

void test_get_travel_angle(void)
{

    // Test 1 : Déplacement vers la droite (0°)
    TEST_ASSERT_EQUAL(0, get_travel_angle(100, 100, 200, 100));

    // Test 2 : Déplacement vers le haut (90°)
    TEST_ASSERT_EQUAL(90, get_travel_angle(100, 100, 100, 200));

    // Test 3 : Déplacement en diagonale (315°)
    TEST_ASSERT_EQUAL(315, get_travel_angle(100, 200, 200, 100));
}

void test_calculate_distance(void)
{
    // Test 1: Cas simple, distance entre (0, 0) et (3, 4)
    float result1 = calculate_distance(0, 0, 3, 4);

    // Test 2: Cas où les deux points sont identiques (distance = 0)
    float result2 = calculate_distance(2, 3, 2, 3);

    TEST_ASSERT_FLOAT_WITHIN(0.1, 5.0, result1);
    TEST_ASSERT_FLOAT_WITHIN(0.1, 0.0, result2);
}

void test_determine_target_planets(void)
{
    // Arrange
    Spaceship_t collector1 = { .ship_id = 10, .x = 1000, .y = 2000 };
    Spaceship_t collector2 = { .ship_id = 20, .x = 3000, .y = 4000 };

    Planet_t planets[3] = {
        { .planet_id = 0, .x = 800, .y = 1800, .saved = 0 }, // Planète 0 (proche de collector1)
        { .planet_id = 1, .x = 3200, .y = 3900, .saved = 0 }, // Planète 1 (proche de collector2)
        { .planet_id = 2, .x = 2500, .y = 2500, .saved = 0 } // Planète 2 (potentiellement assignée)
    };

    Planet_t target_planet1;
    Planet_t target_planet2;

    // Act
    determine_target_planets(collector1, collector2, planets, 3, &target_planet1, &target_planet2);

    // Assert
    TEST_ASSERT_EQUAL(0, target_planet1.planet_id); // Collector 1 devrait cibler la planète 0
    TEST_ASSERT_EQUAL(1, target_planet2.planet_id); // Collector 2 devrait cibler la planète 1
}

void test_get_target_angle(void)
{

    Spaceship_t Defender = { .team_id = 1, .ship_id = 9, .x = 11, .y = 12 };

    Spaceship_t spaceship[NB_MAX_SPACESHIPS] = {
        { .team_id = 0, .ship_id = 8, .x = 10, .y = 10 },
        { .team_id = 1, .ship_id = 9, .x = 11, .y = 12 },
        { .team_id = 4, .ship_id = 2, .x = 50, .y = 100 },
        { .team_id = 5, .ship_id = 1, .x = 70, .y = 150 }
    };

    uint16_t angle = get_target_angle(Defender, spaceship);
    uint16_t target_angle = get_travel_angle(Defender.x, Defender.y, spaceship[1].x, spaceship[1].y);

    TEST_ASSERT_EQUAL(target_angle, angle);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_get_travel_angle);
    RUN_TEST(test_calculate_distance);
    RUN_TEST(test_determine_target_planets);
    RUN_TEST(test_get_target_angle);
    return UNITY_END();
}
