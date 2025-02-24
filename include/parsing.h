#ifndef PARSING_H
#define PARSING_H

#include <stdint.h>
#include <stdio.h>

#define MAX_DATA_SIZE 100

typedef void (*ParseFunc_t)(char* data, void* argument);

void parse_response(const char* response, ParseFunc_t parse_data_func, void* parse_data_func_arg);

#endif // PARSING_H
