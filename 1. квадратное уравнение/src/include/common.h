/**
 * @file common.h
 * @brief Общие функции и прочее.
 */

#ifndef COMMON_H
#define COMMON_H

#include <math.h>
#include <stdbool.h>

#define EPS 1e-6                     ///<  точность double и просто маленькое значение.
#define is_zero(a) (fabs((a)) < EPS) ///< @brief Частный и частый случай is_equal_double(a, .0).
                                     ///< @see is_equal_double

/**
 * @brief Enum возможных внутренних кодов возврата.
 */
typedef enum
{
    OK,                 ///< Ошибки нет
    ERR_BAD_INPUT,      ///< Ошибка ввода
    ERR_CLI_BAD_ARG,    ///< Неизвестный агрумент командной строки.
    HELP_ASKED          ///< Пользователь запросил помощь. Не ошибка, но делать больше ничего не надо.
} eErrors;

/**
 * @brief Enum кол-ва корней.
 */
typedef enum
{   ZERO_ROOTS,
    ONE_ROOT,
    TWO_ROOTS,
    INFINITY_ROOTS = -1           ///< Значение для бесконечности корней.
} eRnum;

/**
 * @brief Cтруктура для записи решения.
 *
 * Если корня два, в x1 меньший,
 * если крень один, он в x1,
 * если корней нет или их бесконечность,
 * ожидается, что x1 и x2 - нули.
 */
typedef struct
{
    double x1; ///< Первый корень.
    double x2; ///< Второй корень.
    eRnum rnum;  ///< Количество корней.
} sSolution;

/**
 * @brief Структура для записи параметров уравнения.
 */
typedef struct
{
    double a; ///< параметр при x^2
    double b; ///< параметр при x
    double c; ///< свободный член
} sParams;

/**
 * @brief Сравнивает два double.
 *
 * @param [in] a Первое число.
 * @param [in] b Второе число.
 * @return true, если a = b, иначе false.
 *
 * @see EPS
 */
bool is_equal_double(double a, double b);

/**
 * @brief Сравнивает две структуры sSolution.
 *
 * @param [in] a указатель на первую структуру.
 * @param [in] b указатель на вторую структуру.
 * @return true, если a = b, иначе false.
 */
bool is_equal_sSolution(const sSolution *a, const sSolution *b);

/**
 * @brief Случайное число от a до b.
 *
 * a должо быть <= b, хотя формула и работает если b > a.
 *
 * @param [in] a Нижняя граница.
 * @param [in] b Верхняя граница.
 * @return Случайное число от a до b.
 */
double random_ab(double a, double b);

/**
 * @brief Случайное число от a до b, кроме 0.
 *
 * a должо быть <= b, хотя формула и работает если b > a.
 *
 * @param [in] a Нижняя граница.
 * @param [in] b Верхняя граница.
 * @return Случайное число от a до b, кроме 0.
 */
double random_ab_nz(double a, double b);

void my_swap (double * a, double * b); ///<swap, т. к. встроенный, поже,  в std::

/**
 * @brief Обработка ошибок.
 *
 * Ошибки пока только ошибки пользователя.
 * А обработка - только printf.
 *
 * @param [in] err_code Код ошибки.
 *
 * @see eErrors
 */
void process_error(int err_code);

#endif /*COMMON_H*/
