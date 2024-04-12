#include "stdlib.h"
#include "sys/ipc.h"
#include "sys/shm.h"
#include "stdbool.h"
#include "stdio.h"
#include "string.h"
#include "sys/types.h"
#include "shared_memory.h"

int get_shared_memory(sharedmem *shm, char file_path[], int project_id, size_t size){
    key_t key;
    key = ftok(file_path, project_id);
    if(key == -1) return -1;
    int shmid;
    shmid = shmget(key, size, 0666|IPC_CREAT);
    if(shmid == -1) return -2;
    strcpy(shm->file_path, file_path);
    shm->project_id = project_id;
    shm->key = key;
    shm->shmid = shmid;
    return 0;
}


int attach_shared_memory(void **shmadr,sharedmem shm){
    *shmadr = shmat(shm.shmid, NULL, 0);
    if(*shmadr == (void *)(-1)) return -1;
    return 0;
}

bool detach_shared_memory(void *shmadr){
    return (shmdt(shmadr) != -1);
}


int destroy_shared_memory(sharedmem shm){
    int status = shmctl(shm.shmid, IPC_RMID, NULL);
    if(status == -1) return -1;
    return 0;
}

void shm_printer(sharedmem shm){
    printf("file_path : %s\n", shm.file_path);
    printf("project_id : %d\n", shm.project_id);
    printf("key : %d\n", shm.key);
    printf("semid : %d\n", shm.shmid);
}




//--------------------------------TESTS ZONE----------------------------------------//

/*
bool destroy_shared_memory(char *filename, int project_id){
    key_t key;
    key = ftok(filename, project_id);
    if(key == -1)
        return false;
    int shmid;
    shmid = shmget(key, 0, 0);
    if(shmid == -1)
        return false;
    return (shmctl(shmid, IPC_RMID, NULL) != -1);
}
*/

/*
int attach_shared_memory(char **shmadr,char *filename, int project_id){
    key_t key;
    key = ftok(filename, project_id);
    if(key == -1) return -1;
    int shmid;
    shmid = shmget(key, 0, 0);
    if(shmid == -1) return NULL
    
    void *shm_adr;
    shm_adr = shmat(shmid, NULL, 0);
    if(shm_adr == (void *)(-1)){
        printf("Couldn't attach shm\n");
        return NULL;
    }
    return shm_adr;
}
*/


/*
int main(int argc, char **argv){
    if(argc != 1){
        printf("Arguments !\n");
        return -1;
    }

    sharedmem shm;
    int status = get_shared_memory(&shm,"./shmfile",'A',4096);
    if(status == -1){
        printf("Couldn't generate key\n");
        return -1;
    }
    else if(status == -2){
        printf("Couldn't generate shmid\n");
        return -1;
    }
    
    shm_printer(shm);

    char *shmadr;
    status = attach_shared_memory(&shmadr,shm);
    if(status == -1){
        printf("Coudln't attach shm\n");
        return -1;
    }

    int i;
    scanf("%d",&i);
    detach_shared_memory(shmadr);
    scanf("%d",&i);
    destroy_shared_memory(shm);
    
    if(strcmp(argv[1],"1") == 0){
        printf("Writing : %s\n", argv[2]);
        strcpy(shmadr, argv[2]);
    }
    else
        printf("Reading : %s\n", shmadr);
    

    

    return 0;


}

*/