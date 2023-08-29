/**
 * @file argparse.cpp
 * @brief разбор аргументов командной строки
 */
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "include/argparse.h"
#include "include/common.h"
#include "include/config.h"

const char HELP_MSG[] = "Некоторые опции отключают другие. Чтобы включить "
                        "опцию обратно, нужно написать эту опцию после "
                        "отключения. По умолчанию включена -s.\n\n"
                        "Разрешенные опции:\n"
                        "\t-t[num] --run-tests[num] запускает num тестов. Если num отсутствует, "
                        "или <= 0, запускается кол-во тестов"
                        "по умолчанию. Отключает решение уравнения.\n"
                        "\t-p[num] --track_progress[num] Если производятся тесты, каждые num тестов "
                        "будет выводится, сколько тестов осталось "
                        "Если num отсутствует или <= 0, выводистя каждый тест.\n"
                        "\t-s[a,b,c] --solve-equation[a,b,c] Решает уравнение ax^2 + bx + c = 0. "
                        "Если параметры не указаны, они читаются из stdin.\n"
                        "\t-h, --help Выводит помощь. Завершает программу\n\n"; ///< Выводится при -h

int argparse(int argc, char *argv[], sOptions *options)
{
    assert(argv);

    assert(options);

    char shortopts[] = "ht::p::s::";
    struct option longopts[] = {
                                    {"help", 0, NULL, 'h'},
                                    {"run-tests", 2, NULL, 't'},
                                    {"track-progress", 2, NULL, 'p'},
                                    {"solve-equation", 2, NULL, 's'},
                                    {NULL, 0, NULL, 0}
                               };

    int opt = 0;

    while (1)
    {
        if ((opt = getopt_long(argc, argv, shortopts, longopts, NULL)) == -1)
            break;

        switch (opt)
        {
            case 'h':
            {
                printf("%s\n", HELP_MSG);
                return HELP_ASKED;
            }

            case 't':
            {
                int tmp_num = 0;

                if (optarg && sscanf(optarg, "%d", &tmp_num) && tmp_num > 0)
                    options->run_tests = tmp_num;
                else
                    options->run_tests = TESTS_N;

                options->solve_equation = NO_SOLVE;
                break;
            }

            case 'p':
            {

                int tmp_num = 0;

                if (optarg && sscanf(optarg, "%d", &tmp_num) && tmp_num > 0)
                    options->tests_tracking_freq = tmp_num;
                else
                    options->tests_tracking_freq = PRINT_TESTS_REM_FREQ;

                break;
            }

            case 's':
            {
                options->solve_equation = INPUT_PARAMS;

                if (!optarg)
                    break;

                int parse_res = 0;
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

int parse_params(const char * arg, sParams *params)
{
    assert(params);
    assert(arg);

    if (sscanf(arg, "%lf,%lf,%lf", &params->a, &params->b, &params->c) < 3)
        return ERR_CLI_BAD_ARG;

    return OK;
}
