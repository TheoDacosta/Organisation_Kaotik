#ifndef DATA_SPLITTER_H

#include <stdint.h>
#include <stdio.h>

#define MAX_DATA 50

typedef struct dataRadar {
    char data[25];

} TabDataRadar;

// Decoupage des donnees
void dataSplitter(char** stockData, const char* data, const char delimiter, uint16_t* count);

#endif // DATA_SPLITTER_H
