#include "hello_world.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unity.h>

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

void test_hello_world(void)
{
    char res[100];
    hello_world(res);
    TEST_ASSERT_EQUAL_STRING("Hello World\n", res);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_hello_world);
    return UNITY_END();
}
