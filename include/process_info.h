#ifndef PROCESS_INFO_H
#define PROCESS_INFO_H

#include <sys/types.h>

#define MAX_PROCESS 4096

typedef struct {
    pid_t pid;
    int ppid;
    char name[256];
} Process;

void process_info();
void print_process_info(pid_t ppid, int lvl);

#endif