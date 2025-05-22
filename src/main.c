#include <limits.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <stdint.h>
#include <wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "error_functions.h"
#include "usage_monitor.h"
#include "usage_interface.h"
#include "process_info.h"

#define NUMBER_OF_THREADS 3

const int N = 300;

int main(int argc, char *argv[])
{
    
    handle_error_not_enough_args(argc);

    
    int *usage_params = get_usage_params();
    if (usage_params == NULL) {
        fprintf(stderr, "Erro: Falha ao obter parâmetros de uso.\n");
        exit(EXIT_FAILURE);
    }

    char **exec_args = (char **)malloc(sizeof(char *) * argc);
    if (exec_args == NULL) {
        perror("malloc for exec_args");
        free(usage_params);
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        exec_args[i - 1] = argv[i];
    }
    exec_args[argc - 1] = NULL;

    pid_t pid = fork();

    if (pid < 0) {
        free(exec_args);
        free(usage_params);
        erro_fork();
    } else if (pid == 0) { 
        execvp(exec_args[0], exec_args);
        erro_exec(exec_args[0]); 
        free(exec_args); 
        free(usage_params);
        exit(EXIT_FAILURE);
    } else {
        int status;
        pid_t result_waitpid;


        for (int i = 0; i < 50; ++i) { 
            result_waitpid = waitpid(pid, &status, WNOHANG);
            if (result_waitpid == pid) {
                if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                    fprintf(stderr, "Erro: O processo monitorado (%s) falhou ao iniciar ou terminou com código de erro %d. Abortando monitoramento.\n", exec_args[0], WEXITSTATUS(status));
                } else if (WIFSIGNALED(status)) {
                    fprintf(stderr, "Erro: O processo monitorado (%s) foi terminado por sinal %d ao iniciar. Abortando monitoramento.\n", exec_args[0], WTERMSIG(status));
                } else {
                    fprintf(stderr, "Aviso: O processo monitorado (%s) terminou muito rapidamente (status 0). Nenhum monitoramento será realizado.\n", exec_args[0]);
                }
                free(exec_args);
                free(usage_params);
                return 1;
            }
            usleep(10000); 
        }

        free(exec_args);

    
        pthread_t threads[NUMBER_OF_THREADS];
        thread_arg_t thread_args[NUMBER_OF_THREADS];

        for (int i = 0; i < NUMBER_OF_THREADS; i++) {
            printf("Metodo Main. Criando thread %d\n", i);
            thread_args[i].tid = i;
            thread_args[i].pid = pid;
            thread_args[i].params = usage_params;
            status = pthread_create(&threads[i], NULL, usage_monitor, &thread_args[i]);
            if (status != 0) {
                fprintf(stderr, "Erro: pthread_create retornou o código de erro %d. Abortando.\n", status);
                free(usage_params);
                exit(EXIT_FAILURE);
            }
        }

        while (1) {
            result_waitpid = waitpid(pid, NULL, WNOHANG);
            if (result_waitpid == 0) {
                process_info();
                sleep(1);
            } else {
                break;
            }
        }

        waitpid(pid, NULL, 0);
        printf("Father Process %d:\n", getpid());
        print_process_info(pid, 0);
        free(usage_params);
        return 0;
    }
}
