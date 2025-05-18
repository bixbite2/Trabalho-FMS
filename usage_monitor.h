#ifndef USAGE_MONITOR_H
#define USAGE_MONITOR_H

#include <pthread.h>
#include <stdio.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <string.h>   // para strrchr, strchr
#include <unistd.h>   // para sysconf, _SC_CLK_TCK

typedef struct {
  int tid;
  int pid;
  int *params;
} thread_arg_t;

void *usage_monitor(void *arg);
double get_process_cpu_time(pid_t pid);

#endif

