#ifndef OS_MANAGER_H_
#define OS_MANAGER_H_
#include <stdint.h>
#include <stdlib.h>


typedef void *Thread_t;
typedef void *ThreadId_t;
typedef void (*ThreadFunc_t) (void *argument);
typedef void *Mutex_t;



// Lancer , start , créer un threzad

// Mise en place des structures pour les mutexes
typedef struct {
    const char* name;
} MutexAttr_t;

// Mise en place des structures pour les threads
typedef struct {
    const char* name; ///< name of the thread
    uint32_t stack_size; ///< size of stack
} ThreadAttr_t;

// Mise en place des paramètres des threads

// Thread_t thread_1, thread_2, thread_3,thread_4, thread_5,thread_6,thread_7,thread_8, thread_9;

// Fonction Pour la créations mutexes
Mutex_t create_mutex();
void get_mutex(Mutex_t mutex_id);
void release_mutex(Mutex_t mutex_id);

// Faire une fonction de conversion pour convertir une fonction un mutexT en Mutex_t
Thread_t create_thread(ThreadFunc_t func, const ThreadAttr_t* arguement);

/*Fonction pour la mise en place des threads*/
void thread_test(void* argument);

#endif // OS_MANAGER_H_
