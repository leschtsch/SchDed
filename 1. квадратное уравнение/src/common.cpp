/**
 * @file common.cpp
 * @brief Общие функции и прочее.
 */

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/common.h"

bool is_equal_double(double a, double b)
{
    assert(isfinite(a));
    assert(isfinite(b));

    return (fabs(a - b) < EPS);
}

bool is_equal_sSolution(const sSolution *a, const sSolution *b)
{
    assert(a);
    assert(b);
    assert(a->x1 < a->x2 || a->rnum < 2);
    assert(b->x1 < b->x2 || b->rnum < 2);

    return (a->rnum == b->rnum && is_equal_double(a->x1, b->x1) && is_equal_double(a->x2, b->x2));
}

double random_ab(double a, double b)
{
    assert(a <= b);

    if (is_equal_double(a, b))
        return a;

    return (double) rand() / RAND_MAX * (b - a) + a;
}

double random_ab_nz(double a, double b)
{
    assert (!is_zero(a) || !is_zero(b));
    assert(a <= b);

    if (is_equal_double(a,b))
        return a;
    if (is_zero(a))
        return random_ab(EPS, b);
    if (is_zero(b))
        return random_ab(a, -EPS);

    if(a > 0 || b < 0)
        return random_ab(a, b);


    /*
    if (random_ab(0,1) < (0 - a) / (b - a))
        return random_ab(a, -EPS);
    else
        return random_ab(EPS, b);
    !!! - это какого-то выдает на грани точности*/

    double res = random_ab(a, b);

    return (is_zero(res)) ? res - EPS : res; //ну будет слегка кринж с распределением, ок
    /*
     * Без разницы, + или - EPS, так как случай,
     * когда одна из границ 0 разобран
     */
};

void my_swap (double * a, double * b)
{
    assert(a);
    assert(b);

    assert(isfinite(*a));
    assert(isfinite(*b));

    double tmp = *a;
    *a = *b;
    *b = tmp;
}

void process_error(int err_code)
{
    switch (err_code)
    {
        case OK:
        {
            printf("process_error(OK): OK.\n");
            break;
        }

        case ERR_BAD_INPUT:
        {
            printf("Аргументы введены неверно / ошибка ввода.\n");
            break;
        }

        case ERR_CLI_BAD_ARG:
        {
            printf("Неизвестный аргумент (флаг) командной строки.\n"
                   "Помощь: --help, -h\n"
            );
            break;
        }

        case HELP_ASKED:
        {
            break;
        }

        default:
        {
            fprintf(stderr, "\nERROR: process_error(): unknown error %d.\n", err_code);
            break;
        }
    }
}
