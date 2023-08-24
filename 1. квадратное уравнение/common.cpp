#include "common.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


int cmp_double(double a, double b)
{
    if (fabs(a - b) < EPS)
        return 0;
    return (a < b) ? -1 : 1;
}

int cmp_sSolution(const sSolution *a, const sSolution *b)// TODO - неинтуитивно
{
    if (a->rnum != b->rnum)
        return (a->rnum < b->rnum) ? -1 : 1;
    int cmp_res = cmp_double(a->x1, b->x1);
    return (cmp_res) ? cmp_res : cmp_double(a->x2, b->x2);
} //TODO - ассерты правильности структур в этой функции и после всяких return'ов

double random_ab(double a, double b)
{
    assert(cmp_double(a, b) < 0);

    if (!cmp_double(a, b))
        return a;

    return (double) rand() / RAND_MAX * (b - a) + a;
}

double random_ab_nz(double a, double b)
{
    double res = random_ab(a, b); // TODO - формула без 0 а не это вот всерооролры
    while (!cmp_double(res, .0))// вероятность этого крайне мала 1!!1!1
        res = random_ab(a, b);
    return res;
};

void swap (double * a, double * b) ..TODO - myswap
{
    double tmp = *a;
    *a = *b;
    *b = tmp;
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

    case ERR_BAD_CL_ARG:
        printf("Неизвестный аргумент командной строки.\n");
        break;

    case ERR_LACK_CL_NUM:
        printf("Недостаточно чисел в командной строке.\n");
        break;

    case ERR_MANY_CL_NUM:
        printf("Слишком много чисел в командной строке.\n");
        break;

    default:
        fprintf(stderr, "\nERROR: process_error(): unknown error %d.\n", err_code);
        break;
    }
}
