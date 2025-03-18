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

extern Mutex_t parsing_mutex;

void parse_response(Planet_t* planets, uint16_t* nb_planets, Spaceship_t* spaceships, uint16_t* nb_spaceships, Base_t* base);

#endif // PARSING_H
