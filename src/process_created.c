#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "process_created.h"
#include <unistd.h>

pid_t create_process(){
    pid_t pid = fork();

    if (pid < 0)
        perror("não deu certo o fork, msg bnt pro bruno");
    else if (pid == 0) 
        printf("Processo filho com PID %d\n", getpid());
    
    return pid;
}