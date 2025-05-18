// #include <limits.h>
// #include <sys/resource.h>
// #include <sys/sysinfo.h>
// #include <unistd.h>
// #include <wait.h>
// #include "error_functions.h"
// #include "usage_monitor.h"
// #include "usage_interface.h"
// #include "process_info.h"

#include "process_created.h"
#include <stdio.h>
#include <stdlib.h>

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

    pid_t pid = create_process();

    //manipular o pid e chamar funções que envolvem threads, threads.h

    
    
    return 0;

}
