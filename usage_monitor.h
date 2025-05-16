#include <pthread.h>
#include <stdio.h>

// Thread function prototype
//void *usage_monitor(void *tid);

// Example thread function

typedef struct {
    int tid;
    int *params;
} thread_arg_t;

void *usage_monitor(void *arg) {
  thread_arg_t *data = (thread_arg_t *)arg;
  int id = data -> tid;
  int *params = data -> params;
  printf("Thread %d is running\n", id);
  printf("Param[0] = %d\n", params[0]);
  printf("Param[1] = %d\n", params[1]);
  printf("Param[2] = %d\n", params[2]);
  pthread_exit(NULL);
}
