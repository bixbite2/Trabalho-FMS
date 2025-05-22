#include "usage_monitor.h"

volatile sig_atomic_t stop_all = 0;
void *usage_monitor(void *arg) {
  thread_arg_t *data = (thread_arg_t *)arg;
  int id = data -> tid;
  int process_id = data -> pid;
  int *params = data -> params;

  int cpu_monitor = 0;
  int uptime_monitor = 1;
  int ram_monitor = 2;
  int sig_term = 15;
  int check_frequency = 1;

  printf("Thread %d is running\n", id);
  printf("Monitored process is %d\n", process_id);

  if (id == cpu_monitor) {
    double cpu_time = get_process_stats(process_id, params)[0];
    while (!stop_all && cpu_time < params[0]) {
      printf("CPU time (user + system): %.2f seconds\n", cpu_time);
      sleep(check_frequency);
      cpu_time = get_process_stats(process_id, params)[0];
    }
    printf("Process killed by CPU time.\n");
  }
  if (id == uptime_monitor) {
    double uptime = get_process_stats(process_id, params)[1];
    while (!stop_all && uptime < params[1]) {
      printf("Uptime: %.2f seconds\n", uptime);
      sleep(check_frequency);
      uptime = get_process_stats(process_id, params)[1];
    }
    printf("Process killed by usage time.\n");
  }
  if (id == ram_monitor) {
    double ram_usage = get_process_stats(process_id, params)[2];
    while (!stop_all && ram_usage < params[2]) {
      printf("RAM usage: %.2f mb\n", ram_usage);
      sleep(check_frequency);
      ram_usage = get_process_stats(process_id, params)[2];
    }
    printf("Process killed by RAM usage.\n");
  }

  stop_all = 1;
  kill(process_id, sig_term);
  pthread_exit(NULL);
}

double* get_process_stats(pid_t pid, int *params) {
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
    //
    // In computing, resident set size is the portion of memory occupied by a
    //                   process that is held in main memory.

    snprintf(path, sizeof(path), "/proc/%d/statm", pid);
    file_pointer = fopen(path, "r");
    if (!file_pointer) return NULL;

    long rss;
    fscanf(file_pointer, "%*s %ld", &rss);
    fclose(file_pointer);

    long page_size = sysconf(_SC_PAGESIZE); // em bytes
    stats[2] = (rss * page_size) / 1024.0 / 1024.0; // Atual RAM usage em MB

    // Save stats to last_usage file in simple format: "cpu_time uptime max_ram"
    FILE *last_usage = fopen("last_usage", "w");
    if (last_usage) {
        fprintf(last_usage, "%.2f %.2f %d", stats[0], stats[1], params[2]);
        fclose(last_usage);
    } else {
        perror("Error opening last_usage file");
    }

    return stats;
}

