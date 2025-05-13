#include <pthread.h>
#include <stdio.h>

// Thread function prototype
void *usage_monitor(void *tid);

// Example thread function

void *usage_monitor(void *tid) {
  int id = (intptr_t)tid;
  printf("Thread %d is running\n", id);
  pthread_exit(NULL);
}
