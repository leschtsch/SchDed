/**
 * @mainpage Квадратка
 *
 * Первая задача с летней школы Деда.
 *
 * @par О задаче:
 *      Задача формулируется так:\n
 * <pre>    <em>Написать программу, решающую квадратное уравнение.</em></pre>
 *      Звучит просто, но очень размыто. После того, как студент пытается
 *      сдать очередной вариант программы, ему сразу предъявляют
 *      дополнительные требования по функционалу, архитектуре и кодстайлу.
 *      В итоге на простую задачу уходит очень много времени.
 *
 * @par Результат:
 *      Программа была успешно написана. Она поддержвает передачу
 *      параметов уравнения во ввод и через опцию командной строки.
 *      Также имеется возможность запускать автоматически
 *      генерируемые тесты покрывающие всевозможные сучаи, при этом
 *      можно отслеживать, сколько на эти тесты уходит времени.
 *
 * @par Установка:
 *      1. Скачать папку `1. квадратное уравнение`.
 *      2. Возможно, потребуется перевети кодировку в cp1251,
 *              иначе в выводе и в документации будут кракозябры.
 *      3. Скачать `TXLib`: [header](http://storage.ded32.net.ru/Lib/TX/TXUpdate/TXLib.h)
 *              или [установщик](https://sourceforge.net/projects/txlib/).
 *      4. Запустить в этой папке `make` или `g++ ./src/*.cpp -o main.exe`.
 *      5. Запустить `doxygen`, если  нужна подробная документация.\n\n
 *      *TXLib - это учебная графическая библиотека.
 *      У меня из всех ее возможностей используется только
 *      русский в консоли, поскольку тратить время на
 *      английский для первого раза не хотелось.*
 *
 * @par Использование:
 *      **Простой способ** - запустить  каким-либо образом `main.exe`.
 *      Программа сама запросит три действительных числа через пробелы.
 *       Строго говоря, можно использовать любые символы разделители.\n\n
 *      **Способ сложнее** - запускать из консоли с аргументами.
 *      Некоторые аргументы отключают другие.
 *      В силу всупает последний. Доступные аргументы:\n
 *      **-t**[num] **--run-tests**[=num] запускает num тестов.
 *      Если num отсутствует, или <= 0, запускается кол-во
 *      тестов по умолчанию. Отключает решение уравнения.\n
 *      **-p**[num] --track_progress[=num] Если производятся тесты,
 *      каждые num тестов будет выводится, сколько тестов осталось.
 *      Если num отсутствует или <= 0, выводистя каждый тест.\n
 *      **-s**[a,b,c] **--solve-equation**[=a,b,c]
 *      Решает уравнение ax^2 + bx + c = 0.
 *      Если параметры не указаны, они читаются из stdin.\n
 *      **-h** **--help** Выводит помощь. Завершает программу.
 *
 * @par Примеры использования:
 *      @code
 *      $ ./main.exe
 *
 *      Введите коэффициэнты - три числа через пробелы:
 *      1 -3 2
 *      У уравнения 2 корня: 1.000000, 2.000000.
 *      @endcode
 *      @code
 *      $ ./main.exe -s1,-3,2
 *
 *      У уравнения 2 корня: 1.000000, 2.000000..
 *      @endcode
 *      @code
 *      $ ./main.exe -t -p5000000
 *
 *      Осталось   20000000 тест(а, ов).        Это ~ -1.000  секунд
 *      Осталось   15000000 тест(а, ов).        Это ~ 3.150   секунд
 *      Осталось   10000000 тест(а, ов).        Это ~ 2.069   секунд
 *      Осталось    5000000 тест(а, ов).        Это ~ 1.031   секунд
 *      Осталось 0 тестов.
 *      Тестов провалено: 0 / 20000000, доля ошибок: 0.000000.
 *      Время выполнения: 4.116000.
 *      @endcode
 *
 * @see solve_general, run_tests, main.cpp
 */

/**
 * @file main.cpp
 */

// ридми - что это, как установить, как использовать, фичи, всякие лицензии и хонорабле ментион
// примеров многовато

//  что это, как собрать, как юзать

#include "TXLib.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/argparse.h"
#include "include/io.h"
#include "include/tests.h"
#include "include/solve.h"
#include "include/common.h"
#include "include/config.h"

/**
 * @see input_params, process_error, solve_general, output
 */
int main(int argc, char * const argv[])
{
    sOptions options = {
        .tests_n = 0,
        .tests_tracking_freq = 0,
        .solve_equation = INPUT_PARAMS,
        .equation_params = {0, 0, 0},
    };

    int parsing_res = parse_args(argc, argv, &options);

    if (parsing_res)
    {
        process_error(parsing_res);
        return parsing_res;
    }

    if (options.tests_n > 0)
        run_tests(options.tests_n, options.tests_tracking_freq);

    if (options.solve_equation != DONT_SOLVE)
    {
        int input_res = 0;

        if (options.solve_equation == INPUT_PARAMS)
            input_res = input_params(argc, argv, &options.equation_params);

        if (input_res)
        {
            process_error(input_res);
            return input_res;
        }

        sSolution solution = {.0, .0, ZERO_ROOTS};
        solve_general(&options.equation_params, &solution);

        assert(solution.x1 < solution.x2 || solution.rnum < 2);

        output(&solution);
    }

    return 0;
}
