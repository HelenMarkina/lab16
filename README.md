# Лабораторная работа 16

## Условие задачи
Работа с динамическими массивами вещественных чисел, включающая два задания:
1. Создание и обработка массива значений математической функции
2. Работа с массивом случайных чисел: удаление элементов и вставка нового элемента

## 1. Алгоритм и блок-схема

### Алгоритм

#### Задание 1
1. **Начало**
2. Ввести размер первого массива
3. Выделить динамическую память под массив
4. Заполнить массив значениями функции: `f(x) = 5x³ + 2x² - 15x - 6`, где `x = 1.3 + i * 0.1`
5. Вывести исходный массив
6. Округлить все элементы массива вверх (функция `ceilf()`)
7. Вывести измененный массив
8. Освободить память

#### Задание 2
1. Ввести размер второго массива
2. Выделить динамическую память под массив
3. Заполнить массив случайными числами в диапазоне [-1.00, 1.00]
4. Вывести исходный массив
5. Ввести значение A
6. Удалить все элементы массива, превышающие значение A
7. Вывести массив после удаления элементов
8. Найти индекс последнего отрицательного элемента
9. Если отрицательный элемент найден:
   - Вставить значение -999 после него
   - Вывести массив после вставки
10. Иначе: вывести сообщение об отсутствии отрицательных элементов
11. Освободить память
12. **Конец**

## 2. Реализация программы

```c
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <time.h>

// Прототипы функций
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

    // Задание 1
    printf("Введите размер массива: ");
    scanf("%d", &size);

    ptr_array = (double*)malloc(size * sizeof(double));
    if (ptr_array == NULL) {
        puts("Ошибка выделения памяти");
        return -1;
    }

    full_elements(ptr_array, size);
    printf("Начальный массив: ");
    put_elements(ptr_array, size);

    calc_elements(ptr_array, size);
    printf("\nМассив после изменения: ");
    put_elements(ptr_array, size);

    free(ptr_array);

    // Задание 2
    printf("\n\nЛР 16: часть 2\n");
    printf("Введите размер массива для задания 2: ");
    scanf("%d", &size2);

    double* arr2 = (double*)malloc(size2 * sizeof(double));
    if (arr2 == NULL) {
        puts("Ошибка выделения памяти");
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

// Функции реализаций
double* full_elements(double* ptr_array, int size) {
    for (int i = 0; i < size; i++) {
        double x = 1.3 + i * 0.1;
        ptr_array[i] = 5 * pow(x, 3) + 2 * pow(x, 2) - 15 * x - 6;
    }
    return ptr_array;
}

int put_elements(double* ptr_array, int size) {
    printf("\na[%d] =", size);
    for (int i = 0; i < size; i++) {
        printf(" %.2f", ptr_array[i]);
    }
    return 0;
}

double* calc_elements(double* ptr_array, int size) {
    for (int i = 0; i < size; i++) {
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
```

## 3. Результаты работы программы

```
Введите размер массива: 5
Начальный массив: 
a[5] = -13.33 -12.44 -11.41 -10.24 -8.93
Массив после изменения: 
a[5] = -13.00 -12.00 -11.00 -10.00 -8.00

ЛР 16: часть 2
Введите размер массива для задания 2: 6
Массив со случайными числами от -1 до 1:
a[6] = 0.12 -0.45 0.89 -0.23 0.56 -0.91

2.1 Удаление элементов > A 
Введите значение A: 0.5
Удалено элементов: 2
Массив после удаления элементов:
a[4] = 0.12 -0.45 -0.23 -0.91

2.2 Вставка -999 после последнего отрицательного
Массив после вставки -999:
a[5] = 0.12 -0.45 -0.23 -0.91 -999.00
```

## Информация о разработчике
Маркина Елена, группа бТИИ-251

## 4. Информация о разработчике

Маркина Елена, группа бТИИ-251
