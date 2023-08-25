/**
 * @file io.h
 * @brief функци ввода-вывода
 */

#ifndef IO_H
#define IO_H

#include "common.h"

/**
 * @brief обработчик флага
 *
 * @par Разрешенные флаги:
 *      @b -t[num] запускает num тестов. Если num отсутствует,
            или <= 0, запускается кол-во тестов
 *                 по умолчанию. Отключает решение уравнения. \n
 *      @b -s Включает решение уранения. Должен идти после отключения.
 *
 *
 * @param arg флаг для обработки
 * @return код возврата
 *
 * @see errors, sFlags
 */
int process_flag(const char * arg);

/**
 * @brief поиск флагов командной строки
 *
 * Вызывается в начале main
 *
 * @note Разрешенные флаги описаны в process_flag
 *
 * @return код возврата
 *
 * @see errors, sFlags, process_flag
 */
int find_flags(int argc, char *argv[]);

/**
 * @brief считывает аргументы командной строки
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

/**
 * @brief Считывает параметры уравнения и флаги
 * @note Выводит приглашение на ввод
 *
 * Про флаги смотри proccess_arg
 *
 * @param [in]  argc    кол-во аргументов командной строки
 * @param [in]  argv    аргументы командной строки
 * @param [out] params  указатель на структуру, в которую
 *                       нужно запсать считанные параметры
 * @return код возврата
 *
 * @see errors, process_flag
 */
int input(int argc, char *argv[], sParams* params);

/**
 * @brief поправляет -0
 *
 * В некоторых случаях в ответ записывается
 * отрицательный ноль. Технически верно, но для
 * человека неприятно.
 *
 * @param [in, out] solution структура с решением, где надо поправлять
 */
void fix_zero(sSolution *solution);

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


#endif //IO_H
