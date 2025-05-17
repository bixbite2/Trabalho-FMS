#include "usage_monitor.h"

void *usage_monitor(void *arg) {
  thread_arg_t *data = (thread_arg_t *)arg;
  int id = data -> tid;
  int process_id = data -> pid;
  int *params = data -> params;
  printf("Thread %d is running\n", id);
  printf("Monitored process  is %d\n", process_id);
  printf("Param[0] = %d\n", params[0]);
  printf("Param[1] = %d\n", params[1]);
  printf("Param[2] = %d\n", params[2]);
  pthread_exit(NULL);
}
