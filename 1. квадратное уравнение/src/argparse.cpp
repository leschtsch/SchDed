/**
 * @file argparse.cpp
 * @brief Разбор аргументов командной строки.
 */

#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "include/argparse.h"
#include "include/common.h"
#include "include/config.h"

extern const char OPT_TESTS_LONG[] = "run-tests";           ///< Длинная опция запуска тестов.
extern const char OPT_PROGRESS_LONG[] = "track_progress";   ///< Длиная опция отслеживания прогресса.
extern const char OPT_SOLVE_LONG[] = "solve-equation";      ///< Длинная опция решения уравнения.
extern const char OPT_HELP_LONG[] = "help";                 ///< Длинная опция помощи.


extern const char HELP_MSG[] = "Некоторые опции отключают другие. Чтобы включить "
                        "опцию обратно, нужно написать эту опцию после "
                        "отключения. По умолчанию включена -s.\n\n"
                        "Разрешенные опции:\n"
                        "\t-%c[num] --%s[=num] запускает num тестов. Если num отсутствует, "
                        "или <= 0, запускается кол-во тестов"
                        "по умолчанию. Отключает решение уравнения.\n"
                        "\t-%c[num] --%s[=num] Если производятся тесты, каждые num тестов "
                        "будет выводится, сколько тестов осталось "
                        "Если num отсутствует или <= 0, выводистя каждый тест.\n"
                        "\t-%c[a,b,c] --%s[=a,b,c] Решает уравнение ax^2 + bx + c = 0. "
                        "Если параметры не указаны, они читаются из stdin.\n"
                        "\t-%c --%s Выводит помощь. Завершает программу.\n\n"; ///< Выводится при -h

eErrors parse_args(int argc, char * const argv[], sOptions *options)
{
    assert(argv);
    assert(options);

    char shortopts[] = "ht::p::s::";
    struct option longopts[] = {
                                    {OPT_HELP_LONG, 0, NULL, OPT_HELP_SHORT},
                                    {OPT_TESTS_LONG, 2, NULL, OPT_TESTS_SHORT},
                                    {OPT_PROGRESS_LONG, 2, NULL, OPT_PROGRESS_SHORT},
                                    {OPT_SOLVE_LONG, 2, NULL, OPT_SOLVE_SHORT},
                                    {NULL, 0, NULL, 0}
                               };

    int opt = 0;

    while (1)
    {
        if ((opt = getopt_long(argc, argv, shortopts, longopts, NULL)) == -1)
            break;

        switch (opt)
        {
            case OPT_HELP_SHORT:
            {
                print_help();
                return HELP_ASKED;
            }

            case OPT_TESTS_SHORT:
            {
                int tmp_num = 0;

                if (optarg && sscanf(optarg, "%d", &tmp_num) && tmp_num > 0)
                    options->tests_n = tmp_num;
                else
                    options->tests_n = TESTS_N_DEFAULT;

                options->solve_equation = DONT_SOLVE;
                break;
            }

            case OPT_PROGRESS_SHORT:
            {

                int tmp_num = 0;

                if (optarg && sscanf(optarg, "%d", &tmp_num) && tmp_num > 0)
                    options->tests_tracking_freq = tmp_num;
                else
                    options->tests_tracking_freq = TESTS_TRACKING_FREQ_DEFAULT;

                break;
            }

            case OPT_SOLVE_SHORT:
            {
                options->solve_equation = INPUT_PARAMS;

                if (!optarg)
                    break;

                eErrors parse_res = OK;
                if ((parse_res = parse_params(optarg, &options->equation_params)))
                    return parse_res;

                options->solve_equation = CLI_PARAMS;
                break;
            }

            default:
            {
                return ERR_CLI_BAD_ARG;
            }
        }
    }

    return OK;
}

eErrors parse_params(const char *arg, sParams *params)
{
    assert(params);
    assert(arg);

    if (sscanf(arg, "%lf,%lf,%lf", &params->a, &params->b, &params->c) != 3)
        return ERR_CLI_BAD_ARG;

    return OK;
}

void print_help(void)
{
    printf(
    HELP_MSG,
    OPT_TESTS_SHORT, OPT_TESTS_LONG,
    OPT_PROGRESS_SHORT, OPT_PROGRESS_LONG,
    OPT_SOLVE_SHORT, OPT_SOLVE_LONG,
    OPT_HELP_SHORT, OPT_HELP_LONG
    );
}
