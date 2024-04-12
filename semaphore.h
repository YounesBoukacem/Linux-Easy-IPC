#ifndef SEMAPHORE_H
#define SEMAPHORE_H
#include "sys/types.h"
#include "semaphore.h"

typedef struct semaphore{
    char file_path[50];
    int project_id;
    key_t key;
    int semid;
} semaphore;

int get_semaphore(semaphore *semptr,char file_path[], int project_id);
int init_semaphore(semaphore semptr, int semval);
int p(semaphore s);
int v(semaphore s);
int delete_semaphore(semaphore sem);
void sem_printer(semaphore sem);

#endif