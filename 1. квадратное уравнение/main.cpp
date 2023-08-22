/*
 * Программа, решающая уравнение ax^2 + bx + c = 0.
 * любые из трех параметров могут быть равны нулю,
 * поскольку я не знаю, что программисты называют
 * КВАДРАТНЫМ уравнением. Да и че бы и нет.
 */

/* QUESTION - не слишком ли много комментариев?
И как их писать правильно вообще? */

//-----------------------------------v-includ'ы и объявления-v-------------------------------------
#include "TXLib.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum root_number
{
    ZERO,
    ONE,
    TWO,
    INFTY,
}; // enum количества найденных корней

typedef struct
{
    enum root_number rnum;
    double x1;
    double x2;
    /* x1 и x2 - корни. столько достаточно, так корней либо
    бесконечность либо <= 2. Предполагается, что
    если корень один, то он хранится в x1, если корней два,
    то в x1 меньший. */
} sSolution; // в такую структуру запишется решение
typedef struct
{
    double a;
    double b;
    double c;
} sParams; // в такую структуру запишутся параметры уравнения

#define EPS 1e-6
#define eq(a, b) (fabs((a) - (b)) < EPS)
//-----------------------------------^-includ'ы и объявления-^-------------------------------------

int input(int argc, char *argv[], sParams* params); // Считывает параметры уравнения
sSolution deg2(sParams params);        // Решает уравнение ax^2 + bx +c = 0
void fix_zero(sSolution *solution);   // Поправляет -0
void output(sSolution solution);       // Выводит решение

int main(int argc, char *argv[])
{

    sParams params = {.0, .0, .0};
    if (!input(argc, argv, &params))
        return -1;
    sSolution solution = deg2(params);
    fix_zero(&solution);
    output(solution);

    return 0;
}

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
        printf("Аргументы консоли введены неверно");
        return 0;
    }
    return 1;
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
        return 0;
    }

    char * p = NULL;

    params->a = strtod(argv[1],&p);
    if (*p != '\0')
        goto NaN_error;
    params->b = strtod(argv[2],&p);
    if (*p != '\0')
        goto NaN_error;
    params->c = strtod(argv[3],&p);
    if (*p != '\0')
        goto NaN_error;

    return 1;

    NaN_error:
        printf("Аргументы командной строки введены неверно");
        return 0;
}

void fix_zero(sSolution *solution) // FIXME - мб можно добиться этого проще?
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
    if (eq(solution->x1, .0))
        solution->x1 = .0;
    if (eq(solution->x2, .0))
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
    case ZERO:
        printf("нет корней.\n");
        break;
    case ONE:
        printf("1 корень: %f.\n", solution.x1);
        break;
    case TWO:
        printf("2 корня: %f, %f.\n", solution.x1, solution.x2);
        break;
    case INFTY:
        printf("бесконечно много корней.");
        break;
    default:
        printf("\n погромист где-то ошибся.");
        break;
    }
}
//---------------------------------------^-ввод и вывод-^------------------------------------------

//-------------------------------------v-решение уравнения-v---------------------------------------
sSolution deg1(sParams params); // Решает уравнение ax + b = 0

sSolution deg2(sParams params)
/*
 * Решает уравнение ax^2 + bx + c = 0.
 *
 * Причем уравнение не обязательно квадратное,
 * т. е. возможно a = 0.
 *
 * Принимает параметры в виде sParams, возвращает
 * решение в виде sSolution.
 */
{
    if (eq(params.a, .0))
        return deg1(params);

    double a = params.a;
    double b = params.b;
    double c = params.c;
    double D = b * b - 4 * a * c;

    if (eq(D, .0))
        return (sSolution){ONE, -b / (2 * a), .0};
    if (D < 0)
        return (sSolution){ZERO, .0, .0};
    return (sSolution){TWO, (-b - sqrt(D)) / (2 * a), (-b + sqrt(D)) / (2 * a)};
}

sSolution deg0(sParams params);  // Решает уравнение c = 0

sSolution deg1(sParams params)
/*
 * Решает уравнение bx + c = 0.
 *
 * Причем уравнение не обязательно линейное,
 * т. е. возможно b = 0.
 *
 * Принимает параметры в виде sParams, возвращает
 * решение в виде sSolution.
 */
{

    if (eq(params.b, .0))
        return deg0(params);

    double b = params.b;
    double c = params.c;
    return (sSolution){ONE, -c / b, .0};
}

sSolution deg0(sParams params)
/*
 * Решает уравнение c = 0.
 *
 * Причем c  может быть любым.
 *
 * Принимает параметры в виде sParams, возвращает
 * решение в виде sSolution.
 */
{
    return (eq(params.c, .0)) ? (sSolution){INFTY, .0, .0} : (sSolution){ZERO, .0, .0};
    // QUESTION - нафига приведение типа?
}
//-------------------------------------^-решение уравнения-^---------------------------------------

