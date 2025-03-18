#include "commands.h"
#include "os_manager.h"
#include "socket.h"
#include "string.h"
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

Mutex_t create_mutex()
{
    pthread_mutex_t* mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
    if (mutex == NULL) {
        perror("mutex malloc failed");
        exit(1);
    }
    if (pthread_mutex_init(mutex, NULL) != 0) {
        perror("pthread_mutex_init failed");
        free(mutex);
        exit(1);
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
        exit(1);
    }
    if (pthread_create(new_thread, NULL, func, argument) != 0) {
        perror("thread creation failed");
        free(new_thread);
        exit(1);
    }
    return (Thread_t)new_thread;
}

uint32_t get_current_timeMs()
{
    return (clock() * 1000) / CLOCKS_PER_SEC;
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
    if (!is_address_valid(address)) {
        perror("Invalid address\n");
        exit(1);
    }
    uint16_t port = (uint16_t)atoi(argv[2]);
    char* team_name = argv[3];
    // init socket and logger
    init_logger(team_name);
    struct sockaddr_in serv_addr;
    init_address(&serv_addr, address, port);
    init_socket(serv_addr, port);
    // Start the game
    send_message("0\n");
    send_message(team_name);
    char response[MAX_RESPONSE_SIZE] = { 0 };
    receive_message(response);
    if (!(response[0] == 'O' && response[1] == 'K' && response[2] == '\n' && response[3] == '\0')) {
        perror("Connection refused by the server");
        exit(1);
    }
}
void os_start()
{
    pthread_exit(NULL);
}
