#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/sysinfo.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include "error_functions.h"

const int N = 300;

int main(int argc, char *argv[])
{
    handle_error_not_enough_args(argc);
    int pid = fork( );
    char program[N];
    strncpy(program, argv[1], N-1);
    printf("PID <%d> tanto pai quanto o filho exibem esta mensagem!\n", getpid());

    if (pid < 0) {
        printf("Erro ao criar o processo!\n");
    } else if (pid == 0) {
        /* processo filho */
        printf("Esse eh o processo filho com PID %d!\n", getpid());
        execlp(program, NULL);
    }

    waitpid(pid, NULL, 0);
    return 1;
}








