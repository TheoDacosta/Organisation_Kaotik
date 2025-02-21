#include "parsing.h"

void parse_response(const char* response, ParseFunc_t parse_data_func, void* parse_data_func_arg)
{
    uint16_t pos = 0;
    const char delimiter = ',';
    char token[MAX_DATA_SIZE];
    for (uint16_t i = 0; response[i] != '\0'; i++) {
        if (response[i] == delimiter) {
            token[pos] = '\0';
            parse_data_func(token, parse_data_func_arg);
            pos = 0;
        } else {
            token[pos] = response[i];
            pos++;
        }
    }
    token[pos] = '\0';
    parse_data_func(token, parse_data_func_arg);
}
