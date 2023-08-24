#include "io.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"

int input(int argc, char *argv[], sParams* params)
{
    assert(params!=NULL);

    int inp_cl_res = ERR_LACK_CL_NUM;
    if (argc > 1)
        inp_cl_res = input_cl(argc, argv, params);

    if (inp_cl_res != ERR_LACK_CL_NUM) // расшифровать CLI, TO_FEW
        return inp_cl_res;
    if (!FLAGS.SOLVE_EQUATION)
        return 0;

    process_error(inp_cl_res);
    printf("Введите коэффициэнты - три числа:\n");

    fflush(stdout);

    if (scanf("%lf %lf %lf", &params->a, &params->b, &params->c) < 3)
        return ERR_BAD_INPUT;

    return OK;
}

int input_cl(int argc, char *argv[], sParams* params)
{
    assert(params!=NULL);

    double numbers[3]={0, 0, 0};
    int ni = 0;

    char * p = NULL;

    double tmp_num = 0;
    int processing_res = 0;

    for (int i = 1;  i < argc; i++)
    {
        processing_res = 0;

        if (argv[i][0] == '\0')
            continue;

        tmp_num = strtod(argv[i],&p); // TODO - sscanf?
        if (*p == '\0' && ni >= 3)
            return ERR_MANY_CL_NUM;
        else if (*p == '\0' && ni < 3)
            numbers[ni++] = tmp_num;
        else
        {
            processing_res = process_arg(argv[i]);
        }

        if (processing_res)
            return processing_res;
    }

    if (ni < 3)
        return ERR_LACK_CL_NUM;

    params->a = numbers[0];
    params->b = numbers[1];
    params->c = numbers[2];

    return OK;
}

int process_arg(const char * arg)
{
    if (arg[0] != '-' || arg[1] != 't')
        return ERR_BAD_CL_ARG;

    FLAGS.RUN_TESTS = 1;
    FLAGS.SOLVE_EQUATION = 0;
    arg += 2;

    char *p = NULL;
    int tmp = strtol(arg, &p, 10);
    if (*p == '\0' && p != arg && tmp > 0)
        TESTS_N = tmp;

    return OK;
}


void output(sSolution *solution)
{
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
    assert(solution != NULL);

    if (!cmp_double(solution->x1, .0))
        solution->x1 = .0;
    if (!cmp_double(solution->x2, .0))
        solution->x2 = .0;
}
