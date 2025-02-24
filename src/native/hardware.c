#include <stdint.h>
#include <stdio.h>

/**
 * @brief convert an integer to a string
 *
 * @param value integer to convert
 * @param str result buffer
 * @param base base of the integer
 * @return char*  string representation of the integer
 */
char* itoa(int value, char* str, int base)
{
    if (base != 10 || value < 0) {
        while (1)
            ;
    }
    if (value == 0) {
        str[0] = '0';
        str[1] = 0;
    } else {
        uint8_t digits[32];
        uint8_t max_power = 0;
        uint8_t i;
        while (value) {
            digits[max_power++] = value % 10;
            value /= 10;
        }
        for (i = 0; i < max_power; i++)
            str[i] = digits[max_power - i - 1] + '0';
        str[max_power] = 0;
    }
    return str;
}

void hardware_init()
{
}
