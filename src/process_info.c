#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include "process_info.h"

void print_process_info(pid_t pid){
    char path[256], buffer[1024];
    FILE *fp;

    printf("\n========== Processo PID %d ==========\n", pid);

    snprintf(path, sizeof(path), "/proc/%d/comm", pid);
    fp = fopen(path, "r");

    if (fp) {
        if (fgets(buffer, sizeof(buffer), fp))
            printf("Nome do processo: %s", buffer);
        fclose(fp);
    }

    //process status
    snprintf(path, sizeof(path), "/proc/%d/status", pid);
    fp = fopen(path, "r");

    if (fp){
        printf("\n--- Status ---\n");
        while (fgets(buffer, sizeof(buffer), fp)){
            if (strncmp(buffer, "State:", 6) == 0 || strncmp(buffer, "VmRSS:", 6) == 0 || strncmp(buffer, "Threads:", 8) == 0)
                printf("%s", buffer);            
        }
        
        fclose(fp);
    }
    
    //cpu information
    snprintf(path, sizeof(path), "/proc/%d/stat", pid);
    fp = fopen(path, "r");

    if (fp){
        unsigned long utime, stime;

        for (int i = 0; i < 13; i++)
            fscanf(fp, "%s", buffer);
        
        fscanf(fp, "%lu", &utime);
        fscanf(fp, "%lu", &stime);


        printf("\n--- Tempo de CPU ---\n");
        printf("User mode: %.2f s\n", utime / (double)sysconf(_SC_CLK_TCK));
        printf("User mode: %.2f s\n", stime / (double)sysconf(_SC_CLK_TCK));

        fclose(fp);
    }

    printf("=====================================\n\n");

    
}