#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <time.h>
#include "array.h"

double* full_elements(double* ptr_array, int size);
int put_elements(double* ptr_array, int size);
double* calc_elements(double* ptr_array, int size);
double* fill_random(double* ptr_array, int size);
int delete_k(double* ptr_arr, int size, double element);
int find_last_negative(double* ptr_arr, int size);
double* insert(double* ptr_arr, int* size, int index, double num);

int main() {
    setlocale(LC_ALL, "");
    srand(time(NULL));

    double* ptr_array;
    int size, size2;
    double element;

    printf("Введите размер массива: ");
    scanf("%d", &size);

    ptr_array = (double*)malloc(size * sizeof(double));

    if (ptr_array == NULL) {

        puts("error");

        return -1;
    }

    full_elements(ptr_array, size);

    printf("Начальный массив: ");
    put_elements(ptr_array, size);

    calc_elements(ptr_array, size);

    printf("\nМассив после изменения: ");
    put_elements(ptr_array, size);

    free(ptr_array);

    printf("\n\nЛР 16: часть 2\n");

    printf("Введите размер массива для задания 2: ");
    scanf("%d", &size2);

    double* arr2 = (double*)malloc(size2 * sizeof(double));
    if (arr2 == NULL) {

        puts("error");

        return -1;
    }

    fill_random(arr2, size2);
    printf("\nМассив со случайными числами от -1 до 1:\n");
    put_elements(arr2, size2);

    printf("\n\n2.1 Удаление элементов > A \n");
    printf("Введите значение A: ");
    scanf("%lf", &element);

    int new_size = delete_k(arr2, size2, element);
    printf("Массив после удаления элементов:\n");
    put_elements(arr2, new_size);

    printf("\n\n2.2 Вставка -999 после последнего отрицательного\n");

    int last_negative_index = find_last_negative(arr2, new_size);

    if (last_negative_index != -1) {
        arr2 = insert(arr2, &new_size, last_negative_index + 1, -999.0);
        printf("Массив после вставки -999:\n");
        put_elements(arr2, new_size);
    }
    else {
        printf("Отрицательных элементов не найдено.\n");
    }

    free(arr2);

    return 0;
}


int delete_k(double* ptr_arr, int size, double element) {
    int new_size = 0;
    for (int i = 0; i < size; i++) {
        if (ptr_arr[i] <= element) {
            ptr_arr[new_size] = ptr_arr[i];
            new_size++;
        }
    }

    printf("Удалено элементов: %d\n", size - new_size);
    return new_size;
}

int find_last_negative(double* ptr_arr, int size) {
    int last_index = -1;
    for (int i = 0; i < size; i++) {
        if (ptr_arr[i] < 0) {
            last_index = i;
        }
    }
    return last_index;
}

double* insert(double* ptr_arr, int* size, int index, double num) {
    int size_n = (*size) + 1;

    if (ptr_arr == NULL) return NULL;

    double* ptr_arr_n = (double*)realloc(ptr_arr, size_n * sizeof(double));
    if (ptr_arr_n == NULL) return ptr_arr;

    ptr_arr = ptr_arr_n;

    for (int i = size_n - 1; i > index; i--) {
        ptr_arr[i] = ptr_arr[i - 1];
    }

    ptr_arr[index] = num;
    *size = size_n;

    return ptr_arr;
}