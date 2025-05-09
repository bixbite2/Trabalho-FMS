#include <limits.h>
#include <sys/resource.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <wait.h>
#include "error_functions.h"
#include "usage_monitor.h"
#include "usage_interface.h"

const int N = 300;
pthread_t thread;

int main(int argc, char *argv[])
{
    handle_error_not_enough_args(argc);
    get_usage_params();
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

    waitpid(pid, NULL, 0);
    return 1;
}








