#ifndef HARDWARE_H_
#define HARDWARE_H_

#include <stdlib.h>

char* itoa(int value, char* str, int base); /* only base=10 and value>=0 is supported */
void hardware_init(void);
int puts(const char*);
char* gets(char* s);

#endif // HARDWARE_H_
