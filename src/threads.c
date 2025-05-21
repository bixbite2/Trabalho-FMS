#include "usage_monitor.h"
#include "process_created.h"
#include "usage_interface.h"
#include <pthread.h>

void *thread_created_function(void *arg){
    thread_arg_t args[NUMBER_THREADS];
    pthread_t threads[NUMBER_THREADS];
    
    thread_arg_t *info = (thread_arg_t *)arg;
    int id = info -> tid;
    int process_id = info -> pid;
    // int *params = info -> params;
    int *usage_params = get_usage_params();



    for(int i=0; i < NUMBER_THREADS; i++) {
        printf("Metodo Main. Criando thread %d\n", i);
        args[i].tid = i;
        args[i].pid = process_id;
        args[i].params = usage_params;
        //status = pthread_create(&threads[i], NULL, usage_monitor, (void *)i);
        int status = pthread_create(&threads[i], NULL, usage_monitor, &args[i]);
        // pthread_join(threads[i], NULL);
        if (status != 0) {
            printf("Oops. pthread create returned error code %d\n", status);
            exit(EXIT_FAILURE);
        }
    }

    return NULL;
}
