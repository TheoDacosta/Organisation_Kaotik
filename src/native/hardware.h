#ifndef HARDWARE_H_
#define HARDWARE_H_

#include <stdio.h>

void srand(unsigned int seed);
int rand(void);
int putchar(int c);
int puts(const char* text);
char* my_gets(char* str, int size);
char* itoa(int value, char* str, int base);
void hardware_init(void);


#endif // HARDWARE_H_
