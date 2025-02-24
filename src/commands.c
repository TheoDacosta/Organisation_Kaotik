#include "commands.h"



void create_move_command(int8_t ship_id, uint16_t angle, uint16_t speed , char* buffer) {
    sprintf(buffer, "MOVE %d %d %d\n", ship_id, angle, speed);
}

void create_fire_command(int8_t ship_id, uint16_t angle, char* buffer) {
    sprintf(buffer, "FIRE %d %d\n", ship_id, angle);
}