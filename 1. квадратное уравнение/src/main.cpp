/**
 * @mainpage Квадратка
 *
 * @note Подробнее о флагах в описании функци process_flag.
 *
 * Первая задача с летней школы Деда.
 * Требуется написать программу, решающую квадратное уравнение,
 * А потом на нее вешается куча всего. O`_o
 *
 * @see process_flag, solve_general, run_tests, main.cpp
 */

/**
 * @file main.cpp
 */

//TODO: норм ридми + англ(необ)?
//TODO: норм флаги - либо без чисел в аргументах либо вообще страшный парсинг жестб
// например до -s числа это ошибка   getopt??
// какой-то гайд?
// TODO: хедер конфига

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

int TESTS_N = (int) 2e7;  //TODO: не забыть делитнуть
int PRINT_TESTS_REM_FREQ = 1; //TODO: не забыть делитнуть

sFlags FLAGS = {
                .RUN_TESTS = 0,
                .SOLVE_EQUATION = 1,
                .PRINT_HELP = 0,
                .PRINT_TESTS_REM  = 0,
               }; //TODO: не забыть делитнуть

const char HELP_MSG[] = "Некоторые флаги отключают другие. Чтобы включить " //TODO: в хедер или в argparse
                        "флаг обратно, нужно написать этот флаг после "
                        "отключения. По умолчанию включен -s.\n \n"
                        "Разрешенные флаги:\n"
                        "\t-t[num] запускает num тестов. Если num отсутствует, "
                            "или <= 0, запускается кол-во тестов "
                        "по умолчанию. Отключает решение уравнения.\n"
                        "\t-p[num] Если производятся тесты, каждые num тестов "
                        "будет выводится, сколько тестов осталось "
                        "Если num отсутствует или <= 0, выводистя каждый тест.\n"
                        "\t-s Включает решение уранения.\n"
                        "\t-h, --help Выводит помощь. Отключает остальное."; ///< выводится при -h

/**
 * @see input, process_error, solve_general, output
 */
int main(int argc, char *argv[])
{
    sOptions options = {
                        .run_tests = 0,
                        .tests_tracking_freq = 0,
                        .solve_equation = 1,
                        .equation_params = {0, 0, 0},
                     };

    int parsing_res = argparse(argc, argv, &options);

    if (parsing_res)
        process_error(parsing_res);

    return parsing_res;

    int input_res = find_flags(argc, argv); //TODO: указ на структуру которая хранит config

    if (input_res)
    {
        process_error(input_res);
        return -1;
    }

    if (FLAGS.PRINT_HELP)
        printf("%s\n", HELP_MSG);

    if (FLAGS.RUN_TESTS)
        run_tests(TESTS_N);

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

        assert(solution.x1 < solution.x2 || solution.rnum < 2);

        output(&solution);
    }

    return 0;
}
