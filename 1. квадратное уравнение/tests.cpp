#include "tests.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "solve.h"
#include "common.h"

int run_tests(int tests_n)
{
    assert(tests_n > 0);

    int tests_failed = 0;
    for(;tests_n;tests_n--)
    {
        sParams params = {.0, .0, .0};
        sSolution ref_solution = {0, .0, .0};
        gen_test(&params, &ref_solution);

        if (run_test(&params, &ref_solution))
            tests_failed++;
    }
    return tests_failed;
}

void gen_test(sParams* params, sSolution *solution)
{
    switch (rand() % 6) // не лучший способ, но простой
    {
    case 0:  //TODO - массив указ на функции
        gen_test_0_roots_deg0(params, solution);
        break;

    case 1:
        gen_test_0_roots_deg0(params, solution);
        break;

    case 2:
        gen_test_1_root_deg1(params, solution);
        break;

    case 3:
        gen_test_1_root_deg2(params, solution);
        break;

    case 4:
        gen_test_2_roots(params, solution);
        break;

    case 5:
        gen_test_INFTY_roots(params, solution);
        break;

    default:
        fprintf(stderr,"\nERRROR: gen_test(): unknown test type\n");
        break;
    }
}

void gen_test_0_roots_deg0(sParams* params, sSolution *solution)
{
    double c = random_ab_nz(-TEST_RANGE, TEST_RANGE);
    *params = {.0, .0, c};
    *solution = {0, .0, .0};
}

void gen_test_0_roots_deg2(sParams* params, sSolution *solution)
{
    double a = random_ab_nz(EPS, TEST_RANGE);
    double b = random_ab(-TEST_RANGE, TEST_RANGE);

    double y  = - (b * b) / (4 * a); // y вершины, если  c = 0
    /*
     *  y                           =
     *  ax^2+bx                     =
     *  a*(-b/2a)^2 + b*(-b/2a)     =
     *  a* b^2 / 4a^2 - b^2 / 2a    =
     *  b^2 / 4a - 2b^2 / 4a        =
     *  - b^2 / 4a
     *
     * Порядок дискриминанта - TETS_RANGE^2
     */

    double c = random_ab(-y+EPS, y + TEST_RANGE);

    *params = (sParams){a, b, c};
    *solution = {0, .0, .0};

}

void gen_test_1_root_deg1(sParams* params, sSolution *solution)
{
    if (random_ab(0,1) < ROOTS_0_PROB)
    {
        *params  = {.0, random_ab_nz(-TEST_RANGE, TEST_RANGE), .0};
        *solution = {1, .0, .0};
        return;
    }

    double x = random_ab_nz(-TEST_RANGE, TEST_RANGE);

    double c = random_ab_nz(-TEST_RANGE, TEST_RANGE);

    *params = {.0, - c / x, c};
    *solution = {1, x, .0};
}

void gen_test_1_root_deg2(sParams* params, sSolution *solution)
{
    if (random_ab(0,1)<ROOTS_0_PROB)
    {
        *params  = {random_ab_nz(-TEST_RANGE, TEST_RANGE), 0, .0};
        *solution = {1, .0, .0};
        return;
    }

    double x = random_ab_nz(-TEST_RANGE, TEST_RANGE);
    double b = random_ab(-TEST_RANGE, TEST_RANGE);

    *params= (sParams){-b / (2 * x), b, -(b * x)/2};
    /*  Здесь x - x вершины
     *
     *  1.  x = -b / 2a => a = -b / 2x
     *
     *  2.  b^2 - 4ac = 0       =>
     *      c = b^2 / 4a        =
     *      b^2 / (4 * -b / 2x) =
     *      -bx / 2
     *
     * Порядок дискриминанта - TETS_RANGE^2
     */
    *solution = {1, x, .0};
}

void gen_test_2_roots(sParams* params, sSolution *solution) //FIXME - лол крч в при оч мелких дискриминантах падает
{
    if ((random_ab(0,1) < ROOTS_0_PROB))
    {
        double x1 = random_ab_nz(EPS,TEST_RANGE);

        double c = -random_ab_nz(-TEST_RANGE, TEST_RANGE);
        double a = -c / (x1 * x1);

        *params = {a, 0, c};
        *solution = {2, -x1, x1};

    }

    double x1 = random_ab(-TEST_RANGE, TEST_RANGE);
    double x2 = random_ab(-TEST_RANGE, TEST_RANGE);
    while (!cmp_double(x1, x2)  || !cmp_double(x1 + x2, 0))
        x2 = random_ab(-TEST_RANGE, TEST_RANGE);
    if (x1 > x2)
        swap(&x1, &x2);

    double b = random_ab_nz(-TEST_RANGE, TEST_RANGE);
    double a = -b / (x1+x2);
    double c = -b * x1 / (x1+x2) * x2;
    // TODO - формула

    *params= (sParams){a, b, c};
    *solution = {2, x1, x2};
}

void gen_test_INFTY_roots(sParams* params, sSolution *solution)
{
    *params = {.0, .0, .0};
    *solution = {INFTY, .0, .0};
}

int run_test(const sParams* params, const sSolution *ref_solution)
{
    sSolution test_solution = {0, .0, .0};
    solve_general(params, &test_solution);

    if (cmp_sSolution(ref_solution, &test_solution))
    {
        fprintf(stderr,
                "TEST_FAILED:\n"
                "\tПараметры: %.9f\t %.9f\t %.9f\n"
                "\tДискриминант: %.9f\n"
                "\tОжидаемое решение: %d\t %.9f\t %.9f\n"
                "\tОтвет функции:     %d\t %.9f\t %.9f\n",
                params->a, params->b, params->c,
                params->b * params->b - 4 * params->a * params->c,
                ref_solution->rnum, ref_solution->x1, ref_solution->x2,
                test_solution.rnum, test_solution.x1, test_solution.x2
                );
        return 1;
    } else
        return 0;
}
