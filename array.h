#ifndef ARRAYS_H
#define ARRAYS_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double* full_elements(double* ptr_array, int size) {
    for (int i = 0; i < size; i++) {
        double x = 1.3 + i * 0.1;
        ptr_array[i] = 5 * pow(x, 3) + 2 * pow(x, 2) - 15 * x - 6;
    }
    return ptr_array;
}

int put_elements(double* ptr_array, int size) {
    printf("\na[%d] =", size);

    for (int i = 0; i < size; i++)
    {
        printf(" %.2f", ptr_array[i]);
    }
}

double* calc_elements(double* ptr_array, int size) {
    for (int i = 0; i < size; i++)
    {
        ptr_array[i] = ceilf(ptr_array[i]);
    }
    return ptr_array;
}

double* fill_random(double* ptr_array, int size) {
    for (int i = 0; i < size; i++) {
        ptr_array[i] = (rand() % 201 - 100) / 100.0;
    }
    return ptr_array;
}



#endif
