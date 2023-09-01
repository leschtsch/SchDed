/**
 * @file io.h
 * @brief функци ввода-вывода
 */

#ifndef IO_H
#define IO_H

#include "common.h"

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
int input_params(int argc, char *argv[], sParams* params);

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
 * @note меняет -0 на 0 в solution, вызывая fix_zero
 *
 * Вывод должен быть красивым и удобным, что
 * субъективно. Поэтому я положился на интуицию.
 *
 * @param [in, out] solution - решение, которое надо вывести
 *
 * @see fix_zero
 */
void output(sSolution *solution);


#endif //IO_H
