#include <pthread.h>
#include <stdio.h>

// Thread function prototype
//void *usage_monitor(void *tid);

// Example thread function

typedef struct {
    int tid;
    int *params;
} thread_arg_t;

void *usage_monitor(void *tid) {
  int id = (intptr_t)tid;
  printf("Thread %d is running\n", id);
  pthread_exit(NULL);
}
