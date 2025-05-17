#include <limits.h>
#include <sys/resource.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <wait.h>
#include <stdint.h>
#include "error_functions.h"
#include "usage_monitor.h"
#include "usage_interface.h"

#define NUMBER_OF_THREADS 3
// 3 threads, cada um para
// Tempo maximo de CPU
// Tempo maximo de execução
// Uso máximo de RAM:

const int N = 300;

int main(int argc, char *argv[])
{
    pthread_t threads[NUMBER_OF_THREADS];

    handle_error_not_enough_args(argc);
    int *usage_params = get_usage_params();
    thread_arg_t args[NUMBER_OF_THREADS];
    // for (int test = 0; test < 3; test++) {
    //     printf("Param %d: %d\n", test, usage_params[test]);
    // } //Esse snippet pode ser usado para testar se recebesse os parametros corretamente

    int pid = fork( );

    char program[N];
    strncpy(program, argv[1], N-1);
    if (pid < 0) {
        printf("Erro ao criar o processo!\n");
    } else if (pid == 0) {
        /* processo filho */
        printf("Esse eh o processo filho com PID %d!\n", getpid());
        execlp(program, NULL);
    }
    if (pid > 0) {
        // printf("O pid é %d\n",pid);
        int status, i;
        for(i=0; i < NUMBER_OF_THREADS; i++) {
            printf("Metodo Main. Criando thread %d\n", i);
            args[i].tid = i;
            args[i].pid = pid;
            args[i].params = usage_params;
            //status = pthread_create(&threads[i], NULL, usage_monitor, (void *)i);
            status = pthread_create(&threads[i], NULL, usage_monitor, &args[i]);
            pthread_join(threads[i], NULL);
            if (status != 0) {
                printf("Oops. pthread create returned error code %d\n", status);
                exit(-1);
            }
        }
    }

    free(usage_params);
    waitpid(pid, NULL, 0);
    return 1;
}








