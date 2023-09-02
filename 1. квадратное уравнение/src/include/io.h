/**
 * @file io.h
 * @brief Функци ввода-вывода.
 */

#ifndef IO_H
#define IO_H

#include "common.h"

/**
 * @brief Считывает параметры уравнения и флаги.
 * @note Выводит приглашение на ввод.
 *
 * Про флаги смотри parse_args.
 *
 * @param [in]  argc    Кол-во аргументов командной строки.
 * @param [in]  argv    Аргументы командной строки.
 * @param [out] params  указатель на структуру, в которую
 *                       нужно запсать считанные параметры
 * @return Код возврата.
 *
 * @see eErrors, process_flag
 */
eErrors input_params(int argc, const char * const argv[], sParams* params);

/**
 * @brief Поправляет -0.
 *
 * В некоторых случаях в ответ записывается
 * отрицательный ноль. Технически верно, но для
 * человека неприятно.
 *
 * @param [in, out] solution Структура с решением, где надо поправлять.
 */
void fix_zero(sSolution *solution);

/**
 * @brief Выводит решение.
 *
 * @note Меняет -0 на 0 в solution, вызывая fix_zero.
 *
 * Вывод должен быть красивым и удобным, что
 * субъективно. Поэтому я положился на интуицию.
 *
 * @param [in, out] solution Решение, которое надо вывести.
 *
 * @see fix_zero
 */
void output(sSolution *solution);


#endif //IO_H
