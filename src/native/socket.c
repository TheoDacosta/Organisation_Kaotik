#include "socket.h"
#include "commands.h"
#include "string.h"
#include <arpa/inet.h>
#include <stdio.h>

static int sockfd;
static FILE* logfile;

void init_address(struct sockaddr_in* serv_addr, char* addr, uint16_t port)
{
    serv_addr->sin_family = AF_INET;
    serv_addr->sin_addr.s_addr = inet_addr(addr);
    serv_addr->sin_port = htons(port);
}

void init_socket(struct sockaddr_in serv_addr, uint16_t port)
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Unable to create socket\n");
        exit(1);
    }
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Unable to connect to the server\n");
        exit(1);
    }
}

void init_logger(char* team_name)
{
    char filename[MAX_FILENAME_SIZE] = "client_";
    str_copy(team_name, &filename[len(filename)], MAX_FILENAME_SIZE - len(filename));
    str_copy(".log", &filename[len(filename)], MAX_FILENAME_SIZE - len(filename));
    logfile = fopen(filename, "w");
    if (logfile == NULL) {
        perror("Unable to open the logging file\n");
    }
}

void send_message(const char* message)
{
    char message_with_endline[MAX_COMMAND_SIZE];
    if (message[len(message) - 1] != '\n') {
        add_endline(message, message_with_endline, MAX_COMMAND_SIZE);
    } else {
        str_copy(message, message_with_endline, MAX_COMMAND_SIZE);
    }
    if (logfile != NULL)
        fprintf(logfile, "sending: %s", message_with_endline);
    printf("sending: %s", message_with_endline);
    if (send(sockfd, message_with_endline, len(message_with_endline), 0) < 0) {
        perror("Unable to send message\n");
        exit(1);
    }
}

void receive_message(char* response)
{
    if (recv(sockfd, response, MAX_RESPONSE_SIZE, 0) < 0) {
        perror("Unable to receive message\n");
        exit(1);
    }
    char* original_response = response;
    char c = -1;
    while (c != '\n') {
        c = *response;
        response++;
    }
    *response = '\0';
    response = original_response;
    if (logfile != NULL)
        fprintf(logfile, "received: %s", response);
    printf("received: %s", response);
}

uint8_t is_address_valid(const char* address)
{
    return inet_addr(address) != INADDR_NONE;
}
