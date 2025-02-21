#include "parsing.h"
#include <stdint.h>
#include <unity.h>

char stock_data[3][150];
uint8_t count = 0;

void parse_data_test_func(char* data, void* argument)
{
    uint16_t i = 0;
    for (i = 0; data[i] != '\0'; i++) {
        stock_data[count][i] = data[i];
    }
    stock_data[count][i] = '\0';
    count++;
}

void test_parsing()
{
    parse_response("P {planet_id} {abscissa} {ordinate} {ship_id} {saved},S {team} {ship_id} {abscissa} {ordinate} {broken},B {abscissa} {ordinate}", parse_data_test_func, NULL);

    TEST_ASSERT_EQUAL(3, count);
    TEST_ASSERT_EQUAL_STRING("P {planet_id} {abscissa} {ordinate} {ship_id} {saved}", stock_data[0]);

    TEST_ASSERT_EQUAL_STRING("S {team} {ship_id} {abscissa} {ordinate} {broken}", stock_data[1]);
    TEST_ASSERT_EQUAL_STRING("B {abscissa} {ordinate}", stock_data[2]);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_parsing);
    return UNITY_END();
}
