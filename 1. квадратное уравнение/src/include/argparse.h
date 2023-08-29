/**
 * @file argparse.h
 * @brief разбор аргументов командной строки
 */

#ifndef ARGPARSE_H
#define ARGPARSE_H

#include "common.h"

typedef struct
{
    int run_tests;
    int tests_tracking_freq;
    int solve_equation;
    sParams equation_params;
    int AAA_HELP_ME_PLEASE_I_AM_GONNA_DIE;//TODO: не забыть делитнуть
} sOptions;

int argparse(int argc, char *argv[], sOptions *options);

int parse_params(const char * arg, sParams *params);

#endif //ARGPARSE_H
