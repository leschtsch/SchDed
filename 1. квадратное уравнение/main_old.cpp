/*
 * Программа, решающая уравнение ax^2 + bx + c = 0.
 * любые из трех параметров могут быть равны нулю,
 * поскольку я не знаю, что программисты называют
 * КВАДРАТНЫМ уравнением. Да и че бы и нет.
 */

/* QUESTION - не слишком ли много комментариев?
И как их писать правильно вообще? */

#include <stdio.h>
#include <math.h>

enum root_number
{
    ZERO,
    ONE,
    TWO,
    INFTY,
}; // enum количества найденных корней

// QUESTION - как лучше назвать структуры?
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

int main(int argc, char *argv[])
{
    sParams get_params(int argc, char *argv[]); // Считывает параметры уравнения
    void fix_zero(sSolution * solution);        // поправляет -0
    sSolution deg2(sParams params);             // Решает уравнение ax^2 + bx +c = 0

    // QUESTION - мб передавать структуры по ссылке?
    sParams params = get_params(argc, argv);
    sSolution solution = deg2(params);
    fix_zero(&solution);

    // FIXME - русские буквы

    printf("equation has "); // TODO - функция для вывода.
    switch (solution.rnum)
    {
    case ZERO:
        printf("no roots \n");
        break;
    case ONE:
        printf("1 root: %f\n", solution.x1);
        break;
    case TWO:
        printf("2 roots: %f, %f\n", solution.x1, solution.x2);
        break;
    case INFTY:
        printf("infinitely many roots");
        break;
    default:
        printf("\n programmer's fault");
        break;
    }
    return 0;
}

sParams get_params(int argc, char *argv[])
/*
 * Считывает параметры уравнения.
 *
 * Пока что здесь банальный scanf, но планируется сделать парсинг
 * срок с иксами и степенями (каким образом, чтобы удобно?),
 * а так же ввод аргументов командной строки.
 *
 * Принимает argc и argv, возвращает параметры в
 * виде sParams.
 */
{
    sParams params = {.0, .0, .0};
    scanf("%lf %lf %lf", &params.a, &params.b, &params.c); // TODO - иксы, аргументы командной строки.
    return params;
}

void fix_zero(sSolution *solution) // FIXME - мб можно добиться этого проще?
/*
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
    sSolution deg1(sParams params); // Решает уравнение ax + b = 0

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
    sSolution deg0(sParams params);

    if (eq(params.b, .0))
        return deg0(params);

    double b = params.b;
    double c = params.c;
    return (sSolution){ONE, -c / b, .0};
}

sSolution deg0(sParams params)
/*
 * Решает уравнение bx + c = 0.
 *
 * Причем возможно b = 0.
 *
 * Принимает параметры в виде sParams, возвращает
 * решение в виде sSolution.
 */
{
    return (eq(params.c, .0)) ? (sSolution){INFTY, .0, .0} : (sSolution){ZERO, .0, .0};
    // QUESTION - нафига приведение типа?
}
