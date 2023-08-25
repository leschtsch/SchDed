#ifndef COMMON_H
#define COMMON_H

/**
 * @brief структура для записи решения
 *
 * Если корня два, в x1 меньший,
 * если крень один, он в x1,
 * если корней нет или их бесконечность,
 * ожидается, что x1 и x2 - нули.
 */
typedef struct
{
    int rnum;  ///< количество корней
    double x1; ///< первый корень
    double x2; ///< второй корень
} sSolution;

/**
 * @brief структура для записи параметров уравнения
 */
typedef struct
{
    double a; ///< параметр при x^2
    double b; ///< параметр при x
    double c; ///< свободный член
} sParams;

/**
 * @brief enum возможных внутренних кодов возврата
 *
 * Я также хотел различать ошибки ввода, но
 * это слишком сложно чрез один лишь scanf.
 * Не захотел ради этого усложнять код.
 */
enum errors// TODO (#2#): расшифровать CLI, TO_FEW
{
    OK,                 ///< ошибки нет
    ERR_BAD_INPUT,      ///< ошибка ввода, см полное описание
    ERR_CLI_BAD_ARG,     ///< неизвестный агрумент командной строки
    ERR_CLI_TOO_FEW_NUM,    ///< мало чисел в командной строке
    ERR_CLI_TOO_MANY_NUM,    ///< слишком много в командной строке
};

/**
 * @brief структура для глобальных флагов
 */
typedef struct
{
    unsigned char RUN_TESTS: 1;      ///< Запускать ли тесты
    unsigned char SOLVE_EQUATION: 1; ///< решать ли уравнение
} sFlags;

const int INFTY = -1;           ///< значение для бесконечности корней
const double EPS = 1e-6;        ///<  точность double и просто маленькое значение

const double TEST_RANGE = 1e3;  /**<
                                 * @brief некоторый разброс для теста
                                 *
                                 * чем больше это значение, тем больше
                                 * корни в тестах, но конкретных
                                 * ограничений нет. Расброс корней и
                                 * TEST_RANGE зависят линейно
                                 * @see gen_test и ее зависимые
                                 */

const double ROOTS_0_PROB = 1e-2;    /**<
                                 * @brief вероятность особог случая в тесте
                                 *
                                 * тесты распадаются на случаи,
                                 * когда корень (сумма корней) 0 и не 0. Это не
                                 * заслуживает разбиения на отдельные функции,
                                 * но заслуживает рассмотрения,
                                 * а вероятность 0 в рандоме КРАЙНЕ МАЛА!1!
                                 *
                                 * @see gen_test_0_roots_deg2, gen_test_1_root_deg2,
                                 * @see gen_test_1_root_deg1, gen_test_2_roots
                                 */

extern int TESTS_N; ///< кол-во тестов по умолчанию
extern sFlags FLAGS; ///< глобальные флаги

/**
 * @brief сравнивает два double
 *
 * @param [in] a первое число
 * @param [in] b второе число
 * @return -1, 0, 1 если а <, ==, > b
 *
 * @see EPS
 */
int cmp_double(double a, double b);

/**
 * @brief сравнивает две структуры sSolution
 *
 * @param [in] a указатель на первую структуру
 * @param [in] b указатель на вторую структуру
 * @return 0, если структуры одинаковы,
 * -1 если первый различный элемент в них в первой
 * структуре меньше, 1 иначе.
 */
int cmp_sSolution(const sSolution *a, const sSolution *b);

/**
 * @brief случайное число от a до b
 *
 * a должо быть <= b, хотя формула и работает если b > a.
 *
 * @param [in] a нижняя граница
 * @param [in] b верхняя граница
 * @return случайное число от a до b
 */
double random_ab(double a, double b);

/**
 * @brief случайное число от a до b, кроме 0
 *
 * a должо быть <= b, хотя формула и работает если b > a.
 *
 * @param [in] a нижняя граница
 * @param [in] b верхняя граница
 * @return случайное число от a до b
 */
double random_ab_nz(double a, double b);

void my_swap (double * a, double * b); ///<swap, т. к. встроенный, поже,  в std::

/**
 * @brief обработка ошибок
 *
 * Ошибки пока только ошибки пользователя.
 * А обработка - только printf.
 *
 * @param [in] err_code код ошибки
 *
 * @see errors
 */
void process_error(int err_code);

#endif /*COMMON_H*/
