#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULUS (1 << 31)
#define MULTIPLIER (1103515245)
#define INCREMENT (12345)

static unsigned int prng;

void srand(unsigned int seed) { prng = seed; }

int rand(void)
{
    prng = (MULTIPLIER * prng + INCREMENT) % MODULUS;
    return (int)(prng & 0x7FFFFFFF);
}

int putchar(int c)
{
    return fputc(c, stdout);
}

int puts(const char* text)
{
    return fputs(text, stdout), fputc('\n', stdout);
}

char* my_gets(char* str, int size)
{
    if (fgets(str, size, stdin)) {
        size_t len = strlen(str);
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }
        return str;
    }
    return NULL;
}

char* itoa(int value, char* str, int base)
{
    if (base < 2 || base > 36) {
        return NULL;
    }
    char *ptr = str, *ptr1 = str, tmp_char;
    int tmp_value;

    if (value < 0 && base == 10) {
        *ptr++ = '-';
        value = -value;
    }

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[tmp_value - value * base];
    } while (value);

    *ptr-- = '\0';

    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }
    return str;
}

void hardware_init()
{
}
