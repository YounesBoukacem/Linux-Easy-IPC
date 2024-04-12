#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "semaphore.h"

typedef union semun {
    int              val;    
    struct semid_ds *buf;    
    unsigned short  *array;
    struct seminfo  *__buf;
} semctl_ar
int get_semaphore(semaphore *semptr,char file_path[], int project_id){
    key_t key;
    key = ftok(file_path,project_id);
    if(key == -1) return -1;
    int semid;
    semid = semget(key, 1, 0666|IPC_CREAT);
    if(semid == -1) return -2;
    strcpy(semptr->file_path, file_path);
    semptr->project_id = project_id;
    semptr->key = key;
    semptr->semid = semid; 

    return 0;
}

int init_semaphore(semaphore semptr, int semval){
    semctl_arg arg;
    arg.val = semval;
    int status = semctl(semptr.semid, 0, SETVAL, arg);
    if(status == -1) return -1;
    
    return 0;
}

int p(semaphore s){
    
    struct sembuf sops[1];
    sops[0].sem_num = 0;
    sops[0].sem_op = -1;
    sops[0].sem_flg = 0;
    int status;
    status = semop(s.semid, sops, 1);
    if(status == -1) return -1;
    return 0;
}

int v(semaphore s){
    struct sembuf sops[1];
    sops[0].sem_num = 0;
    sops[0].sem_op = 1;
    sops[0].sem_flg = 0;
    int status;
    status = semop(s.semid, sops, 1);
    if(status == -1) return -1;
    return 0;
}

int delete_semaphore(semaphore sem){
    int status;
    status = semctl(sem.semid, 0, IPC_RMID, 0);
    if(status == -1) return -1;
    return 0;
}

void sem_printer(semaphore sem){
    printf("file_path : %s\n", sem.file_path);
    printf("project_id : %d\n", sem.project_id);
    printf("key : %d\n", sem.key);
    printf("semid : %d\n", sem.semid);
    printf("semval : %d\n", semctl(sem.semid, 0, GETVAL,NULL));
}


/*--------------------------------------------------------TEST ZONE--------------------------------------------------*/
/*
int main(){
    semaphore s;
    get_semaphore(&s, "flio", 'A');
    sem_printer(s);
    sleep(3);
    
    init_semaphore(s, 13);
    printf("----------------------\n");
    sem_printer(s);
    sleep(3);
    
    v(s);
    printf("----------------------\n");
    sem_printer(s);
    sleep(3);
    
    p(s);
    printf("----------------------\n");
    sem_printer(s);
    sleep(3);
    


    return 0;
}
*/