#include "usage_monitor.h"

void *usage_monitor(void *arg) {
  thread_arg_t *data = (thread_arg_t *)arg;
  int id = data -> tid;
  int process_id = data -> pid;
  int *params = data -> params;

  int cpu_monitor = 0;
  int uptime_monitor = 1;
  int ram_monitor = 2;
  int sig_term = 9;

  printf("Thread %d is running\n", id);
  printf("Monitored process is %d\n", process_id);

  if (id == cpu_monitor) {
    double cpu_time = get_process_stats(process_id)[0];
    while (cpu_time < params[0]) {
      printf("CPU time (user + system): %.2f seconds\n", cpu_time);
      sleep(1);
      cpu_time = get_process_stats(process_id)[0];
    }
  }
  if (id == uptime_monitor) {
    double uptime = get_process_stats(process_id)[1];
    while (uptime < params[1]) {
      printf("Uptime: %.2f seconds\n", uptime);
      sleep(1);
      uptime = get_process_stats(process_id)[1];
    }
  }
  if (id == ram_monitor) {
    double ram_usage = get_process_stats(process_id)[2];
    while (ram_usage < params[2]) {
      printf("RAM usage: %.2f mb\n", ram_usage);
      sleep(1);
      ram_usage = get_process_stats(process_id)[2];
    }
  }

  kill(process_id, sig_term);
  pthread_exit(NULL);
}

double* get_process_stats(pid_t pid) {
    static double stats[3]; // [cpu_time, uptime, ram_usage]

    // Abrir /proc/[pid]/stat
    char path[64];
    snprintf(path, sizeof(path), "/proc/%d/stat", pid);
    FILE *file_pointer = fopen(path, "r");
    if (!file_pointer) {
        perror("fopen");
        return NULL;
    }

    char buffer[1024];
    fgets(buffer, sizeof(buffer), file_pointer);
    fclose(file_pointer);

    char *pointer = strrchr(buffer, ')') + 2;
    for (int i = 3; i < 15; i++){
      pointer = strchr(pointer, ' ') + 1;
    }

    long utime, stime;
    sscanf(pointer, "%ld %ld", &utime, &stime);

    for (int i = 15; i < 22; i++){
      pointer = strchr(pointer, ' ') + 1;
    }

    long long starttime;
    sscanf(pointer, "%lld", &starttime);

    long clk_tck = sysconf(_SC_CLK_TCK);
    stats[0] = (utime + stime) / (double)clk_tck;

    // uptime do sistema
    FILE *uptime_file_pointer = fopen("/proc/uptime", "r");
    if (!uptime_file_pointer) return NULL;
    double uptime;
    fscanf(uptime_file_pointer, "%lf", &uptime);
    fclose(uptime_file_pointer);

    stats[1] = uptime - (starttime / (double)clk_tck);

    // memória (RSS) de /proc/[pid]/statm
    snprintf(path, sizeof(path), "/proc/%d/statm", pid);
    file_pointer = fopen(path, "r");
    if (!file_pointer) return NULL;

    long rss;
    fscanf(file_pointer, "%*s %ld", &rss);
    fclose(file_pointer);

    long page_size = sysconf(_SC_PAGESIZE); // em bytes
    stats[2] = (rss * page_size) / 1024.0 / 1024.0; // em MB

    return stats;
}

