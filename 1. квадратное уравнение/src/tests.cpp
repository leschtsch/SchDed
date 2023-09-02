/**
 * @file tests.cpp
 * @brief Функци генерации и запуска тестов.
 */


#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "include/tests.h"
#include "include/solve.h"
#include "include/common.h"
#include "include/config.h"

double comp_time_rem(int tests_completed, int tests_n, clock_t time_running)
{
    if (!tests_completed)
        return -1;

    double time_rem = time_running;
    time_rem /= CLOCKS_PER_SEC;
    time_rem *= (double) (tests_n - tests_completed) / tests_completed;

    return time_rem;
}

int run_tests(int tests_n, int tracking_freq)
{
    assert(tests_n > 0);

    int tests_failed = 0;
    clock_t start = clock();

    for (int i = 0; i < tests_n; i++)
    {
        if (tracking_freq && !(i % tracking_freq))
        {
            printf(
                "Осталось  %9d тест(а, ов).\tЭто ~ %-7.3f секунд\n",
                tests_n - i,
                comp_time_rem(i, tests_n, clock() - start)
            );
            fflush(stdout);
        }

        sParams params = {.0, .0, .0};
        sSolution ref_solution = {.0, .0, ZERO_ROOTS};
        gen_test(&params, &ref_solution);

        if (run_test(&params, &ref_solution))
            tests_failed++;
    }

    if (tracking_freq)
        printf("Осталось 0 тестов.\n");

    fflush(stderr);

    printf(
        "Тестов провалено: %d / %d, доля ошибок: %f.\n"
        "Время выполнения: %f.\n",
        tests_failed, tests_n, (double) tests_failed / tests_n,
        (double) (clock() - start) / CLOCKS_PER_SEC
    );

    return tests_failed;
}

void gen_test(sParams* params, sSolution *ref_solution)
{
    assert(params);
    assert(ref_solution);

    void (*test_cases[])(sParams *, sSolution *) = {
                        *gen_test_0_roots_deg0,
                        *gen_test_0_roots_deg2,
                        *gen_test_1_root_deg1,
                        *gen_test_1_root_deg2,
                        *gen_test_2_roots,
                        *gen_test_deg2_no_D,
                        *gen_test_infity_roots,
                        };

    int cases_n = sizeof test_cases / sizeof test_cases[0];

    (*test_cases[rand() % (cases_n)])(params, ref_solution);
}

void gen_test_0_roots_deg0(sParams* params, sSolution *ref_solution)
{
    assert(params);
    assert(ref_solution);

    double c = random_ab_nz(-TEST_RANGE, TEST_RANGE);
    *params = {.0, .0, c};
    *ref_solution = {.0, .0, ZERO_ROOTS};
}

void gen_test_0_roots_deg2(sParams* params, sSolution *ref_solution)
{
    assert(params);
    assert(ref_solution);

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
    *ref_solution = {.0, .0, ZERO_ROOTS};

}

void gen_test_1_root_deg1(sParams* params, sSolution *ref_solution)
{
    assert(params);
    assert(ref_solution);

    if (random_ab(0,1) < ROOTS_0_PROB)
    {
        *params = {
            .0,
            random_ab_nz(-TEST_RANGE, TEST_RANGE),
            .0
        };
        *ref_solution = {.0, .0, ONE_ROOT};
        return;
    }

    double x = random_ab_nz(-TEST_RANGE, TEST_RANGE);

    double c = random_ab_nz(-TEST_RANGE, TEST_RANGE);

    *params = {
        .0,
        - c / x,
        c
    };
    *ref_solution = {x, .0, ONE_ROOT};
}

void gen_test_1_root_deg2(sParams* params, sSolution *ref_solution)
{
    assert(params);
    assert(ref_solution);

    double x = random_ab_nz(-TEST_RANGE, TEST_RANGE);

    double b = random_ab(-TEST_RANGE, TEST_RANGE);
    double a = -b / (2 * x);
    double c = -(b * x)/2;
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

    *params= (sParams){a, b, c};
    *ref_solution = {x, .0, ONE_ROOT};
}

void gen_test_2_roots(sParams* params, sSolution *ref_solution)
{
    assert(params);
    assert(ref_solution);

    double x1 = random_ab(-TEST_RANGE, TEST_RANGE);
    double x2 = random_ab(-TEST_RANGE, TEST_RANGE);
    if (is_equal_double(x1, x2)  || is_equal_double((x1 + x2), 0)) // какая-то тонкая настройка, не трогать
    {
        *params = {.0, .0, .0};
        *ref_solution = {.0, 0, INFINITY_ROOTS};
        return;
    }
    if (x1 > x2)
        my_swap(&x1, &x2);

    double b = random_ab_nz(-TEST_RANGE, TEST_RANGE);
    double a = -b / (x1+x2);
    double c = -b * x1 / (x1+x2) * x2;
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

    if (is_zero(b * b - 4 * a * c))
    {
        *params = {.0, .0, .0};
        *ref_solution = {.0, 0, INFINITY_ROOTS};
        return;
    }

    *params= (sParams){a, b, c};
    *ref_solution = {x1, x2, TWO_ROOTS};
}

void gen_test_deg2_no_D(sParams* params, sSolution *ref_solution)
{
    assert(params);
    assert(ref_solution);

    switch (rand() % 3)
    {
        case 0b00: // b и с - 0, 0
        {
            *params = {
                random_ab_nz(-TEST_RANGE, TEST_RANGE),
                .0,
                .0
            };
            *ref_solution = {.0, .0, ONE_ROOT};
            return;
        }

        case 0b01: // b и с - 0, !0
        {
            if (rand() % 2)
            {
                double x = random_ab_nz(0, TEST_RANGE);

                double a = 0, c = 0, cx = 0;

                cx = random_ab_nz(-TEST_RANGE, TEST_RANGE);
                c = cx * x;
                a = -cx / x;

                *params = {a, .0, c};
                *ref_solution = {-x, x, TWO_ROOTS};
            }
            else
            {
                double a = random_ab_nz(-TEST_RANGE, TEST_RANGE);
                int sign = (a < 0) ? -1 : 1;
                double c = sign * random_ab_nz(0, TEST_RANGE);

                *params = {a, .0, c};
                *ref_solution = {.0, .0, ZERO_ROOTS};
            }
            return;
        }

        case 0b10: // b и с - !0, 0
        {
            double x2 = random_ab_nz(-TEST_RANGE, TEST_RANGE);

            double b = random_ab_nz(-TEST_RANGE, TEST_RANGE);
            double a = -b  / x2;

            *params = {a, b, .0};
            *ref_solution = {.0, x2, TWO_ROOTS};

            if (x2 < 0)
                my_swap(&ref_solution->x1, &ref_solution->x2);

            return;
        }

        default:
        {
            fprintf(stderr, "\nERROR(): gen_test_2_roots_no_D(): unknown case\n");
            return;
        }
    }
}

void gen_test_infity_roots(sParams* params, sSolution *ref_solution)
{
    assert(params);
    assert(ref_solution);

    *params = {.0, .0, .0};
    *ref_solution = {.0, .0, INFINITY_ROOTS};
}

bool run_test(const sParams* params, const sSolution *ref_solution)
{
    assert(params);
    assert(ref_solution);

    sSolution test_solution = {.0, .0, ZERO_ROOTS};
    solve_general(params, &test_solution);

    if (is_equal_sSolution(ref_solution, &test_solution))
        return 0;

    double D = params->b * params->b - 4 * params->a * params->c;
    fprintf(
        stderr,
        "ТЕСТ ПРОВАЛЕН:\n"
        "\tПараметры: %.9f\t %.9f\t %.9f\n"
        "\tДискриминант: %g\n"
        "\tОжидаемое решение: %d\t %.9f\t %.9f\n"
        "\tОтвет функции:     %d\t %.9f\t %.9f\n",
        params->a, params->b, params->c,
        D,
        ref_solution->rnum, ref_solution->x1, ref_solution->x2,
        test_solution.rnum, test_solution.x1, test_solution.x2
    );
    return 1;
}
