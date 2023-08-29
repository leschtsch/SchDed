/**
 * @file config.h
 *
 * @brief файл с настройками
 */
#ifndef CONFIG_H
#define CONFIG_H

const int TESTS_N = (int) 2e7;      ///< кол-во тестов по умолчанию
const int PRINT_TESTS_REM_FREQ = 1000000; ///< как часто выводить кол-во оставшихся тестов

const double TEST_RANGE = 1e3;  /**<
                                 * @brief Yекоторый разброс для теста
                                 *
                                 * @note Рекомендуется значение в EPS^(-2)
                                 *
                                 * Чем больше это значение, тем больше
                                 * корни в тестах, но конкретных
                                 * ограничений нет. Расброс корней зависит
                                 * линейно от TEST_RANGE.
                                 *
                                 * @see gen_test и ее зависимые
                                 */

const double ROOTS_0_PROB = 1e-2;    /**<
                                 * @brief Вероятность особого случая в тесте
                                 *
                                 * Тесты распадаются на случаи,
                                 * когда корень  0 и не 0. Это не
                                 * заслуживает разбиения на отдельные функции,
                                 * но заслуживает рассмотрения,
                                 * а вероятность 0 в рандоме КРАЙНЕ МАЛА!1!
                                 *
                                 * @see gen_test_0_roots_deg2, gen_test_1_root_deg2,
                                 * @see gen_test_1_root_deg1, gen_test_2_roots
                                 */


#endif //CONFIG_H
