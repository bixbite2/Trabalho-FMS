#include <limits.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <string.h>

const int N = 300;

int error_not_enough_args()
{
    printf("Error: Not enough arguments.");
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        error_not_enough_args();
        return 0;
    }
    int pid = fork( );
    char nome[N];
    printf("PID <%d> tanto pai quanto o filho exibem esta mensagem!\n", getpid());
    // execl("/bin/bc");
    strncpy(nome, argv[1], N-1);
    execve(nome, argv, 0);
    return 1;
}








