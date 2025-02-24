#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unity.h>


void test_create_move_command(void)
{
    char buffer[MAX_COMMAND_SIZE];
    create_move_command(1, 90, 1000, buffer);
    TEST_ASSERT_EQUAL_STRING("MOVE 1 90 1000\n", buffer);

}

void test_create_fire_command(void)
{
    char buffer[MAX_COMMAND_SIZE];
    create_fire_command(1, 90, buffer);
    TEST_ASSERT_EQUAL_STRING("FIRE 1 90\n", buffer);
}

void test_create_radar_command(void)
{
    char buffer[MAX_COMMAND_SIZE];
    create_radar_command(1, buffer);
    TEST_ASSERT_EQUAL_STRING("RADAR 1\n", buffer);
}


void test_verif_angle(void)
{
    TEST_ASSERT_TRUE(is_valid_angle(0));
    TEST_ASSERT_TRUE(is_valid_angle(90));
    TEST_ASSERT_TRUE(is_valid_angle(180));
    TEST_ASSERT_TRUE(is_valid_angle(270));
    TEST_ASSERT_TRUE(is_valid_angle(359));
    TEST_ASSERT_FALSE(is_valid_angle(360));
    TEST_ASSERT_FALSE(is_valid_angle(361));
    TEST_ASSERT_FALSE(is_valid_angle(400));
    TEST_ASSERT_FALSE(is_valid_angle(1000));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_create_move_command);
    RUN_TEST(test_create_fire_command);
    RUN_TEST(test_create_radar_command);
    RUN_TEST(test_verif_angle);
    return UNITY_END();
}
