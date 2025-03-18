#include "string.h"

uint16_t len(const char* str)
{
    uint16_t length = 0;
    while (*str != '\0') {
        length++;
        str++;
    }
    return length;
}

void str_copy(const char* src, char* dest)
{
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

void add_endline(const char* str, char* dest)
{
    while (*str != '\0') {
        *dest = *str;
        dest++;
        str++;
    }
    *dest = '\n';
    dest++;
    *dest = '\0';
}
