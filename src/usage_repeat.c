#include "usage_repeat.h"

double* usage_repeat(int *array) {
    static double result[3];

    result[0] = array[0] - stats[0];
    result[1] = array[1] - stats[1];
    result[2] = array[2] - stats[2];

    return result;
}
