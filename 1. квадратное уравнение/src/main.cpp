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
 *      $ ./main.exe
 *
 *      Введите коэффициэнты - три числа через пробелы:
 *      -.5 1.5 -1.
 *      У уравнения 2 корня: 1.000000, 2.000000.
 *      @endcode
 *      @code
 *      $ ./main.exe -s1,-3,2
 *
 *      У уравнения 2 корня: 1.000000, 2.000000..
 *      @endcode
 *      @code
 *      $ ./main.exe -s-.5,1.5,-1.
 *
 *      У уравнения 2 корня: 1.000000, 2.000000.
 *      @endcode
 *      @code
 *      $ ./main.exe -t
 *
 *      Тестов провалено: 0 / 20000000, доля ошибок: 0.000000.
 *      Время выполнения: 4.661000.
 *      @endcode
 *      @code
 *      $ ./main.exe -t10 -p3
 *
 *      Осталось         10 тест(а, ов).        Это ~ -1.000  секунд
 *      Осталось          7 тест(а, ов).        Это ~ 0.000   секунд
 *      Осталось          4 тест(а, ов).        Это ~ 0.000   секунд
 *      Осталось          1 тест(а, ов).        Это ~ 0.000   секунд
 *      Осталось 0 тестов.
 *      Тестов провалено: 0 / 10, доля ошибок: 0.000000.
 *      Время выполнения: 0.000000.
 *      @endcode
 *      @code
 *      $ ./main.exe --run-tests=100 --track-progress=25 --solve-equation=1,-2,1
 *
 *      Осталось        100 тест(а, ов).        Это ~ -1.000  секунд
 *      Осталось         75 тест(а, ов).        Это ~ 0.000   секунд
 *      Осталось         50 тест(а, ов).        Это ~ 0.000   секунд
 *      Осталось         25 тест(а, ов).        Это ~ 0.000   секунд
 *      Осталось 0 тестов.
 *      Тестов провалено: 0 / 100, доля ошибок: 0.000000.
 *      Время выполнения: 0.000000.
 *      У уравнения 1 корень: 1.000000.
 *      @endcode
 *
 * @see solve_general, run_tests, main.cpp
 */

/**
 * @file main.cpp
 */

//TODO: норм ридми + англ(необ)?
//TODO: описание флагов
// например до -s числа это ошибка   getopt??
// какой-то гайд?

//  что это, как собрать, как юзать

#include "TXLib.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "include/io.h"
#include "include/argparse.h"
#include "include/tests.h"
#include "include/solve.h"
#include "include/common.h"
#include "include/config.h"

/**
 * @see input, process_error, solve_general, output
 */
int main(int argc, char *argv[])
{
    sOptions options = {
                        .run_tests = 0,
                        .tests_tracking_freq = 0,
                        .solve_equation = INPUT_PARAMS,
                        .equation_params = {0, 0, 0},
                     };

    int parsing_res = argparse(argc, argv, &options);

    if (parsing_res)
    {
        process_error(parsing_res);
        return parsing_res;
    }

    if (options.run_tests)
        run_tests(options.run_tests, options.tests_tracking_freq);

    if (options.solve_equation)
    {
        int input_res = 0;

        if (options.solve_equation == INPUT_PARAMS)
            input_res = input(argc, argv, &options.equation_params);

        if (input_res)
        {
            process_error(input_res);
            return -1;
        }

        sSolution solution = {0, .0, .0};
        solve_general(&options.equation_params, &solution);

        assert(solution.x1 < solution.x2 || solution.rnum < 2);

        output(&solution);
    }

    return 0;
}
