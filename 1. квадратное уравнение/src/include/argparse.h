/**
 * @file argparse.h
 * @brief разбор аргументов командной строки
 */

#ifndef ARGPARSE_H
#define ARGPARSE_H

#include "common.h"

/**
 * @brief enum того, надо ли решать уравнение и/или считывать его параметры.
 * @see sOptions
 */
typedef enum //TODO: rename eSfsdfds
{
    DONT_SOLVE,       ///< Не решать уравнение
    INPUT_PARAMS,   ///< Нужно считать параметры уравнения из stdin
    CLI_PARAMS      ///< Параметры уже считаны из аргументов командной строки
} solve_equation_state;

/**
 * @brief структура, куда  parse_args запишет считанные опции
 * @see parse_args, solve_equation_state
 */
typedef struct
{
    int run_tests;  //TODO: n_tests/.../...                        ///< Запускать ли тесты. Если > 0, запустит столько тестов.
    int tests_tracking_freq;                ///< Как часто выводить прогресс по тестам. Если = 0, то прогресс не выводится.
    solve_equation_state solve_equation;    ///< Надо ли решать уравнение и/или считывать его параметры.
    sParams equation_params;                ///< Структура для записи параметров уравнения.
} sOptions;

//TODO: точки и заглавные
/**
 * @brief парсит аргументы командной строки.
 *
 * @note об опциях см на главной.
 */
int parse_args(int argc, char *argv[], sOptions *options);

/**
 * @brief парсит параметры опции -s, т.е параметры уравнения.
 */
int parse_params(const char * arg, sParams *params);

#endif //ARGPARSE_H
