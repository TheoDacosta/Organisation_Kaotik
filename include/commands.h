#ifndef COMMANDS_H
#define COMMANDS_H

#include "base.h"
#include "os_manager.h"
#include "spaceship.h"
#include <stdint.h>

#define MAX_COMMAND_SIZE 100
#define MAX_RESPONSE_SIZE 1000
#define MAX_PLANET_ID 65535
#define MAX_SHIP_ID 9
#define MAX_COLLECTORS_SPEED 1000
#define MAX_EXPLORERS_SPEED 2000
#define MAX_ATTACKERS_SPEED 3000
#define ATTACKERS_SIZE 5
#define EXPLORERS_SIZE 2
#define COLLECTORS_SIZE 2
#define FIRE_RANGE 5000

extern Mutex_t response_mutex;
extern char response[MAX_RESPONSE_SIZE];

void create_move_command(int8_t ship_id, uint16_t angle, uint16_t speed, char* buffer);
void create_fire_command(int8_t ship_id, uint16_t angle, char* buffer);
void create_radar_command(int8_t ship_id, char* buffer);

void send_command(char* command);

#endif // COMMANDS_H
