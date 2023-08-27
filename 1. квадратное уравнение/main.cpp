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
int PRINT_TESTS_REM_FREQ = 1;

sFlags FLAGS = {
                .RUN_TESTS = 0,
                .SOLVE_EQUATION = 1,
                .PRINT_HELP = 0,
                .PRINT_TESTS_REM  = 0,
               };

const char HELP_MSG[] = "Некоторые флаги отключают другие. Чтобы включить "
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
                        "\t-h, --help Выводит помощь. Отключает остальное.";

/**
 * @see input, process_error, solve_general, output
 */
int main(int argc, char *argv[])
{
    int input_res = find_flags(argc, argv);

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
