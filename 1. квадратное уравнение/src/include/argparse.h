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
enum solve_equation_state
{
    NO_SOLVE,       ///< Не решать уравнение
    INPUT_PARAMS,   ///< Нужно считать параметры уравнения из stdin
    CLI_PARAMS      ///< Параметры уже считаны из аргументов командной строки
};

/**
 * @brief структура, куда  argparse запишет считанные опции
 * @see argparse, solve_equation_state
 */
typedef struct
{
    int run_tests;                          ///< Запускать ли тесты. Если > 0, запустит столько тестов.
    int tests_tracking_freq;                ///< Как часто выводить прогресс по тестам. Если = 0, то прогресс не выводится.
    solve_equation_state solve_equation;    ///< Надо ли решать уравнение и/или считывать его параметры.
    sParams equation_params;                ///< Структура для записи параметров уравнения.
} sOptions;

/**
 * @brief парсит аргументы командной строки.
 *
 * @note об опциях см на главной.
 */
int argparse(int argc, char *argv[], sOptions *options);

/**
 * @brief парсит параметры опции -s, т.е параметры уравнения.
 */
int parse_params(const char * arg, sParams *params);

#endif //ARGPARSE_H
