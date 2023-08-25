/**
 * @mainpage Квадратка
 *
 * Первая задача с летней школы Деда.
 * Требуется написать программу, решающую квадратное уравнение,
 * А потом на нее вешается куча всего. O`_o
 *
 * @see process_flag, solve_general, run_tests, main.cpp
 */

/**
 * @file main.cpp
 * @brief первый и единственный файл
 */

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
    //int input_res = input(argc, argv, &params);
    int input_res = find_flags(argc, argv);

    if (input_res)
    {
        process_error(input_res);
        return -1;
    }

    if (FLAGS.RUN_TESTS && run_tests(TESTS_N))
        return -1;

    if (FLAGS.SOLVE_EQUATION)
    {
        sParams params = {.0, .0, .0};

        input_res = input(argc, argv, &params);
        if (input_res)
        {
            process_error(input_res);
            return -1;
        }

        sSolution solution = {0, .0, .0};
        solve_general(&params, &solution);

        output(&solution);
    }

    return 0;
}
