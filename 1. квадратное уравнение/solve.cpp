#include "solve.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"

void solve_general(const sParams* params, sSolution *solution)
{
    assert(params);
    assert(solution);

    if (!cmp_double(params->a, 0))
        solve_deg2(params, solution);
    else if (!cmp_double(params->b, 0))
        solve_deg1(params, solution);
    else
        solve_deg0(params, solution);
}

void solve_deg2(const sParams* params, sSolution *solution)
{
    assert(params);
    assert(solution);

    assert(!cmp_double(params->a, .0));

    double a = params->a;
    double b = params->b;
    double c = params->c;

    int bc = 2 * (!cmp_double(b, 0)) + !cmp_double(c, 0);

    switch(bc)
    {
    case 0b00:
        *solution = {1, .0, .0};
        return;

    case 0b01:
        if ((c < 0) == (a < 0))
        {
            *solution = {0, .0, .0};
            return;
        }
        else
        {
            double sqrt_ca = sqrt(-c / a);
            *solution = {2, -sqrt_ca, sqrt_ca};
        }
        return;

    case 0b10:
        *solution = {2, 0, -b / a};

        if ((b < 0) == (a < 0))
            my_swap(&solution->x1, &solution->x2);

        return;

    default:
        break;
    }

    double D = b * b - 4 * a * c;

    if (cmp_double(D, .0))
        *solution = {1, -b / (2 * a), .0};
    else if (D < 0)
        *solution = {0, .0, .0};
    else
    {
        double sqrt_D = sqrt(D);
        *solution = {2, (-b - sqrt_D) / (2 * a), (-b + sqrt_D) / (2 * a)};
        if (a < 0)
            my_swap(&solution->x1, &solution->x2);
    }
}

void solve_deg1(const sParams* params, sSolution *solution)
{
    assert(params);
    assert(solution);

    assert(cmp_double(params->a, .0));
    assert(!cmp_double(params->b, .0));

    double b = params->b;
    double c = params->c;
    *solution = {1, -c / b, .0};
}

void solve_deg0(const sParams* params, sSolution *solution)
{
    assert(params);
    assert(solution);

    assert(cmp_double(params->a, .0));
    assert(cmp_double(params->b, .0));

    *solution =  (!cmp_double(params->c, .0)) ? (sSolution){0, .0, .0} : (sSolution){INFTY, .0, .0};
}
