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

    fflush(stderr);
    printf("тестов провалено: %d / %d, доля ошибок: %f\n",
           tests_failed, TESTS_N, (double) tests_failed / TESTS_N
           );

    return tests_failed;
}

void gen_test(sParams* params, sSolution *solution)
{
    void (*test_cases[])(sParams *, sSolution *)= {
                        *gen_test_0_roots_deg0,
                        *gen_test_0_roots_deg2,
                        *gen_test_1_root_deg1,
                        *gen_test_1_root_deg2,
                        *gen_test_2_roots,
                        *gen_test_deg2_no_D,
                        *gen_test_INFTY_roots,
                        };

    int cases_n = sizeof test_cases / sizeof test_cases[0];
    (*test_cases[rand() % (cases_n)])(params, solution);
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
    int sign = (a < 0) ? -1 : 1; // восходящая или нисходящая парабола
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

    double c = -y + sign * random_ab_nz(0, TEST_RANGE);

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

void gen_test_2_roots(sParams* params, sSolution *solution)
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
    while (cmp_double(x1, x2)  || cmp_double((x1 + x2), 0)) //FIXME (#4#): без циклов
        x2 = random_ab(-TEST_RANGE, TEST_RANGE);
    if (x1 > x2)
        my_swap(&x1, &x2);
    double a = .0, b = .0, c = .0;
    do {
        b = random_ab_nz(-TEST_RANGE, TEST_RANGE);
        a = -b / (x1+x2);
        c = -b * x1 / (x1+x2) * x2;
    } while (cmp_double(b * b - 4 * a * c, 0));
    /*
     * 1.   x1 + x2 = -b / a         =>
     *      a = -b / (x1 + x2)
     *
     * 2.   x1 * x2 = c / a          =>
     *      c = x1 * x2  * a         =
     *      -b * x1 * x2 / (x1 + x2)
     *
     * Порядок дискриминанта - TETS_RANGE^2
     */

    *params= (sParams){a, b, c};
    *solution = {2, x1, x2};
}

void gen_test_deg2_no_D(sParams* params, sSolution *solution)
{
    switch (rand() % 3)
    {
    case 0b00: // b и с - 0, 0
        *params = {random_ab_nz(-TEST_RANGE, TEST_RANGE), .0, .0};
        *solution = {1, .0, .0};
        return;

    case 0b01: // b и с - 0, !0
        if (rand() % 2)
        {
            double x = random_ab_nz(0, TEST_RANGE);

            double a = 0, c = 0;
            do {                                            //FIXME (#4#): без циклов
                c = random_ab_nz(-TEST_RANGE, TEST_RANGE);
                a = -c / (x * x);
            } while (cmp_double(a, 0));

            *params = {a, .0, c};
            * solution = {2, -x, x};
        }
        else
        {
            double a = random_ab_nz(-TEST_RANGE, TEST_RANGE);
            int sign = (a < 0) ? -1 : 1;
            double c = sign * random_ab_nz(0, TEST_RANGE);

            *params = {a, .0, c};
            *solution = {0, .0, .0};
        }
        return;

    case 0b10: // b и с - !0, 0
    {
        double x2 = random_ab_nz(-TEST_RANGE, TEST_RANGE);

        double b = random_ab_nz(-TEST_RANGE, TEST_RANGE);
        double a = -b  / x2;

        *params = {a, b, .0};
        *solution = {2, .0, x2};

        if (x2 < 0)
            my_swap(&solution->x1, &solution->x2);

        return;
    }

    default:
        fprintf(stderr, "\nERROR(): gen_test_2_roots_no_D(): unknown case\n");
        return;
    }
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
        return 0;

    fprintf(stderr,
                "TEST_FAILED:\n"
                "\tПараметры: %.9f\t %.9f\t %.9f\n"
                "\tДискриминант: %g\n"
                "\tОжидаемое решение: %d\t %.9f\t %.9f\n"
                "\tОтвет функции:     %d\t %.9f\t %.9f\n",
                params->a, params->b, params->c,
                params->b * params->b - 4 * params->a * params->c,
                ref_solution->rnum, ref_solution->x1, ref_solution->x2,
                test_solution.rnum, test_solution.x1, test_solution.x2
                );
    return 1;
}
