#ifndef USAGE_MONITOR_H
#define USAGE_MONITOR_H

#include <pthread.h>
#include <stdio.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <string.h>   // para strrchr, strchr
#include <unistd.h>   // para sysconf, _SC_CLK_TCK
#include <signal.h>
#include <sys/wait.h>

#define NUMBER_THREADS 3

typedef struct {
    pthread_t pthread_id;
    pid_t tid;
    pid_t pid;
    int thread_index;
    int *params; 
} thread_arg_t;

threads[NUMBER_THREADS];

void *usage_monitor(void *arg);
double* get_process_stats(pid_t pid);

#endif

