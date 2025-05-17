#ifndef USAGE_MONITOR_H
#define USAGE_MONITOR_H

#include <pthread.h>
#include <stdio.h>

typedef struct {
  int tid;
  int pid;
  int *params;
} thread_arg_t;

void *usage_monitor(void *arg);

#endif

