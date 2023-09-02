/**
 * @file solve.cpp
 * @brief Функци, решающие уравнения.
 */

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/solve.h"
#include "include/common.h"

void solve_general(const sParams* params, sSolution *solution)
{
    assert(params);
    assert(solution);

    if (!is_zero(params->a))
        solve_deg2(params, solution);
    else if (!is_zero(params->b))
        solve_deg1(params, solution);
    else
        solve_deg0(params, solution);
}

void solve_deg2(const sParams* params, sSolution *solution)
{
    assert(params);
    assert(solution);

    assert(!is_zero(params->a));

    double a = params->a;
    double b = params->b;
    double c = params->c;

    int bc = ((!is_zero(b)) << 1) + !is_zero(c);

    switch(bc)
    {
        case 0b00:
        {
            *solution = {.0, .0, ONE_ROOT};
            return;
        }

        case 0b01:
        {
            if ((c < 0) == (a < 0))
            {
                *solution = {.0, .0, ZERO_ROOTS};
                return;
            }

            double sqrt_ca = sqrt(-c / a);
            *solution = {
                -sqrt_ca,
                sqrt_ca,
                TWO_ROOTS
            };

            return;
        }

        case 0b10:
        {
            *solution = {
                .0,
                -b / a,
                TWO_ROOTS
            };

            if ((b < 0) == (a < 0))
                my_swap(&solution->x1, &solution->x2);

            return;
        }

        default:
        {
            break;
        }
    }

    double D = b * b - 4 * a * c;

    if (is_zero(D))
        *solution = {-b / (2 * a), .0, ONE_ROOT};
    else if (D < 0)
        *solution = {.0, .0, ZERO_ROOTS};
    else
    {
        double sqrt_D = sqrt(D);

        *solution = {
            (-b - sqrt_D) / (2 * a),
            (-b + sqrt_D) / (2 * a),
            TWO_ROOTS
        };
        if (a < 0)
            my_swap(&solution->x1, &solution->x2);
    }
}

void solve_deg1(const sParams* params, sSolution *solution)
{
    assert(params);
    assert(solution);

    assert(is_zero(params->a));
    assert(!is_zero(params->b));

    double b = params->b;
    double c = params->c;
    *solution = {
        -c / b,
        .0,
        ONE_ROOT
    };
}

void solve_deg0(const sParams* params, sSolution *solution)
{
    assert(params);
    assert(solution);

    assert(is_zero(params->a));
    assert(is_zero(params->b));

    *solution =  (!is_zero(params->c)) ?
        (sSolution){.0, .0, ZERO_ROOTS} :
        (sSolution){.0, .0, INFINITY_ROOTS};
}
