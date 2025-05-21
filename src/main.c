// #include <limits.h>
// #include <sys/resource.h>
// #include <sys/sysinfo.h>
// #include <unistd.h>
// #include <wait.h>
// #include "error_functions.h"
// #include "usage_monitor.h"
// #include "usage_interface.h"
// #include "process_info.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "process_created.h"
#include "process_info.h"

// #define NUMBER_OF_THREADS 10

// const int N = 300;

int main(int argc, char *argv[]) {
    // pthread_t threads[NUMBER_OF_THREADS];
    // int tids[NUMBER_OF_THREADS];
    // int status, i;
    
    // (void *)i
    handle_error_not_enough_args(argc);
    get_usage_params();
    
    // char program[N];

    pid_t processo_filho = create_process();

    //manipular o pid e chamar funções que envolvem threads, threads.h

    while (1) {
        if (waitpid(processo_filho, NULL, WNOHANG) == 0) {
            process_info();
            sleep(1);
        } else
            break;
    }

    printf("Processos do programa:\n");
    print_process_info(processo_filho, 0);
    
    return 0;
}
