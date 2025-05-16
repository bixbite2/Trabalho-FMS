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
    int tids[NUMBER_OF_THREADS];
    int status, i;
    
    // (void *)i
    handle_error_not_enough_args(argc);
    get_usage_params();
    
    char program[N];
    // int pid = fork( );
    
    // strncpy(program, argv[1], N-1);
    
    // for(i=0; i < NUMBER_OF_THREADS; i++) {
        
    //     pthread_join(threads[i], NULL);
        
    //     tids[i] = i;
    //     printf("Metodo Main. Criando thread %d\n", i);
    //         status = pthread_create(&threads[i], NULL, usage_monitor, (void *)&tids[i]);
    //     if (status != 0) {
    //         printf("Oops. pthread create returned error code %d\n", status);
    //         exit(-1);
    //     }
    // }

    // if (pid < 0) {
    //     printf("Erro ao criar o processo!\n");
    // } else if (pid == 0) {
    //     /* processo filho */
    //     printf("Esse eh o processo filho com PID %d!\n", getpid());
    //     execlp(program, program, NULL);
    // }

    // waitpid(pid, NULL, 0);
    // return 1;

    int pid = fork();

    if (pid < 0) {
        printf("Erro ao criar o processo!\n");
        return 1;
    } else if (pid == 0) {
        printf("Esse eh o processo filho com PID %d!\n", getpid());
        execlp(argv[1], argv[1], NULL);
        perror("Erro ao executar o programa");
        exit(1);
    } else {
        strncpy(program, argv[1], N-1);

        for (i = 0; i < NUMBER_OF_THREADS; i++) {
            tids[i] = i;
            printf("Metodo Main. Criando thread %d\n", i);
            status = pthread_create(&threads[i], NULL, usage_monitor, (void *)&tids[i]);
            if (status != 0) {
                printf("Oops. pthread create returned error code %d\n", status);
                exit(-1);
            }
        }

        for (i = 0; i < NUMBER_OF_THREADS; i++) {
            printf("milena");
            pthread_join(threads[i], NULL);
        }

        waitpid(pid, NULL, 0);
    }

    return 0;

}








