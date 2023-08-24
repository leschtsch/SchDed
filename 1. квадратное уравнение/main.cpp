/**
 * @mainpage Квадратка
 *
 * Первая задача с летней школы Деда.
 * Требуется написать программу, решающую квадратное уравнение,
 * А потом на нее вешается куча всего. O`_o
 *
 * @see solve_general, run_tests, main.cpp
 */

/**
 * @file main.cpp
 * @brief первый и единственный файл
 */

// TODO - доки файлов
// TODO - readme

#include "TXLib.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "tests.h"
#include "solve.h"
#include "io.h"
#include "common.h"

int TESTS_N = (int) 2e7;
sFlags FLAGS = {0, 1};


/**
 * @see input, process_error, solve_general, output
 */
int main(int argc, char *argv[])
{
    sParams params = {.0, .0, .0};
    int input_res = input(argc, argv, &params);

    if (input_res)
    {
        process_error(input_res);
        return -1;
    }

    if (FLAGS.RUN_TESTS)
    {
        assert(TESTS_N > 0);

        int tf = run_tests(TESTS_N);
        printf("тестов провалено: %d / %d, доля ошибок: %f\n", tf, TESTS_N, (double) tf / TESTS_N); //TODO - stdin и stderr путаются
        return tf;
    }

    sSolution solution = {0, .0, .0};
    solve_general(&params, &solution);
    output(&solution);

    return 0;
}
