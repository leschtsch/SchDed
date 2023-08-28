#include "io.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

int find_flags(int argc, char *argv[])
{
    assert(argc > 0);
    assert(argv);

    int process_res = 0;

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '\0')
            continue;

        if (is_number(argv[i]))
            continue;

        process_res = process_flag(argv[i]);
        if (process_res)
            return process_res;
    }

    return 0;
}

int input(int argc, char *argv[], sParams* params)
{
    assert(argc > 0);
    assert(argv);
    assert(params);

    int inp_cl_res = ERR_CLI_TOO_FEW_NUM;

    if (argc > 1)
        inp_cl_res = input_cl(argc, argv, params);

    if (inp_cl_res != ERR_CLI_TOO_FEW_NUM)
        return inp_cl_res;
    process_error(inp_cl_res);

    printf("Введите коэффициэнты - три числа:\n");
    fflush(stdout);

    if (scanf("%lf %lf %lf", &params->a, &params->b, &params->c) < 3)
        return ERR_BAD_INPUT;

    return OK;
}

int input_cl(int argc, char *argv[], sParams* params) //tODO - cli
{
    assert(argc > 0);
    assert(argv);
    assert(params);

    double numbers[3]={0, 0, 0};
    int ni = 0;

    double tmp_num = 0;

    for (int i = 1;  i < argc; i++)
    {

        if (argv[i][0] == '\0')
            continue;

        if (!sscanf(argv[i],"%lf", &tmp_num))
            continue;

        if (ni >= 3)
            return ERR_CLI_TOO_MANY_NUM;
        else
            numbers[ni++] = tmp_num;

    }

    if (ni < 3)
        return ERR_CLI_TOO_FEW_NUM;

    params->a = numbers[0];
    params->b = numbers[1];
    params->c = numbers[2];

    return OK;
}

int process_flag(const char * arg)
{
    assert(arg);

    int tmp_num = 0;
    if (sscanf(arg, "-t%d", &tmp_num))
    {
        FLAGS.RUN_TESTS = 1;
        FLAGS.SOLVE_EQUATION = 0;

        if (tmp_num > 0)
            TESTS_N = tmp_num;

        return OK;
    } else if (sscanf(arg, "-p%d", &tmp_num))
    {
        FLAGS.PRINT_TESTS_REM = 1;

        if (tmp_num > 0)
            PRINT_TESTS_REM_FREQ = tmp_num;

        return OK;
    }
    else if (strcmp(arg, "-s") == 0)
    {
        FLAGS.SOLVE_EQUATION = 1;

        return OK;
    }
    else if (strcmp(arg, "-h") == 0 ||
             strcmp(arg, "--help") == 0)
    {
        FLAGS = {};
        FLAGS.PRINT_HELP = 1;

        return OK;
    }
    return ERR_CLI_BAD_ARG;
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
        printf("нет корней.\n");
        break;
    case 1:
        printf("1 корень: %f.\n", solution->x1);
        break;
    case 2:
        printf("2 корня: %f, %f.\n", solution->x1, solution->x2);
        break;
    case INFTY:
        printf("бесконечно много корней.\n");
        break;
    default:
        fprintf(stderr, "\nERROR: output(): solution.rnum == %d\n", solution->rnum);
        break;
    }
}

void fix_zero(sSolution *solution)
{
    assert(solution);
    assert(solution->x1 < solution->x2 || solution->rnum < 2);

    if (cmp_double(solution->x1, .0))
        solution->x1 = .0;
    if (cmp_double(solution->x2, .0))
        solution->x2 = .0;
}
