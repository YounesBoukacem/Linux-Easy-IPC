#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H
#include "stdbool.h"

typedef struct sharedmem{
    char file_path[50];
    int project_id;
    key_t key;
    int shmid;
}sharedmem;

int get_shared_memory(sharedmem *shm, char file_path[], int project_id, size_t size);
int attach_shared_memory(void **shmadr,sharedmem shm);
bool detach_shared_memory(void *shmadr);
int destroy_shared_memory(sharedmem shm);
void shm_printer(sharedmem shm);
#endif