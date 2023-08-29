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
                options->run_tests = 0;
                options->tests_tracking_freq = 0;
                options->solve_equation = 0;
                options->AAA_HELP_ME_PLEASE_I_AM_GONNA_DIE = 1;
                break;
            }

            case 't':
            {
                int tmp_num = 0;

                if (optarg && sscanf(optarg, "%d", &tmp_num) && tmp_num > 0)
                    options->run_tests = tmp_num;
                else
                    options->run_tests = TESTS_N;

                options->solve_equation = 0;
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
                options->solve_equation = 1;
                options->equation_params = {1, 2, 3};
                break; //TODO: доделать

                if (!optarg)
                    break;

                int parse_res  = 0;
                if ((parse_res = parse_params(optarg, &options->equation_params)))
                    return parse_res;
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
    *params = {.0, .0, .0}; //TODO сделать

    return OK;
}
