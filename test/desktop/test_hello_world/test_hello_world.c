#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unity.h>

void hello_world(char* res)
{
    char hw[13] = "Hello World\n";
    char c = hw[0];
    int i = 0;
    while (c != '\0') {
        res[i] = c;
        i++;
        c = hw[i];
    }
    res[i] = '\0';
}

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
