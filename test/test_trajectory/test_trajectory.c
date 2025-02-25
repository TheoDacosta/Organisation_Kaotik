#include "base.h"
#include "planet.h"
#include "spaceship.h"
#include "trajectory.h"
#include <unity.h>

Spaceship_t spaceships[NB_MAX_SPACESHIPS];
uint16_t nb_spaceships = 0;
Planet_t planets[NB_MAX_PLANETS];
uint16_t nb_planets;

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
    uint16_t result = get_distance(2, 3, 2, 3);

    TEST_ASSERT_EQUAL(0, result);
}

void test_calculate_distance_positive_substract_result(void)
{
    uint16_t result = get_distance(10, 10, 20, 20);

    TEST_ASSERT_EQUAL(14, result);
}

void test_calculate_distance_negative_substract_result(void)
{
    uint16_t result = get_distance(20, 20, 10, 10);

    TEST_ASSERT_EQUAL(14, result);
}

void test_get_target_angle(void)
{

    Spaceship_t Defender = { .team_id = 0, .ship_id = 9, .x = 11, .y = 12 };

    Spaceship_t spaceships[NB_MAX_SPACESHIPS] = {
        { .team_id = 0, .ship_id = 9, .x = 11, .y = 12 },
        { .team_id = 4, .ship_id = 2, .x = 50, .y = 100 },
        { .team_id = 5, .ship_id = 1, .x = 70, .y = 150 }
    };

    uint16_t target_angle = get_target_angle(Defender, spaceships);

    TEST_ASSERT_EQUAL(66, target_angle);
}

void test_deplacement_vaisseau_broken(void)
{
    Spaceship_t spaceships[NB_MAX_SPACESHIPS] = { 0 };
    Base_t base = { 50, 50 };
    spaceships[2].x = 100;
    spaceships[2].y = 100;
    spaceships[2].broken = 1;
    uint16_t angle = deplace_space_from_an_other(2, 0, spaceships, &base);
    TEST_ASSERT_EQUAL(get_angle(100, 100, 50, 50), angle);
}

void test_deplacement_vaisseau_suit_autre(void)
{
    Spaceship_t spaceships[NB_MAX_SPACESHIPS] = { 0 };
    Base_t base = { 50, 50 };
    spaceships[1].x = 100;
    spaceships[1].y = 100;
    spaceships[1].broken = 0;
    spaceships[3].x = 200;
    spaceships[3].y = 200;
    spaceships[3].broken = 0;
    uint16_t angle = deplace_space_from_an_other(1, 3, spaceships, &base);
    TEST_ASSERT_EQUAL(get_angle(100, 100, 200, 200), angle);
}

void test_find_nearest_planet(void)
{
    // Création des données de test 
    char* data = "P 12 30 400 0 0,P 13 0 0 0 0,P 14 400 400 0 0";
    parse_planet(data, planets, &nb_planets);

    data = "S 1 31 300 300 0";
    parse_spaceship(data, spaceships, &nb_spaceships);

    Planet_t* nearest_planet = NULL;

    
    find_nearest_planet(spaceships, planets, &nearest_planet);

    
    TEST_ASSERT_NOT_NULL(nearest_planet);
    TEST_ASSERT_EQUAL(12, nearest_planet->planet_id); 
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_get_angle);
    RUN_TEST(test_calculate_distance_0);
    RUN_TEST(test_calculate_distance_positive_substract_result);
    RUN_TEST(test_calculate_distance_negative_substract_result);
    RUN_TEST(test_get_target_angle);
    RUN_TEST(test_deplacement_vaisseau_broken);
    RUN_TEST(test_deplacement_vaisseau_suit_autre);
    RUN_TEST(test_find_nearest_planet);
    return UNITY_END();
}
