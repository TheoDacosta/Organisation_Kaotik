#include "os_manager.h"
#include "unity.h"

void test_get_current_time()
{
    uint32_t start_time = get_current_timeMs();

    while (get_current_timeMs() - start_time <= 1000)
        ;

    uint32_t current_time = get_current_timeMs();
    uint32_t elapsed_time = current_time - start_time;

    TEST_ASSERT_GREATER_OR_EQUAL(1000, elapsed_time);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_get_current_time);
    return UNITY_END();
}
