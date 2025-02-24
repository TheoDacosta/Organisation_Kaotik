#ifndef COMMANDS_H
#define COMMANDS_H


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_SIZE 100



void create_move_command(int8_t ship_id, uint16_t angle, uint16_t speed , char* buffer);
void create_fire_command(int8_t ship_id, uint16_t angle, char* buffer); 



#endif // COMMANDS_H