#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "data_splitter.h"
#include <unity.h>

// Test de decoupage des donnees
void test_data_splitter()
{
    uint16_t count;
    char *stock_data[10];

    dataSplitter(stock_data, "test1,donnee stocke dit vrais et ok,dating,donnee recu", ',', &count);

    TEST_ASSERT_EQUAL(4, count);
    TEST_ASSERT_EQUAL_STRING("test1", stock_data[0]);

    TEST_ASSERT_EQUAL_STRING("donnee stocke dit vrais et ok", stock_data[1]);
    TEST_ASSERT_EQUAL_STRING("dating", stock_data[2]);

    TEST_ASSERT_EQUAL_STRING("donnee recu", stock_data[3]);

    for (uint16_t i = 0; i < count; i++)
    {
        free(stock_data[i]);
    }
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_data_splitter);
    return UNITY_END();
}