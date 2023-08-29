/**
 * @file common.h
 * @brief общие функции и прочее
 */

#ifndef COMMON_H
#define COMMON_H

#include <math.h>

#define EPS 1e-6  ///<  точность double и просто маленькое значение
#define is_zero(a) (fabs((a)) < EPS) ///< @brief частный и частый случай is_zero(a);
                                     ///< @see cmp_double

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
 */
enum errors
{
    OK,                 ///< Ошибки нет
    ERR_BAD_INPUT,      ///< Ошибка ввода
    ERR_CLI_BAD_ARG,    ///< Неизвестный агрумент командной строки.
    HELP_ASKED          ///< Пользователь запросил помощь. Не ошибка, но делать больше ничего не надо.
};

const int INFTY = -1;           ///< значение для бесконечности корней

/**
 * @brief сравнивает два double
 *
 * @param [in] a первое число
 * @param [in] b второе число
 * @return 1, если a = b, иначе 0
 *
 * @see EPS
 */
int cmp_double(double a, double b);

/**
 * @brief сравнивает две структуры sSolution
 *
 * @param [in] a указатель на первую структуру
 * @param [in] b указатель на вторую структуру
 * @return 1, если a = b, иначе 0
 */
int cmp_sSolution(const sSolution *a, const sSolution *b);

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

void my_swap (double * a, double * b); ///<swap, т. к. встроенный, поже,  в std::

/**
 * @brief проверяет, является ли строка числом
 * @param s - строка
 * @return 1 если строка - число, 0 иначе
 */
int is_number(char * s);

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

#endif /*COMMON_H*/
