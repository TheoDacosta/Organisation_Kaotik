#ifndef HARDWARE_H_
#define HARDWARE_H_

#include <stdio.h>
#include <stdlib.h>

char* itoa(int value, char* str, int base); /* only base=10 and value>=0 is supported */
void hardware_init(void);

#endif // HARDWARE_H_
