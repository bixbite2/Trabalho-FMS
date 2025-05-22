#include "usage_repeat.h"
#include "usage_monitor.h"
#include <stdio.h>
#include <stdlib.h>

double resources_left[3];

void* usage_repeat(void *arg) {
    thread_arg_t *data = (thread_arg_t *)arg;
    int *params = data->params;
    static int result = 1;  // Initially true

    FILE *last_usage = fopen("last_usage", "r");
    if (!last_usage) {
        perror("fopen");
        return NULL;
    }

    for (int i = 0; i < 3; i++) {
        if (fscanf(last_usage, "%lf", &resources_left[i]) != 1) {
            fprintf(stderr, "Erro ao ler recurso %d de last_usage\n", i);
            fclose(last_usage);
            return NULL;
        }
        // Check if any resource is greater than its parameter
        if (resources_left[i] > params[i]) {
            result = 0;  // Return false if any resource exceeds its limit
            break;
        }
    }

    printf("resources_left: %.2f %.2f %.2f\n", resources_left[0], resources_left[1], resources_left[2]);
    printf("Parametros: %d %d %d\n", params[0], params[1], params[2]);
    fclose(last_usage);
    
    int *ret = malloc(sizeof(int));
    *ret = result;
    return ret;
}

