/**
 * @file solve.h
 * @brief функци, решающие уравнения
 */

#ifndef SOLVE_H
#define SOLVE_H

#include  "common.h"

/**
 * @brief решает уравнение
 *
 * Внутри в зависимости от параметров вызывает solve_deg.
 *
 * @param [in]  params      параметры уравнения
 * @param [out] solution    указатель на структуру для записи решения
 * @return Ничего, так как я не придумал чего-либо осмысленного
 */
void solve_general(const sParams* params, sSolution *solution);

/**
 * @brief Решает уравнение ax^2 + bx + c = 0.
 *
 * @note Если params.a == 0, то падает на assert'е
 *
 * @param [in]  params      параметры уравнения
 * @param [out] solution    указатель на структуру для записи решения
 * @return Ничего, так как я не придумал чего-либо осмысленного
 */
void solve_deg2(const sParams* params, sSolution *solution);

/**
 * @brief Решает уравнение bx + c = 0.
 *
 * @note Если params.b == 0 или params.a != 0, то падает на assert'е
 *
 * @param [in]  params      параметры уравнения
 * @param [out] solution    указатель на структуру для записи решения
 * @return Ничего, так как я не придумал чего-либо осмысленного
 */
void solve_deg1(const sParams* params, sSolution *solution);

/**
 * @brief Решает уравнение c = 0.
 *
 * @note Если params.b != 0 или params.a != 0, то падает на assert'е
 *
 * Она состоит из одного тернарника, но для общности сделал так
 *
 * @param [in]  params      параметры уравнения
 * @param [out] solution    указатель на структуру для записи решения
 * @return Ничего, так как я не придумал чего-либо осмысленного
 */
void solve_deg0(const sParams* params, sSolution *solution);


#endif //SOLVE_H
