#include <limits.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <stdint.h>
#include <wait.h>
#include "error_functions.h"
#include "usage_monitor.h"
#include "usage_interface.h"
#include "process_created.h"
#include "process_info.h"
#include <pthread.h>


// 3 threads, cada um para
// Tempo maximo de CPU
// Tempo maximo de execução
// Uso máximo de RAM:

const int N = 300;

int main(int argc, char *argv[]) {
    
    handle_error_not_enough_args(argc);
    // int *usage_params = get_usage_params();
    

    // for (int test = 0; test < 3; test++) {
    //     printf("Param %d: %d\n", test, usage_params[test]);
    // } //Esse snippet pode ser usado para testar se recebesse os parametros corretamente

    pid_t child_process = create_process();

    char program[N];
    strncpy(program, argv[1], N-1);
   
    if (child_process == 0) {
        /* processo filho */
        // printf("Esse eh o processo filho com PID %d!\n", getpid());
        execlp(program, program, (char *)NULL);
        perror("execlp deu ruim");
        exit(EXIT_FAILURE);
    } else {
        while (1){
            if (waitpid(child_process, NULL, WNOHANG) == 0){
                process_info();
                sleep(1);
            } else 
                break;
            
        }
        
    }

    // free(usage_params);
    // waitpid(pid, NULL, 0);

    printf("Father Process %d:\n", getpid());
    print_process_info(child_process, 0);
    return 0;
}
