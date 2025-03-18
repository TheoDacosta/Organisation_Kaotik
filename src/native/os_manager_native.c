#include "commands.h"
#include "os_manager.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

static int sockfd;

Mutex_t create_mutex()
{
    pthread_mutex_t* mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
    if (mutex == NULL) {
        perror("mutex malloc failed");
        return NULL;
    }
    if (pthread_mutex_init(mutex, NULL) != 0) {
        perror("pthread_mutex_init failed");
        free(mutex);
        return NULL;
    }
    return (Mutex_t)mutex;
}

void get_mutex(Mutex_t mutex)
{
    if (mutex == NULL)
        return;
    pthread_mutex_lock((pthread_mutex_t*)mutex);
}

void release_mutex(Mutex_t mutex)
{
    if (mutex == NULL)
        return;
    pthread_mutex_unlock((pthread_mutex_t*)mutex);
    sched_yield();
}

Thread_t create_thread(ThreadFunc_t func, void* argument)
{
    pthread_t* new_thread = malloc(sizeof(pthread_t));
    if (new_thread == NULL) {
        perror("thread malloc failed");
        while (1)
            ;
    }
    if (pthread_create(new_thread, NULL, func, argument) != 0) {
        perror("thread creation failed");
        free(new_thread);
        while (1)
            ;
    }
    return (Thread_t)new_thread;
}

uint32_t get_current_timeMs()
{
    return (clock() * 1000) / CLOCKS_PER_SEC;
}

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
        printf("Unable to create socket\n");
        exit(1);
    }
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Unable to connect to the server\n");
        exit(1);
    }
    printf("Connected to the server successfully\n");
}

uint16_t len(const char* str)
{
    uint16_t length = 0;
    while (*str != '\0') {
        length++;
        str++;
    }
    return length;
}

void str_copy(const char* src, char* dest)
{
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

void add_endline(const char* str, char* str_result)
{
    while (*str != '\0') {
        *str_result = *str;
        str_result++;
        str++;
    }
    *str_result = '\n';
    str_result++;
    *str_result = '\0';
}

void send_message(const char* message)
{
    char message_with_endline[MAX_COMMAND_SIZE];
    if (message[len(message) - 1] != '\n') {
        add_endline(message, message_with_endline);
    } else {
        str_copy(message, message_with_endline);
    }
    printf("sending: %s\n", message_with_endline);
    if (send(sockfd, message_with_endline, len(message_with_endline), 0) < 0) {
        printf("Unable to send message\n");
        exit(1);
    }
}

void receive_message(char* response)
{
    if (recv(sockfd, response, MAX_RESPONSE_SIZE, 0) < 0) {
        printf("Unable to receive message\n");
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
    printf("received: %s\n", response);
}

int puts(const char* str)
{
    send_message(str);
    return 0;
}

char* gets(char* str)
{
    receive_message(str);
    return str;
}

uint8_t is_localhost(char* address)
{
    char* localhost = "localhost";
    while (*address != '\0' && *localhost != '\0') {
        if (*address != *localhost) {
            return 0;
        }
        address++;
        localhost++;
    }
    return *address == *localhost;
}

void os_initialisation(int argc, char* argv[])
{
    if (argc != 4) {
        printf("Usage: %s <address> <port> <team_name>\n", argv[0]);
        exit(1);
    }
    char* address = argv[1];
    if (is_localhost(address)) {
        char* localhost = "127.0.0.1";
        str_copy(localhost, address);
    }
    if (inet_addr(address) == INADDR_NONE) {
        printf("Invalid address\n");
        exit(1);
    }
    uint16_t port = (uint16_t)atoi(argv[2]);
    char* team_name = argv[3];

    struct sockaddr_in serv_addr;
    init_address(&serv_addr, address, port);
    init_socket(serv_addr, port);
    // Start the game
    send_message(team_name);
    char response[MAX_RESPONSE_SIZE] = { 0 };
    receive_message(response);
    if (!(response[0] == 'O' && response[1] == 'K' && response[2] == '\n' && response[3] == '\0')) {
        printf("Connection refused by the server");
        exit(1);
    }
}
void os_start()
{
    pthread_exit(NULL);
}
