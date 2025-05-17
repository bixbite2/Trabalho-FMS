#include "error_functions.h"

void handle_error_not_enough_args(int args)
{
    if (args < 2) {
        printf("Error: Not enough arguments.");
        exit(1);
    }
}

