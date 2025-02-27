#include "commands.h"
#include "planet.h"
#include "strategie.h"
#include "unity.h"
#include <stdlib.h>

Planet_t planets[NB_MAX_PLANETS];
uint16_t nb_planets;
void test_manage_collector(void)
{
}

void test_manage_explorer(void)
{
}

void test_manage_attacker(void)
{
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_manage_collector);
    RUN_TEST(test_manage_explorer);
    RUN_TEST(test_manage_attacker);
    return UNITY_END();
}
