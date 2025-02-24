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



int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_create_move_command);
    return UNITY_END();
}
