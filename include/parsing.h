#ifndef PARSING_H
#define PARSING_H

#include <stdint.h>

#include "base.h"
#include "os_manager.h"
#include "planet.h"
#include "spaceship.h"

#define MAX_DATA_SIZE 100

enum DataType_t {
    DATA_TYPE_PLANET = 'P',
    DATA_TYPE_SPACESHIP = 'S',
    DATA_TYPE_BASE = 'B'
};

void parse_response(const char* response);

#endif // PARSING_H
