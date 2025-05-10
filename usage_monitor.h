#include <pthread.h>
#include <stdio.h>

// Thread function prototype
void *usage_monitor(void *tid);

// Example thread function
void *usage_monitor(void *tid) {
  // Code that will be executed by the new thread
  printf("Thread is running\n");
  // Return a value from the thread (optional)
  pthread_exit(NULL); // Terminates the thread
}
