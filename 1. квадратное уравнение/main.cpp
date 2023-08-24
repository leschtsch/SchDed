/**
 * @mainpage Квадратка
 *
 * Первая задача с летней школы Деда.
 * Требуется написать программу, решающую квадратное уравнение,
 * А потом на нее вешается куча всего. O`_o
 *
 * @see solve_general, run_tests, main.cpp
 */

/**
 * @file main.cpp
 * @brief первый и единственный файл
 */

// TODO - флаг для тестов
// TODO - readme

//-----------------------------------------------------v-общее-v-------------------------------------------------------

#include "TXLib.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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
    ERR_BAD_INPUT,  ///< ошибка ввода, см полное описание
    ERR_BAD_CL,     ///< агрумент командной строки не число
    ERR_LACK_CL,    ///< мало аргументов командной строки
};

const int INFTY = -1;           ///< значение для бесконечности корней
const double EPS = 1e-6;        ///<  точность double и просто маленькое значение

const double TEST_RANGE = 1e3;  /**<
                                 * @brief некоторый разброс для теста
                                 *
                                 * чем больше это значение, тем больше
                                 * корни в тестах, но конкретных
                                 * ограничений нет. Расброс корней и
                                 * TEST_RANGE зависят линейно
                                 * @see gen_test и ее зависимые
                                 */

const double ROOTS_0_PROB = 1e-2;    /**<
                                 * @brief вероятность особог случая в тесте
                                 *
                                 * тесты распадаются на случаи,
                                 * когда корень (сумма корней) 0 и не 0. Это не
                                 * заслуживает разбиения на отдельные функции,
                                 * но заслуживает рассмотрения,
                                 * а вероятность 0 в рандоме КРАЙНЕ МАЛА!1!
                                 *
                                 * @see gen_test_0_roots_deg2, gen_test_1_root_deg2,
                                 * @see gen_test_1_root_deg1, gen_test_2_roots
                                 */

const int TESTS_N = (int) 2e7;  ///< кол-во тестов по умолчанию


/**
 * @brief сравнивает два double
 *
 * @param [in] a первое число
 * @param [in] b второе число
 * @return -1, 0, 1 если а <, ==, > b
 *
 * @see EPS
 */
int cmp_double(double a, double b);

/**
 * @brief сравнивает две структуры sSolution
 *
 * @param [in] a указатель на первую структуру
 * @param [in] b указатель на вторую структуру
 * @return 0, если структуры одинаковы,
 * -1 если первый различный элемент в них в первой
 * структуре меньше, 1 иначе.
 */
int cmp_sSolution(sSolution * a, sSolution * b);

/**
 * @brief случайное число от a до b
 *
 * a должо быть <= b, хотя формула и работает если b > a.
 *
 * @param [in] a нижняя граница
 * @param [in] b верхняя граница
 * @return случайное число от a до b
 */
double random_ab(double a, double b);

/**
 * @brief случайное число от a до b, кроме 0
 *
 * a должо быть <= b, хотя формула и работает если b > a.
 *
 * @param [in] a нижняя граница
 * @param [in] b верхняя граница
 * @return случайное число от a до b
 */
double random_ab_nz(double a, double b);

void swap (double * a, double * b); ///<swap, т. к. встроенный, поже,  в std::

//-----------------------------------------------------^-общее-^-------------------------------------------------------

//---------------------------------------------v-main и вызываемое ею-v------------------------------------------------

/**
 * @brief запускает случайные тесты
 *
 * @param [in] tests_n кол-во тестов
 * @return кол-во проваленных тестов
 *
 * @see TESTS_N
 */
int run_tests(int tests_n);

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
 *
 * @see errors
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
 */
void solve_general(sParams *params, sSolution* solution);

/**
 * @brief выводит решение
 *
 * @note меняет -0 на 0 в solution
 *
 * Вывод должен быть красивым и удобным, что
 * субъективно. Поэтому я положился на интуицию.
 *
 * @param [in, out] solution - решение, которое надо вывести
 */
void output(sSolution *solution);

/**
 * @brief обработка ошибок
 *
 * Ошибки пока только ошибки пользователя.
 * А обработка - только printf.
 *
 * @param [in] err_code код ошибки
 *
 * @see errors
 */
void process_error(int err_code);

/**
 * @see input, process_error, solve_general, output
 */
int main(int argc, char *argv[])
{
    // FIXME - это временно!!! :
    int tf = run_tests(TESTS_N);
    printf("тестов провалено: %d, доля ошибок: %f", tf, (double) tf / TESTS_N);
    return 0;


    sParams params = {.0, .0, .0};
    int input_res = input(argc, argv, &params);
    if (input_res)
    {
        process_error(input_res);
        return -1;
    }

    sSolution solution = {0, .0, .0};
    solve_general(&params, &solution);
    output(&solution);

    return 0;
}

//---------------------------------------------^-main и вызываемое ею-^------------------------------------------------

//-------------------------------------------------v-ввод и вывод-v----------------------------------------------------

/**
 * @brief считывает аргументы командной строки
 *
 * Разрешено вводить только три числа. Никаких флагов!
 *
 * @param [in]  argc    кол-во аргументов командной строки
 * @param [in]  argv    аргументы командной строки
 * @param [out] params  указатель на структуру, в которую
 *                       нужно запсать считанные параметры
 * @return код возврата
 *
 * @see errors
 */
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

/**
 * @brief поправляет -0
 *
 * В некоторых случаях в ответ записывается
 * отрицательный ноль. Технически верно, но для
 * человека неприятно.
 *
 * @param [in, out] solution структура с решением, где надо поправлять
 */
void fix_zero(sSolution* solution);

void output(sSolution* solution)
{
    fix_zero(solution);

    printf("У уравнения ");

    switch (solution->rnum)
    {
    case 0:
        printf("нет корней.\n");
        break;
    case 1:
        printf("1 корень: %f.\n", solution->x1);
        break;
    case 2:
        printf("2 корня: %f, %f.\n", solution->x1, solution->x2);
        break;
    case INFTY:
        printf("бесконечно много корней.\n");
        break;
    default:
        fprintf(stderr, "\nERROR: output(): solution.rnum == %d\n", solution->rnum);
        break;
    }
}

void fix_zero(sSolution* solution)
{
    assert(solution != NULL);

    if (!cmp_double(solution->x1, .0))
        solution->x1 = .0;
    if (!cmp_double(solution->x2, .0))
        solution->x2 = .0;
}

//-------------------------------------------------^-ввод и вывод-^----------------------------------------------------

//-----------------------------------------------v-решение уравнения-v-------------------------------------------------

/**
 * @brief Решает уравнение ax^2 + bx + c = 0.
 *
 * @note Если params.a == 0, то падает на assert'е
 *
 * @param [in]  params      параметры уравнения
 * @param [out] solution    указатель на структуру для записи решения
 * @return Ничего, так как я не придумал чего-либо осмысленного
 */
void solve_deg2(sParams *params, sSolution* solution);

/**
 * @brief Решает уравнение bx + c = 0.
 *
 * @note Если params.b == 0 или params.a != 0, то падает на assert'е
 *
 * @param [in]  params      параметры уравнения
 * @param [out] solution    указатель на структуру для записи решения
 * @return Ничего, так как я не придумал чего-либо осмысленного
 */
void solve_deg1(sParams *params, sSolution* solution);

/**
 * @brief Решает уравнение c = 0.
 *
 * @note Если params.b != 0 или params.a != 0, то падает на assert'е
 *
 * Она состоит из одного тернарника, но для общности сделал так
 *
 * @param [in]  params      параметры уравнения
 * @param [out] solution    указатель на структуру для записи решения
 * @return Ничего, так как я не придумал чего-либо осмысленного
 */
void solve_deg0(sParams *params, sSolution* solution);
//TODO - структуру по ссылке

void solve_general(sParams *params, sSolution* solution)
{
    if (cmp_double(params->a, 0))
        solve_deg2(params, solution);
    else if (cmp_double(params->b, 0))
        solve_deg1(params, solution);
    else
        solve_deg0(params, solution);
}

void solve_deg2(sParams *params, sSolution* solution)
{
    assert(cmp_double(params->a, .0));

    double a = params->a;
    double b = params->b;
    double c = params->c;
    double D = b * b - 4 * a * c;

    if (!cmp_double(D, .0))
        *solution = {1, -b / (2 * a), .0};
    else if (D < 0)
        *solution = {0, .0, .0};
    else if (a>0)
        *solution = {2, (-b - sqrt(D)) / (2 * a), (-b + sqrt(D)) / (2 * a)};
    else
        *solution = {2, (-b + sqrt(D)) / (2 * a), (-b - sqrt(D)) / (2 * a)};


}

void solve_deg1(sParams *params, sSolution* solution)
{

    assert(!cmp_double(params->a, .0));
    assert(cmp_double(params->b, .0));

    double b = params->b;
    double c = params->c;
    *solution = {1, -c / b, .0};
}

void solve_deg0(sParams *params, sSolution* solution)
{
    assert(!cmp_double(params->a, .0));
    assert(!cmp_double(params->b, .0));

    *solution =  (cmp_double(params->c, .0)) ? (sSolution){0, .0, .0} : (sSolution){INFTY, .0, .0};
}

//-----------------------------------------------^-решение уравнения-^-------------------------------------------------

//-----------------------------------------------------v-тесты-v-------------------------------------------------------

/**
 * @brief генерирут тестовый случай
 *
 * выбирает один из вариантов
 *
 * @param [out] params указатель на структуру для записи параметров
 * @param [out] params указатель на структуру для записи ответов
 */
void gen_test(sParams * params, sSolution * solution);

/**
 * @brief проверяет правильность работы solve_general
 *
 * @param params       параметры тестового уравнения
 * @param ref_solution правильные ответы тестового уравнения
 * @return 0 в случае успеха, 1 в случае провала.
 */
int run_test(sParams * params, sSolution * ref_solution);

int run_tests(int tests_n)
{
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

/**
 * @brief тест: случай с 0 корней и a = b = 0
 *
 * @param [out] params указатель на структуру для записи параметров
 * @param [out] params указатель на структуру для записи ответов
 */
void gen_test_0_roots_deg0(sParams * params, sSolution * solution);

/**
 * @brief тест: случай с 0 корней и a != 0
 *
 * @param [out] params указатель на структуру для записи параметров
 * @param [out] params указатель на структуру для записи ответов
 */
void gen_test_0_roots_deg2(sParams * params, sSolution * solution);

/**
 * @brief тест: случай с 1 корнем и a = 0, b != 0
 *
 * @param [out] params указатель на структуру для записи параметров
 * @param [out] params указатель на структуру для записи ответов
 */
void gen_test_1_root_deg1(sParams * params, sSolution * solution);

/**
 * @brief тест: случай с 1 корнем и a != 0
 *
 * @param [out] params указатель на структуру для записи параметров
 * @param [out] params указатель на структуру для записи ответов
 */
void gen_test_1_root_deg2(sParams * params, sSolution * solution);

/**
 * @brief тест: случай с 2 корнями и a != 0
 *
 * @note иногда генерит тесты с близкими корнями и
 * маленькими дискриминантами, и тест падет из-за точности
 *
 * @param [out] params указатель на структуру для записи параметров
 * @param [out] params указатель на структуру для записи ответов
 */
void gen_test_2_roots(sParams * params, sSolution * solution);

/**
 * @brief тест: случай с бесконечностью корней
 *
 * @param [out] params указатель на структуру для записи параметров
 * @param [out] params указатель на структуру для записи ответов
 */
void gen_test_INFTY_roots(sParams * params, sSolution * solution);

void gen_test(sParams * params, sSolution * solution)
{
    switch (rand() % 6) // не лучший способ, но простой
    {
    case 0:
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

void gen_test_0_roots_deg0(sParams * params, sSolution * solution)
{
    double c = random_ab_nz(-TEST_RANGE, TEST_RANGE);
    *params = {.0, .0, c};
    *solution = {0, .0, .0};
}

void gen_test_0_roots_deg2(sParams * params, sSolution * solution)
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

void gen_test_1_root_deg1(sParams * params, sSolution * solution)
{
    if (random_ab(0,1)<ROOTS_0_PROB)
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

void gen_test_1_root_deg2(sParams * params, sSolution * solution)
{
    if (random_ab(0,1)<ROOTS_0_PROB)
    {
        *params  = {random_ab_nz(-TEST_RANGE, TEST_RANGE), 0, .0};
        *solution = {1, .0, .0};
        return;
    }

    double x = random_ab_nz(-TEST_RANGE, TEST_RANGE);
    double b = random_ab(-TEST_RANGE, TEST_RANGE);

    *params= (sParams){-b / (2*x), b, -(b * x)/2};
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

void gen_test_2_roots(sParams * params, sSolution * solution) //FIXME - лол крч в при оч мелких дискриминантах падает
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

    *params= (sParams){a, b, c};
    *solution = {2, x1, x2};
}

void gen_test_INFTY_roots(sParams * params, sSolution * solution)
{
    *params = {.0, .0, .0};
    *solution = {INFTY, .0, .0};
}

int run_test(sParams* params, sSolution* ref_solution)
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

//-----------------------------------------------------^-тесты-^-------------------------------------------------------

//-----------------------------------------------v-общее (реализации)-v------------------------------------------------

int cmp_double(double a, double b)
{
    if (fabs(a - b) < EPS)
        return 0;
    return (a < b) ? -1 : 1;
}

int cmp_sSolution(sSolution* a, sSolution* b)
{
    if (a->rnum != b->rnum)
        return (a->rnum < b->rnum) ? -1 : 1;
    int cmp_res = cmp_double(a->x1, b->x1);
    return (cmp_res) ? cmp_res:cmp_double(a->x2, b->x2);
} //TODO - ассерты правильности структур в этой функции и после всяких return'ов

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

double random_ab(double a, double b)
{
    assert(cmp_double(a, b) < 0);
    if (!cmp_double(a, b))
        return a;
    return (double) rand() / RAND_MAX * (b - a) + a;
}

double random_ab_nz(double a, double b)
{
    double res = random_ab(a, b);
    while (!cmp_double(res, .0))// вероятность этого крайне мала 1!!1!1
        res = random_ab(a, b);
    return res;
};

void swap (double * a, double * b)
{
    double tmp = *a;
    *a = *b;
    *b = tmp;
}
//-----------------------------------------------^-общее (реализации)-^------------------------------------------------
