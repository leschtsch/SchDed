/**
 * @file argparse.h
 * @brief Разбор аргументов командной строки.
 */

#ifndef ARGPARSE_H
#define ARGPARSE_H

#include "common.h"

const char OPT_TESTS_SHORT =    't'; ///< Короткая опция запуска тестов.
const char OPT_PROGRESS_SHORT = 'p'; ///< Короткая опция отслеживания прогресса.
const char OPT_SOLVE_SHORT =    's'; ///< Короткая опция решения уравнения.
const char OPT_HELP_SHORT =     'h'; ///< Короткая опция помощи.

/**
 * @brief enum того, надо ли решать уравнение и/или считывать его параметры.
 * @see sOptions
 */
typedef enum
{
    DONT_SOLVE,     ///< Не решать уравнение.
    INPUT_PARAMS,   ///< Нужно считать параметры уравнения из stdin.
    CLI_PARAMS      ///< Параметры уже считаны из аргументов командной строки.
} eSolveEquationState;

/**
 * @brief структура, куда  parse_args запишет считанные опции
 * @see parse_args, eSolveEquationState
 */
typedef struct
{
    int tests_n;                            ///< Запускать ли тесты. Если > 0, запустит столько тестов.
    int tests_tracking_freq;                ///< Как часто выводить прогресс по тестам. Если = 0, то прогресс не выводится.
    eSolveEquationState solve_equation;    ///< Надо ли решать уравнение и/или считывать его параметры.
    sParams equation_params;                ///< Структура для записи параметров уравнения.
} sOptions;

/**
 * @brief Выводит сообщение о помощи.
 *
 * Форматирует HELP_MSG с помощью OPT_<...>_SHORT/LONG
 */
void print_help(void);

/**
 * @brief Парсит аргументы командной строки.
 *
 * @note Об опциях см на главной.
 *
 * @param [in] argc Кол-во аргументов командной строки.
 * @param [in] argv Аргументы командной строки.
 * @param [out] options Структура для записи опций.
 * @return Код возврата.
 */
eErrors parse_args(int argc, char * const argv[], sOptions *options);

/**
 * @brief парсит параметры опции -s, т.е параметры уравнения.
 *
 * @param [in]  arg     Аргумент опции -s. Ожидается 3 числа через запятую.
 * @param [out] params  Структура для записи параметров
 *
 * @return Код возврата.
 */
eErrors parse_params(const char * arg, sParams *params);

#endif //ARGPARSE_H
