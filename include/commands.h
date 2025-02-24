#ifndef COMMANDS_H
#define COMMANDS_H


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_SIZE 100



void create_move_command(int8_t ship_id, uint16_t angle, uint16_t speed , char* buffer);
void create_fire_command(int8_t ship_id, uint16_t angle, char* buffer); 
void create_radar_command(int8_t ship_id, char* buffer);

void send_move_command(int8_t ship_id, uint16_t angle, uint16_t speed);
void send_fire_command(int8_t ship_id, uint16_t angle);
void send_radar_command(int8_t ship_id);


#endif // COMMANDS_H