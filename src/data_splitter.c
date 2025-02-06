#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "data_splitter.h"

// Decoupage des donnees
void dataSplitter(char **stockData, const char *data, const char delimiter, uint16_t *count)
{
    uint16_t i = 0;
    *count = 0;
    char caractereFinLigne = '\0';

    uint16_t post = 0;
    char tempStockData[MAX_DATA];

    for (i = 0; data[i] != caractereFinLigne; i++)
    {
        if (data[i] == delimiter)
        {
            tempStockData[post] = caractereFinLigne;
            stockData[*count] = strdup(tempStockData);

            (*count)++;
            post = caractereFinLigne;
            tempStockData[0] = caractereFinLigne;
        }
        else
        {
            tempStockData[post] = data[i];
            post++;
        }
    }

    tempStockData[post] = caractereFinLigne;
    stockData[*count] = strdup(tempStockData);
    (*count)++;
}