/**
 * @mainpage Квадратка
 *
 * @note Подробнее о флагах в описании функци process_flag.
 *
 * Первая задача с летней школы Деда.
 * Требуется написать программу, решающую квадратное уравнение,
 * А потом на нее вешается куча всего. O`_o
 *
 * @see solve_general, run_tests, main.cpp
 */

/**
 * @file main.cpp
 */

//TODO: норм ридми + англ(необ)?
//TODO: описание флагов
// например до -s числа это ошибка   getopt??
// какой-то гайд?

//  что это, как собрать, как юзать

#include "TXLib.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/io.h"
#include "include/argparse.h"
#include "include/tests.h"
#include "include/solve.h"
#include "include/common.h"
#include "include/config.h"

/**
 * @see input, process_error, solve_general, output
 */
int main(int argc, char *argv[])
{
    sOptions options = {
                        .run_tests = 0,
                        .tests_tracking_freq = 0,
                        .solve_equation = INPUT_PARAMS,
                        .equation_params = {0, 0, 0},
                     };

    int parsing_res = argparse(argc, argv, &options);

    if (parsing_res)
    {
        process_error(parsing_res);
        return parsing_res;
    }

    if (options.run_tests)
        run_tests(options.run_tests, options.tests_tracking_freq);

    if (options.solve_equation)
    {
        int input_res = 0;

        if (options.solve_equation == INPUT_PARAMS)
            input_res = input(argc, argv, &options.equation_params);

        if (input_res)
        {
            process_error(input_res);
            return -1;
        }

        sSolution solution = {0, .0, .0};
        solve_general(&options.equation_params, &solution);

        assert(solution.x1 < solution.x2 || solution.rnum < 2);

        output(&solution);
    }

    return 0;
}
