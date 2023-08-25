#ifndef TESTS_H
#define TESTS_H

#include  "common.h"

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
 * @brief генерирут тестовый случай
 *
 * выбирает один из вариантов
 *
 * @param [out] params указатель на структуру для записи параметров
 * @param [out] params указатель на структуру для записи ответов
 */
void gen_test(sParams* params, sSolution *solution);

/**
 * @brief проверяет правильность работы solve_general
 *
 * @param params       параметры тестового уравнения
 * @param ref_solution правильные ответы тестового уравнения
 * @return 0 в случае успеха, 1 в случае провала.
 */
int run_test(const sParams* params, const sSolution *ref_solution);

/**
 * @brief тест: случай с 0 корней и a = b = 0
 *
 * @param [out] params указатель на структуру для записи параметров
 * @param [out] params указатель на структуру для записи ответов
 */
void gen_test_0_roots_deg0(sParams* params, sSolution *solution);

/**
 * @brief тест: случай с 0 корней и a != 0
 *
 * @param [out] params указатель на структуру для записи параметров
 * @param [out] params указатель на структуру для записи ответов
 */
void gen_test_0_roots_deg2(sParams* params, sSolution *solution);

/**
 * @brief тест: случай с 1 корнем и a = 0, b != 0
 *
 * @param [out] params указатель на структуру для записи параметров
 * @param [out] params указатель на структуру для записи ответов
 */
void gen_test_1_root_deg1(sParams* params, sSolution *solution);

/**
 * @brief тест: случай с 1 корнем и a != 0
 *
 * @param [out] params указатель на структуру для записи параметров
 * @param [out] params указатель на структуру для записи ответов
 */
void gen_test_1_root_deg2(sParams* params, sSolution *solution);

/**
 * @brief тест: случай с 2 корнями и a != 0
 *
 * @note иногда генерит тесты с близкими корнями и
 * маленькими дискриминантами, и тест падет из-за точности
 *
 * @param [out] params указатель на структуру для записи параметров
 * @param [out] params указатель на структуру для записи ответов
 */
void gen_test_2_roots(sParams* params, sSolution *solution);

void gen_test_deg2_no_D(sParams* params, sSolution *solution);

/**
 * @brief тест: случай с бесконечностью корней
 *
 * @param [out] params указатель на структуру для записи параметров
 * @param [out] params указатель на структуру для записи ответов
 */
void gen_test_INFTY_roots(sParams* params, sSolution *solution);

#endif //TESTS_H
