/**
 * @mainpage Квадратка
 *
 * Первая задача с летней школы Деда.
 * Требуется написать программу, решающую квадратное уравнение,
 * А потом на нее вешается куча всего. O`_o
 *
 * @see solve_general, main.cpp
 */

/**
 * @file main.cpp
 * @brief первый и единственный файл
 */

//TODO - тесты

//-------------------------------------------v-общее-v---------------------------------------------

#include "TXLib.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

const int INFTY = -1; ///< значение для бесконечности корней
const double EPS = 1e-6; ///<  точность для сравненияф double

/**
 * @brief сравнивает два double
 *
 * @param [in] a первое число
 * @param [in] b второе число
 * @return -1, 0, 1 если а <, ==, > b
 * @see EPS
 */
int cmp_double(double a, double b);

/**
 * @brief структура для записи решения
 *
 * Если корня два, в x1 меньший,
 * если крень один, он в x1,
 * если корней нет или их бесконечность,
 * ожидается, что x1 и x2 - нули.
 */
typedef struct
{
    int rnum;  ///< количество корней
    double x1; ///< первый корень
    double x2; ///< второй корень
} sSolution;

/**
 * @brief структура для записи параметров уравнения
 */
typedef struct
{
    double a; ///< параметр при x^2
    double b; ///< параметр при x
    double c; ///< свободный член
} sParams;

/**
 * @brief enum возможных внутренних кодов возврата
 *
 * Я также хотел различать ошибки ввода, но
 * это слишком сложно чрез один лишь scanf.
 * Не захотел ради этого усложнять код.
 */
enum errors
{
    OK,             ///< ошибки нет
    ERR_BAD_INPUT,  ///< ошибка ввода, см ниже
    ERR_BAD_CL,     ///< агрумент командной строки не число
    ERR_LACK_CL,    ///< мало аргументов командной строки
};

//-------------------------------------------^-общее-^---------------------------------------------

//-----------------------------------v-main и вызываемое ею-v--------------------------------------

/**
 * @brief Считывает параметры уравнения
 * @note Выводит приглашение на ввод
 *
 * Разрешено вводить три числа либо из консоли,
 * либо в аргументах командной строки.
 * Никаких флагов, фишек и сложных форматов
 * нет - не захотел усложнять.
 *
 * @param [in]  argc    кол-во аргументов командной строки
 * @param [in]  argv    аргументы командной строки
 * @param [out] params  указатель на структуру, в которую
 *                       нужно запсать считанные параметры
 * @return код возврата
 * @see sParams, errors
 */
int input(int argc, char *argv[], sParams* params);

/**
 * @brief решает уравнение
 *
 * Внутри в зависимости от параметров вызывает solve_deg.
 *
 * @param [in]  params      параметры уравнения
 * @param [out] solution    указатель на структуру для записи решения
 * @return Ничего, так как я не придумал чего-либо осмысленного
 * @see sParams, sSolution, solve_deg2, solve_deg1, solve_deg0
*/
void solve_general(sParams params, sSolution* solution);


void fix_zero(sSolution *solution);   // Поправляет -0
void output(sSolution solution);       // Выводит решение
void process_error(int err_code);
int main(int argc, char *argv[])
{
    sParams params = {.0, .0, .0};
    int input_res = input(argc, argv, &params);
    if (input_res)
    {
        process_error(input_res);
        return -1;
    }

    sSolution solution = {0, .0, .0};
    solve_general(params, &solution);
    fix_zero(&solution);
    output(solution);

    return 0;
}
//-----------------------------------^-main и вызываемое ею-^--------------------------------------

//---------------------------------------v-ввод и вывод-v------------------------------------------
int input_cl(int argc, char *argv[], sParams* params);
int input(int argc, char *argv[], sParams* params)
{
    assert(params!=NULL);

    if (argc > 1)
        return input_cl(argc, argv, params);

    printf("Введите коэффициэнты - три числа:\n");

    if (scanf("%lf %lf %lf", &params->a, &params->b, &params->c) < 3)
        return ERR_BAD_INPUT;

    return OK;
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
        return ERR_LACK_CL;

    char * p = NULL;

    params->a = strtod(argv[1],&p);
    if (*p != '\0' || p==argv[1])
        return ERR_BAD_CL;
    params->b = strtod(argv[2],&p);
    if (*p != '\0' || p==argv[2])
        return ERR_BAD_CL;
    params->c = strtod(argv[3],&p);
    if (*p != '\0' || p==argv[3])
        return ERR_BAD_CL;

    return OK;
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
    assert(solution != NULL);

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
        fprintf(stderr, "\nERROR: main(): solution.rnum == %d\n", solution.rnum);
        break;
    }
}
//---------------------------------------^-ввод и вывод-^------------------------------------------

//-------------------------------------v-решение уравнения-v---------------------------------------
void solve_deg2(sParams params, sSolution* solution); // Решает уравнение ax^2 + bx +c = 0
void solve_deg1(sParams params, sSolution* solution); // Решает уравнение ax + b = 0
void solve_deg0(sParams params, sSolution* solution); // Решает уравнение c = 0

void solve_general(sParams params, sSolution* solution)
{
    if (cmp_double(params.a, 0))
    {
        solve_deg2(params, solution);
        return;
    }
    if (cmp_double(params.b, 0))
    {
        solve_deg1(params, solution);
        return;
    }
    solve_deg0(params, solution);
}

void solve_deg2(sParams params, sSolution* solution)
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

}

void solve_deg1(sParams params, sSolution* solution)
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
}

void solve_deg0(sParams params, sSolution* solution)
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
}
//-------------------------------------^-решение уравнения-^---------------------------------------

//-------------------------------------v-общее (реализации)-v--------------------------------------
int cmp_double(double a, double b)
{
    if (fabs(a-b) < EPS)
        return 0;
    return a<b?-1:1;
}

void process_error(int err_code)
{
    switch (err_code)
    {
    case OK:
        printf("process_error(OK): OK.\n");
        break;
    case ERR_BAD_INPUT:
        printf("Аргументы введены неверно / ошибка ввода.\n");
        break;
    case ERR_BAD_CL:
        printf("Аргументы командной строки введены неверно.\n");
        break;
    case ERR_LACK_CL:
        printf("Недостаточно аргументов командной строки.\n");
        break;
    default:
        fprintf(stderr, "\nERROR: process_error(%d): unknown error %d.\n", err_code, err_code);
        break;
    }
}
//-------------------------------------^-общее (реализации)-^--------------------------------------

