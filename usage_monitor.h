#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <pthread.h>

#define MAX_PIDS 32768

static int pid_exist[MAX_PIDS];

// Thread function that monitors processes
void *usage_monitor(void *arg){
    int tid = *((int*)arg);
    int vec[MAX_PIDS] = {0};

    if (vec == NULL){
        perror("calloc");
        pthread_exit(NULL);
    }

    printf("thread %d is running\n", tid);

    while (1){
        memset(vec, 0, sizeof(0));

        DIR *dp = opendir("/proc");
        if (!dp){
            perror("opendir /proc");
            EXIT_FAILURE;
        }

        struct dirent *entry;
        while ((entry = readdir(dp))){
          //verify if entry as a number, represent as PID
            if (isdigit(*entry -> d_name)){
                int pid = atoi(entry -> d_name);
                if (pid > 0 && pid < MAX_PIDS){
                    vec[pid] = 1;
                    //if the process is new, printf
                    if (!pid_exist[pid])
                        printf("New process: PID %d\n", pid);
                }
            }
        }

        closedir(dp);

        //check finished processes
        for (int i = 1; i < MAX_PIDS; i++){
            if (pid_exist[i] && !vec[i])
                printf("Process finished: %d\n", i);

            pid_exist[i] = vec[i];
        }

        sleep(1);
        
    }

    free(vec);

    return NULL;
}

// // Example thread function
// void *usage_monitor(void *tid) {
//   // Code that will be executed by the new thread
//   printf("Thread is running\n");
//   // Return a value from the thread (optional)
//   pthread_exit(NULL); // Terminates the thread
// }
