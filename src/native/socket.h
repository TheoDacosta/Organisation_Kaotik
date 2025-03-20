#ifndef SOCKET_H
#define SOCKET_H

#include <netinet/in.h>

#define MAX_FILENAME_SIZE 50

void init_logger(char* team_name);
void init_address(struct sockaddr_in* serv_addr, char* addr, uint16_t port);
void init_socket(struct sockaddr_in serv_addr, uint16_t port);

void send_message(const char* message);
void receive_message(char* response);

uint8_t is_address_valid(const char* address);

#endif // SOCKET_H
