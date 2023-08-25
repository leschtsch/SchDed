#include "common.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


int cmp_double(double a, double b)
{
    return (fabs(a - b) < EPS);
}

int cmp_sSolution(const sSolution *a, const sSolution *b)
{
    return (a->rnum == b->rnum && cmp_double(a->x1, b->x1) && cmp_double(a->x2, b->x2));
} //TODO (#1#): ассерты правильности структур в этой функции и после всяких return'ов

double random_ab(double a, double b)
{
    assert(a < b);

    if (cmp_double(a, b))
        return a;

    double res =  (double) rand() / RAND_MAX * (b - a) + a;
    return round(res / EPS) * EPS; // иначе беды с маленькими значениями
}

double random_ab_nz(double a, double b)
{
    assert(a < b);

    if (cmp_double(a,b))
        return a;
    if (cmp_double(a, 0))
        return random_ab(EPS, b);
    if (cmp_double(b, 0))
        return random_ab(a, -EPS);
    if(a > 0 || b < 0)
        return random_ab(a, b);


    if (random_ab(0,1) < (0 - a) / (b - a))
        return random_ab(a, -EPS);
    else
        return random_ab(EPS, b); // какого-то выдает на грани точности

    double res = random_ab(a, b);
    return (cmp_double(res, 0)) ? res - EPS : res; // ну будет слегка кринж с распределением, ок
};

void my_swap (double * a, double * b)
{
    double tmp = *a;
    *a = *b;
    *b = tmp;
}

int is_number(char * s)
{
    char * p = s;
    strtod(s, &p);

    return (p != s && *p == '\0');
}

void process_error(int err_code)
{
    switch (err_code)
    {
    case OK:
        printf("process_error(OK): OK.\n");
        break;

    case ERR_BAD_INPUT:
        printf("Аргументы введены неверно / ошибка ввода.\n");
        break;

    case ERR_CLI_BAD_ARG:
        printf("Неизвестный аргумент (флаг) командной строки. Известные флаги:\n"
               "\t-t[num] Запускает num тестов. Если num отсутствует "
               "или <= 0, запускается кол-во тестов по умолчанию. "
               "Отключает решение уравнения.\n"
               "\t-s Включает решение уранения. Должен идти после отключения.\n"
        );
        break;

    case ERR_CLI_TOO_FEW_NUM:
        printf("Недостаточно чисел в командной строке.\n");
        break;

    case ERR_CLI_TOO_MANY_NUM:
        printf("Слишком много чисел в командной строке.\n");
        break;

    default:
        fprintf(stderr, "\nERROR: process_error(): unknown error %d.\n", err_code);
        break;
    }
}
