#include <limits.h>
#include <sys/resource.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <wait.h>
#include "error_functions.h"
#include "usage_monitor.h"
#include "usage_interface.h"

#define NUMBER_OF_THREADS 10

const int N = 300;

int main(int argc, char *argv[])
{
    pthread_t threads[NUMBER_OF_THREADS];

    handle_error_not_enough_args(argc);
    get_usage_params();
    int pid = fork( );
    char program[N];
    strncpy(program, argv[1], N-1);
    int status, i;
    for(i=0; i < NUMBER_OF_THREADS; i++) {
        printf("Metodo Main. Criando thread %d\n", i);
            status = pthread_create(&threads[i], NULL, usage_monitor, (void *)i);
        if (status != 0) {
            printf("Oops. pthread create returned error code %d\n", status);
            exit(-1);
        }
    }

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








