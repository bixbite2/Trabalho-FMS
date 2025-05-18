#include "usage_monitor.h"
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

void *usage_monitor(void *arg) {
  thread_arg_t *data = (thread_arg_t *)arg;
  int id = data -> tid;
  int process_id = data -> pid;
  int *params = data -> params;
  printf("Thread %d is running\n", id);
  printf("Monitored process  is %d\n", process_id);

double cpu_time = get_process_cpu_time(process_id);
  while (get_process_cpu_time(process_id) < params[0]) {

    printf("CPU time (user + system): %.2f seconds\n", cpu_time);
    sleep(1);
    cpu_time = get_process_cpu_time(process_id);
  }
  kill(process_id, 9);


  printf("Param[0] = %d\n", params[0]);
  printf("Param[1] = %d\n", params[1]);
  printf("Param[2] = %d\n", params[2]);
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

    // Skip to the 14th and 15th fields (utime and stime)
    long utime, stime;
    int i;
    char buffer[1024];
    fgets(buffer, sizeof(buffer), fp);
    fclose(fp);

    // Find the closing parenthesis of the process name
    char *ptr = strrchr(buffer, ')') + 2;

    for (i = 3; i < 15; i++) {
        ptr = strchr(ptr, ' ') + 1;
    }

    sscanf(ptr, "%ld %ld", &utime, &stime);
    double total_time = (utime + stime) / (double) sysconf(_SC_CLK_TCK);
    return total_time;
}
