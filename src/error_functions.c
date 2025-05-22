#include "error_functions.h"

void terminate_program(const char *message, int exit_code, int sys_errno) {
    if (message != NULL) {
        fprintf(stderr, "Erro: %s\n", message);
    }
    if (sys_errno != 0) {
        fprintf(stderr, "Erro do sistema: %s\n", strerror(sys_errno));
    }
    exit(exit_code);
}

void handle_error_not_enough_args(int args) {
    if (args < 2) {
        terminate_program("Não há argumentos suficientes. Uso: ./my_app.out <comando_a_monitorar> [argumentos_do_comando...]", EXIT_FAILURE, 0);
    }
}

void erro_fork(void) {
    terminate_program("Falha ao criar processo (fork)", EXIT_FAILURE, errno);
}

void erro_exec(const char *program) {
    char msg[512];
    snprintf(msg, sizeof(msg), "Falha ao executar o programa: %s", program);
    terminate_program(msg, EXIT_FAILURE, errno);
}

void erro_open(const char *file) {
    char msg[512];
    snprintf(msg, sizeof(msg), "Falha ao abrir o arquivo: %s", file);
    terminate_program(msg, EXIT_FAILURE, errno);
}