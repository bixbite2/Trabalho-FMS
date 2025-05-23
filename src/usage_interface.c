#include "usage_interface.h"

int* get_usage_params() {
    size_t zero = 0;
    char *input = NULL;
    int *usage_params = malloc(3 * sizeof(int));

    printf("Tempo maximo de CPU: ");
    getline(&input, &zero, stdin);
    usage_params[0] = atoi(input);

    printf("Tempo maximo de execução: ");
    getline(&input, &zero, stdin);
    usage_params[1] = atoi(input);

    printf("Uso máximo de RAM: ");
    getline(&input, &zero, stdin);
    usage_params[2] = atoi(input);

    free(input);
    return usage_params;
}

