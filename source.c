#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct date
{
    int day;
    int mon;
    int year;
}DATE;

int getDayNum(DATE);
int inputData(DATE**);
void printData(DATE**, size_t);
int deleteValues(DATE** new_arr, DATE** arr, size_t size, DATE begin_val, DATE end_val);
int inputDataFromFile(DATE**);

int main(void)
{
    system("chcp 1251");
    DATE* arr = NULL;
    DATE* new_arr = NULL;
    int size = 0;
    int new_size = 0;
    DATE range_begin;
    DATE range_end;
    int flag = 0;
    printf("Введіть 1 для зчитування з файлу або 2 для зчитування з консолі ");
    scanf("%d", &flag);
    if (flag == 2) {
        size = inputData(&arr);
    }
    else {
        size = inputDataFromFile(&arr);
    }
    printData(&arr, size);
    printf("Введіть початок діапазону дат, що потрібно вилучити: ");
    scanf("%d.%d.%d", &range_begin.day, &range_begin.mon, &range_begin.year);
    printf("Введіть кінець діапазону дат, що потрібно вилучити: ");
    scanf("%d.%d.%d", &range_end.day, &range_end.mon, &range_end.year);
    new_size = deleteValues(&new_arr, &arr, size, range_begin, range_end);
    free(arr);
    new_arr = realloc(new_arr, new_size * sizeof(DATE));
    printf("===============================\n");
    printData(&new_arr, new_size);

    free(new_arr);
    system("pause");
    return 0;
}

int deleteValues(DATE** new_arr, DATE** arr, size_t size, DATE begin_val, DATE end_val)
{
    *new_arr = malloc(sizeof(DATE) * size);
    int begin = getDayNum(begin_val);
    int end = getDayNum(end_val);
    int num_count = 0, new_size = 0;
    for (int i = 0; i < size; i++)
    {
        num_count = getDayNum((*arr)[i]);
        if (num_count > end || num_count < begin)
        {
            (*new_arr)[new_size] = (*arr)[i];
            new_size++;
        }
    }
    return new_size;
}

int inputDataFromFile(DATE** arr)
{
    int size = 1;
    FILE* fin;
    char file_name[260];
    *arr = malloc(sizeof(DATE));
    printf("Введіть повний шлях до файлу і його назву:");
    scanf("%s", file_name);
    if ((fin = fopen(file_name, "r")) == NULL)
    {
        printf("Неможливо відкрити файл");
        exit(1);
    }
    for (int i = 0; EOF != fscanf(fin, "%d.%d.%d", &(*arr)[i].day, &(*arr)[i].mon, &(*arr)[i].year); i++, size++)
        *arr = realloc(*arr, ((1 + size) * sizeof(DATE)));
    *arr = realloc(*arr, (--size * sizeof(DATE)));
    fclose(fin);
    return size;
}

int inputData(DATE** arr)
{
    int size = 1;
    *arr = malloc(sizeof(DATE));
    printf("Введіть послідовність дат у форматі ДД.ММ.РРРР. Щоб перервати ввід, введіть будь-яку цифру\n");
    for (int i = 0; scanf("%d.%d.%d", &(*arr)[i].day, &(*arr)[i].mon, &(*arr)[i].year) == 3; i++, size++)
        *arr = realloc(*arr, ((1 + size) * sizeof(DATE)));
    *arr = realloc(*arr, (--size * sizeof(DATE)));
    return size;
}

void printData(DATE** arr, size_t size)
{
    for (int i = 0; i < size; i++)
        printf("%d.%d.%d\n", (*arr)[i].day, (*arr)[i].mon, (*arr)[i].year);
}

int getDayNum(DATE obj)
{
    int mon_days[] = { 31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30 };
    int num = obj.day;
    mon_days[1] = ((obj.year % 4 == 0 && obj.year % 100 != 0) || (obj.year % 400 == 0)) ? 29 : 28;
    for (int i = 0; i < obj.mon - 1; i++)
        num += mon_days[i];
    return num;
}
