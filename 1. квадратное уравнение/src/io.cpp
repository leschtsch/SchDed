/**
 * @file io.cpp
 * @brief Функци ввода-вывода.
 */

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/io.h"
#include "include/common.h"

eErrors input_params(int argc, const char * const argv[], sParams* params)
{
    assert(argc > 0);
    assert(argv);
    assert(params);

    printf("Введите коэффициэнты - три числа через пробелы:\n");
    fflush(stdout);

    if (scanf("%lf %lf %lf", &params->a, &params->b, &params->c) != 3)
        return ERR_BAD_INPUT;

    return OK;
}

void output(sSolution *solution)
{
    assert(solution);
    assert(solution->x1 < solution->x2 || solution->rnum < 2);

    fix_zero(solution);

    printf("У уравнения ");
    switch (solution->rnum)
    {
        case 0:
        {
            printf("нет корней.\n");
            break;
        }

        case 1:
        {
            printf("1 корень: %f.\n", solution->x1);
            break;
        }

        case 2:
        {
            printf("2 корня: %f, %f.\n", solution->x1, solution->x2);
            break;
        }

        case INFINITY_ROOTS:
        {
            printf("бесконечно много корней.\n");
            break;
        }

        default:
        {
            fprintf(stderr, "\nERROR: output(): solution.rnum == %d\n", solution->rnum);
            break;
        }
    }
}

void fix_zero(sSolution *solution)
{
    assert(solution);
    assert(solution->x1 < solution->x2 || solution->rnum < 2);

    if (is_zero(solution->x1))
        solution->x1 = .0;
    if (is_zero(solution->x2))
        solution->x2 = .0;
}
