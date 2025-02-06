#include "hello_world.h"

void hello_world(char* res)
{
    char hw[13] = "Hello World\n";
    char c = hw[0];
    int i = 0;
    while (c != '\0') {
        res[i] = c;
        i++;
        c = hw[i];
    }
    res[i] = '\0';
}
