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
    RUN_TEST(test_get_target_angle);
    return UNITY_END();
}
