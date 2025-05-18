#include "usage_monitor.h"
#include <stdio.h>

void *usage_monitor(void *arg) {
  thread_arg_t *data = (thread_arg_t *)arg;
  int id = data -> tid;
  int process_id = data -> pid;
  int *params = data -> params;

  int cpu_monitor = 0;
  int uptime_monitor = 1;
  int ram_monitor = 2;

  printf("Thread %d is running\n", id);
  printf("Monitored process  is %d\n", process_id);

  if (id == cpu_monitor) {
    double cpu_time = get_process_cpu_time(process_id);
    while (get_process_cpu_time(process_id) < params[0]) {
      printf("CPU time (user + system): %.2f seconds\n", cpu_time);
      sleep(1);
      cpu_time = get_process_cpu_time(process_id);
    }
    kill(process_id, 15);
  }
  if (id == uptime_monitor) {
    printf("Uptime monitor\n");
  }
  if (id == ram_monitor) {
    printf("Ram monitor\n");
  }

  pthread_exit(NULL);
}


double get_process_cpu_time(pid_t pid) {
    char path[64];
    snprintf(path, sizeof(path), "/proc/%d/stat", pid);

    FILE *fp = fopen(path, "r");
    if (!fp) {
        perror("fopen");
        return 0;
    }

    long utime, stime;
    int i;
    char buffer[1024];
    fgets(buffer, sizeof(buffer), fp);
    fclose(fp);

    // Find the closing parenthesis of the process name
    //
    char *ptr = strrchr(buffer, ')') + 2;

    for (i = 3; i < 15; i++) {
        ptr = strchr(ptr, ' ') + 1;
    }

    sscanf(ptr, "%ld %ld", &utime, &stime);
    double total_time = (utime + stime) / (double) sysconf(_SC_CLK_TCK);
    return total_time;
}
