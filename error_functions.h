#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int handle_error_not_enough_args(int args)
{
    if (args < 2) {
        printf("Error: Not enough arguments.");
        exit(1);
        return 0;
    }
}
