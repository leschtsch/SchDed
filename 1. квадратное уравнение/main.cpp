/*
 * Программа, решающая уравнение ax^2 + bx + c = 0.
 * любые из трех параметров могут быть равны нулю,
 * поскольку я не знаю, что программисты называют
 * КВАДРАТНЫМ уравнением. Да и че бы и нет.
 */
// QUESTION - МБ можно документровть и не функции?
//-------------------------------------------v-общее-v---------------------------------------------
#include "TXLib.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

const int INFTY = -1; // значение для бесконечности корней
const double EPS = 1e-6; //  точность

int cmp_double(double a, double b); // равны ли два числа

typedef struct
{
    int rnum;
    double x1; // x1 и x2 - корни. Два корня - x1 < x2.
    double x2; //Один корень - он в x1.
} sSolution; // в такую структуру запишется решение

typedef struct
{
    double a;
    double b;
    double c;
} sParams; // в такую структуру запишутся параметры уравнения

//-------------------------------------------^-общее-^---------------------------------------------

//-----------------------------------v-main и вызываемое ею-v--------------------------------------
int input(int argc, char *argv[], sParams* params); // Считывает параметры уравнения

// TODO - ЗДЕСЬ ДОКИ
int solve_general(sParams params, sSolution* solution);
void fix_zero(sSolution *solution);   // Поправляет -0

void output(sSolution solution);       // Выводит решение

int main(int argc, char *argv[])
{
    sParams params = {.0, .0, .0};
    if (!input(argc, argv, &params))
        return -1;

    sSolution solution = {0, .0, .0};
    solve_general(params, &solution);
    fix_zero(&solution);
    output(solution);

    return 0;
}
//-----------------------------------^-main и вызываемое ею-^--------------------------------------

//---------------------------------------v-ввод и вывод-v------------------------------------------
int input_cl(int argc, char *argv[], sParams* params); // Считывает аргументы командной строки.
int input(int argc, char *argv[], sParams* params)
/*
 * Считывает параметры уравнения.
 *
 * Разрешено вводить три числа либо из консоли,
 * либо в аргументах командной строки.
 * Никаких флагов, фишек и сложных форматов
 * нет - не захотел усложнять.
 *
 * Принимает argc, argv и структуру для записи параметров.
 * возвращает1 в случае успеха, иначе 0.
 */
{
    assert(params!=NULL);

    if (argc > 1)
        return input_cl(argc, argv, params);
    printf("Введите коэффициэнты - три числа:\n");
    if (scanf("%lf %lf %lf", &params->a, &params->b, &params->c) < 3)
    {
        printf("Аргументы введены неверно");
        return 0;
    }
    return 1; //TODO - константы ошибок, 0 - это ок
}

int input_cl(int argc, char *argv[], sParams* params)
/*
 * Считывает аргументы командной строки.
 *
 * Разрешено вводить только три числа. Никаких флагов!
 *
 * Принимает argc, argv и структуру для записи параметров.
 * возвращает1 в случае успеха, иначе 0.
 */
{
    assert(params!=NULL);

    if (argc < 4)
    {
        printf("Недостаточно аргументов командной строки");
        return 1;
    }

    char * p = NULL;

    params->a = strtod(argv[1],&p);
    if (*p != '\0' || p==argv[1])
        goto NaN_error;
    params->b = strtod(argv[2],&p);
    if (*p != '\0' || p==argv[2])
        goto NaN_error;
    params->c = strtod(argv[3],&p);
    if (*p != '\0' || p==argv[3])
        goto NaN_error;

    return 1;

    NaN_error:
        printf("Аргументы командной строки введены неверно");
        return 0;
}

void fix_zero(sSolution *solution)
/*sParams* params
 * Поправляет -0.
 *
 * В некоторых случаях в ответ записывается
 * отрицательный ноль. Технически верно, но для
 * человека неприятно.
 *
 * Принимает указатель на структуру с ответом и
 * заменяет -0.0 на 0.0 .
 */
{
    if (!cmp_double(solution->x1, .0))
        solution->x1 = .0;
    if (!cmp_double(solution->x2, .0))
        solution->x2 = .0;
}

void output(sSolution solution)
/*
 * Выводит решение.
 *
 * Вывод должен быть красивым и удобным, что
 * субъективно. Поэтому я положился на интуицию.
 *
 * Принимает решение в виде sSolution,
 * ничего не возвращает.
 */
{
    printf("У уравнения ");

    switch (solution.rnum)
    {
    case 0:
        printf("нет корней.\n");
        break;
    case 1:
        printf("1 корень: %f.\n", solution.x1);
        break;
    case 2:
        printf("2 корня: %f, %f.\n", solution.x1, solution.x2);
        break;
    case INFTY:
        printf("бесконечно много корней.\n");
        break;
    default:
        fprintf(stderr,"\nERROR: main(): solution.rnum == %d\n", solution.rnum);
        break;
    }
}
//---------------------------------------^-ввод и вывод-^------------------------------------------

//-------------------------------------v-решение уравнения-v---------------------------------------
int solve_deg2(sParams params, sSolution* solution); // Решает уравнение ax^2 + bx +c = 0
int solve_deg1(sParams params, sSolution* solution); // Решает уравнение ax + b = 0
int solve_deg0(sParams params, sSolution* solution); // Решает уравнение c = 0

int solve_general(sParams params, sSolution* solution)
{
    if (cmp_double(params.a, 0))
        return solve_deg2(params, solution);
    if (cmp_double(params.b, 0))
        return solve_deg1(params, solution);
    return solve_deg0(params, solution);
}

int solve_deg2(sParams params, sSolution* solution)
/*
 * Решает уравнение ax^2 + bx + c = 0.
 *
 * Если a = 0, то падает на assert'е
 *
 * Принимает параметры в виде sParams и указатель
 * для записи решения, возвращает 0.
 */
{
    assert(cmp_double(params.a, .0));

    double a = params.a;
    double b = params.b;
    double c = params.c;
    double D = b * b - 4 * a * c;

    if (!cmp_double(D, .0))
        *solution = {1, -b / (2 * a), .0};
    else if (D < 0)
        *solution = {0, .0, .0};
    else
        *solution = {2, (-b - sqrt(D)) / (2 * a), (-b + sqrt(D)) / (2 * a)};

    return 0;
}

int solve_deg1(sParams params, sSolution* solution)
/*
 * Решает уравнение bx + c = 0.
 *
 * Если b = 0, то падает на assert'е
 *
 * Принимает параметры в виде sParams и указатель
 * для записи решения, возвращает 0.
 */
{

    assert(!cmp_double(params.a, .0));
    assert(cmp_double(params.b, .0));

    double b = params.b;
    double c = params.c;
    *solution = {1, -c / b, .0};
    return 0;
}

int solve_deg0(sParams params, sSolution* solution)
/*
 * Решает уравнение c = 0.
 *
 * Причем c  может быть любым.
 *
 * Принимает параметры в виде sParams и указатель
 * для записи решения, возвращает 0.
 */
{
    assert(!cmp_double(params.a, .0));
    assert(!cmp_double(params.b, .0));

    *solution =  (cmp_double(params.c, .0)) ? (sSolution){0, .0, .0} : (sSolution){INFTY, .0, .0};
    // QUESTION - поч не работает без приведения?
    return 0;
}
//-------------------------------------^-решение уравнения-^---------------------------------------

//-------------------------------------v-общее (реализации)-v--------------------------------------
int cmp_double(double a, double b)
{
    if (fabs(a-b) < EPS)
        return 0;
    return a<b?-1:1;
}
//-------------------------------------^-общее (реализации)-^--------------------------------------

