#include "solve.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"

void solve_general(const sParams* params, sSolution *solution)
{
    if (cmp_double(params->a, 0)) // TODO - поведение cmp неинтуитивно
        solve_deg2(params, solution);
    else if (cmp_double(params->b, 0))
        solve_deg1(params, solution);
    else
        solve_deg0(params, solution);
}

void solve_deg2(const sParams* params, sSolution *solution)
{
    assert(cmp_double(params->a, .0));

    double a = params->a;
    double b = params->b;
    double c = params->c;
    double D = b * b - 4 * a * c;
    //TODO - sqrt_D

    if (!cmp_double(D, .0))
        *solution = {1, -b / (2 * a), .0};
    else if (D < 0)
        *solution = {0, .0, .0};
    else if (a>0)
        *solution = {2, (-b - sqrt(D)) / (2 * a), (-b + sqrt(D)) / (2 * a)}; //TODO - случаи без дисккримминанта
    else
        *solution = {2, (-b + sqrt(D)) / (2 * a), (-b - sqrt(D)) / (2 * a)};


}

void solve_deg1(const sParams* params, sSolution *solution)
{

    assert(!cmp_double(params->a, .0));
    assert(cmp_double(params->b, .0));

    double b = params->b;
    double c = params->c;
    *solution = {1, -c / b, .0};
}

void solve_deg0(const sParams* params, sSolution *solution)
{
    assert(!cmp_double(params->a, .0));
    assert(!cmp_double(params->b, .0));

    *solution =  (cmp_double(params->c, .0)) ? (sSolution){0, .0, .0} : (sSolution){INFTY, .0, .0};
}
