#include "planet.h"
#include "spaceship.h"
#include "trajectory.h"
#include <unity.h>

void test_get_angle(void)
{

    // Test 1 : Déplacement vers la droite (0°)
    TEST_ASSERT_EQUAL(0, get_angle(100, 100, 200, 100));

    // Test 2 : Déplacement vers le haut (90°)
    TEST_ASSERT_EQUAL(90, get_angle(100, 100, 100, 200));

    // Test 3 : Déplacement en diagonale (315°)
    TEST_ASSERT_EQUAL(315, get_angle(100, 200, 200, 100));
}

void test_calculate_distance_0(void)
{
    u_int16_t result = get_distance(2, 3, 2, 3);

    TEST_ASSERT_EQUAL(0, result);
}

void test_calculate_distance_positive_substract_result(void)
{
    u_int16_t result = get_distance(10, 10, 20, 20);

    TEST_ASSERT_EQUAL(14, result);
}

void test_calculate_distance_negative_substract_result(void)
{
    u_int16_t result = get_distance(20, 20, 10, 10);

    TEST_ASSERT_EQUAL(14, result);
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
    uint16_t target_angle = get_angle(Defender.x, Defender.y, spaceship[1].x, spaceship[1].y);

    TEST_ASSERT_EQUAL(target_angle, angle);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_get_angle);
    RUN_TEST(test_calculate_distance_positive_substract_result);
    RUN_TEST(test_calculate_distance_negative_substract_result);
    RUN_TEST(test_get_target_angle);
    return UNITY_END();
}
