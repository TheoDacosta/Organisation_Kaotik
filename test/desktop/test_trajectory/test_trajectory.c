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
    // Initialisation des collecteurs
    Spaceship_t collector1 = { .ship_id = 10, .x = 1000, .y = 2000 }; // ID 10, position (1000, 2000)
    Spaceship_t collector2 = { .ship_id = 20, .x = 3000, .y = 4000 }; // ID 20, position (3000, 4000)

    // Création de planètes
    Planet_t planets[3] = {
        { .planet_id = 0, .x = 500, .y = 1800, .saved = 0 }, // Planète 0 (proche de collector1)
        { .planet_id = 1, .x = 3200, .y = 3900, .saved = 0 }, // Planète 1 (proche de collector2)
        { .planet_id = 2, .x = 2500, .y = 2500, .saved = 0 } // Planète 2 (potentiellement assignée)
    };

    uint16_t results[2][2] = { 0 };

    determine_target_planets(collector1, collector2, planets, 3, results);

    // Vérifications
    TEST_ASSERT_EQUAL(10, results[0][0]); // Collector 1 ID
    TEST_ASSERT_EQUAL(0, results[0][1]); // Devrait cibler la planète 0

    TEST_ASSERT_EQUAL(20, results[1][0]); // Collector 2 ID
    TEST_ASSERT_EQUAL(1, results[1][1]); // Devrait cibler la planète 1
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_get_travel_angle);
    RUN_TEST(test_calculate_distance);
    RUN_TEST(test_determine_target_planets);
    return UNITY_END();
}
