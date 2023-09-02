/**
 * @file tests.h
 * @brief Функци генерации и запуска тестов.
 */

#ifndef TESTS_H
#define TESTS_H

#include <stdbool.h>
#include <time.h>

#include  "common.h"

/**
 * @brief Сколько времени осталось на оставшиеся тесты.
 *
 * Время расчитывается из пропорции
 * (тестов_завершено / тестов_осталось)             ~
 * (времени_прошло / времени_осталось)              =>
 * (tests_completed / (tests_n - tests_completed))  ~
 * (time_running / res)                             =>
 * res ~ time_running / tests_completed * (tests_n - tests_completed)
 *
 * @param [in] tests_completed  Сколько завершено тестов.
 * @param [in] tests_n          Сколько всего тестов.
 * @param [in] time_running     Сколько времени прошло.
 *
 * @return Оставшееся время в секундах.
 */
double comp_time_rem(int tests_completed, int tests_n, clock_t time_running);

/**
 * @brief Запускает случайные тесты.
 *
 * @param [in] tests_n          Кол-во тестов.
 * @param [in] tracking_freq    Как часто выводить прогресс по тестам.
 *                              если 0 - никогда.
 *
 * @return Кол-во проваленных тестов.
 *
 * @see TESTS_N_DEFAULT, TESTS_TRACKING_FREQ_DEFAULT
 */
int run_tests(int tests_n, int tracking_freq);

/**
 * @brief Генерирут тестовый случай.
 *
 * выбирает один из вариантов
 *
 * @param [out] params      Указатель на структуру для записи параметров.
 * @param [out] solution    Указатель на структуру для записи ответов.
 */
void gen_test(sParams* params, sSolution *solution);

/**
 * @brief Проверяет правильность работы solve_general.
 *
 * @param params       Параметры тестового уравнения.
 * @param ref_solution Правильные ответы тестового уравнения.
 * @return false в случае успеха, true в случае провала.
 */
bool run_test(const sParams* params, const sSolution *ref_solution);

/**
 * @brief Тест: случай с 0 корней и a = b = 0.
 *
 * @param [out] params Указатель на структуру для записи параметров.
 * @param [out] solution Указатель на структуру для записи ответов.
 */
void gen_test_0_roots_deg0(sParams* params, sSolution *solution);

/**
 * @brief Тест: случай с 0 корней и a != 0.
 *
 * @param [out] params      Указатель на структуру для записи параметров.
 * @param [out] solution    Указатель на структуру для записи ответов.
 */
void gen_test_0_roots_deg2(sParams* params, sSolution *solution);

/**
 * @brief Тест: случай с 1 корнем и a = 0, b != 0.
 *
 * @param [out] params      Указатель на структуру для записи параметров.
 * @param [out] solution    Указатель на структуру для записи ответов.
 */
void gen_test_1_root_deg1(sParams* params, sSolution *solution);

/**
 * @brief Тест: случай с 1 корнем и a != 0.
 *
 * @param [out] params      Указатель на структуру для записи параметров.
 * @param [out] solution    Указатель на структуру для записи ответов.
 */
void gen_test_1_root_deg2(sParams* params, sSolution *solution);

/**
 * @brief Тест: случай с 2 корнями и a != 0, для которого нужен дискриминант.
 *
 * @note иногда генерит значения на грани точности.
 * В таких случаях я использую заглушку,
 * т. к. ничего лучше не придумал. Но таких случаев
 * крайне мало.
 *
 * @param [out] params      Указатель на структуру для записи параметров.
 * @param [out] solution    Указатель на структуру для записи ответов.
 */
void gen_test_2_roots(sParams* params, sSolution *solution);

/**
 * @brief Тест: случаи с 2 корнями и a != 0, которые решается без дискриминанта.
 *
 * @param [out] params      Указатель на структуру для записи параметров.
 * @param [out] solution    Указатель на структуру для записи ответов.
 */
void gen_test_deg2_no_D(sParams* params, sSolution *solution);

/**
 * @brief Тест: Случай с бесконечностью корней.
 *
 * @param [out] params      Указатель на структуру для записи параметров.
 * @param [out] solution    Указатель на структуру для записи ответов.
 */
void gen_test_infity_roots(sParams* params, sSolution *solution);

#endif //TESTS_H
