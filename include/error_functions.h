#ifndef ERROR_FUNCTIONS_H
#define ERROR_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void terminate_program(const char *message, int exit_code, int sys_errno);
void handle_error_not_enough_args(int args);
void erro_fork(void);
void erro_exec(const char *program);
void erro_open(const char *file);

#endif