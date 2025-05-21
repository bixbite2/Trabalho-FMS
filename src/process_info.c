#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <ctype.h>
#include "process_info.h"

void process_info(){
    char path[256], buffer[512];
    Process array[MAX_PROCESS], p;
    int qtd = 0;
    
    DIR *dir = opendir("/proc");
    struct dirent *entry;
    
    
    while ((entry = readdir(dir)) != NULL) {
        if (isdigit(entry->d_name[0])) {
            pid_t pid = atoi(entry->d_name);
            snprintf(path, sizeof(path), "/proc/%d/status", pid);
            
            FILE *f = fopen(path, "r");
            if (!f) continue;
            
            p.pid = pid;
            p.ppid = -1;
            strcpy(p.name, "desconhecido");

            while (fgets(buffer, sizeof(buffer), f)) {
                if (strncmp(buffer, "Name:", 5) == 0) 
                    sscanf(buffer, "Name:\t%255s", p.name);
                else if (strncmp(buffer, "PPid:", 5) == 0)
                    sscanf(buffer, "PPid:\t%d", &p.ppid);
            }
            fclose(f);
            array[qtd++] = p;
        }
    }
    
    extern qtd, array, pid;
    closedir(dir);
    
}

void print_process_info(pid_t ppid, int lvl){
    for (int i = 0; i < qtd; i++){        
        if (array[i].ppid == ppid) {
            for (int j = 0; i < lvl;j++) printf("  "); 
            printf("└─ %s (PID: %d)\n", array[i].name, array[i].pid);
            print_process_info(array[i].pid, lvl + 1);
        }
    }
}