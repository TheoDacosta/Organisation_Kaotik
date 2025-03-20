#include "string.h"
#include "unity.h"

void test_len()
{
    char* str = "Hello";
    TEST_ASSERT_EQUAL(5, len(str));
}

void test_len_0()
{
    char* str = "";
    TEST_ASSERT_EQUAL(0, len(str));
}

void test_str_copy()
{
    char* src = "Hello";
    char dest[6];
    str_copy(src, dest, 6);
    TEST_ASSERT_EQUAL_STRING("Hello", dest);
}

void test_str_copy_cut()
{
    char* src = "Hello";
    char dest[4];
    str_copy(src, dest, 4);
    TEST_ASSERT_EQUAL_STRING("Hel", dest);
}

void test_add_endline()
{
    char* str = "Hello";
    char dest[7];
    add_endline(str, dest, 7);
    TEST_ASSERT_EQUAL_STRING("Hello\n", dest);
}

void test_add_endline_cut()
{
    char* str = "Hello";
    char dest[4];
    add_endline(str, dest, 4);
    TEST_ASSERT_EQUAL_STRING("He\n", dest);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_len);
    RUN_TEST(test_len_0);
    RUN_TEST(test_str_copy);
    RUN_TEST(test_str_copy_cut);
    RUN_TEST(test_add_endline);
    RUN_TEST(test_add_endline_cut);
    return UNITY_END();
}
