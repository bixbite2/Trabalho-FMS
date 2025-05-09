#include <stdio.h>
#include <string.h>

int get_usage_params(){
    size_t zero = 0;
    char *max_cpu_time = NULL;
    char *max_run_time = NULL;
    char *max_ram_usage = NULL;
    printf("Tempo maximo de CPU:");
    getline(&max_cpu_time, &zero, stdin);
    printf("Tempo maximo de execução:");
    getline(&max_run_time, &zero, stdin);
    printf("Uso máximo de RAM:");
    getline(&max_ram_usage, &zero, stdin);
    printf("%s",max_cpu_time);
    printf("%s",max_run_time);
    printf("%s",max_ram_usage);
    return 1;
}


