#ifndef OOPPROG1_PROG1_H
#define OOPPROG1_PROG1_H
#include <iostream>
#include <string>
#include <limits>
#include <cstring>
#include <vector>
namespace Prog1 {
    // шаблонная функция ввода одного числа
    template<class T>
    T get(T min = std::numeric_limits<T>::lowest(), T max = std::numeric_limits<T>::max()) {
        T a;
        while(true) {
            std::cin >> a;
            if(std::cin.eof()) // обнаружен конец файла
                throw std::runtime_error("Failed to read: EOF");
            else if(std::cin.bad()) // обнаружена невосстановимая ошибка входного потока
                throw std::runtime_error(std::string("Failed to read: ") + strerror(errno));
                // прочие ошибки (неправильный формат ввода) либо число не входит в заданный диапазон
            else if(std::cin.fail() || a < min || a > max) {
                std::cin.clear(); // очищаем флаги состояния потока
                // игнорируем все символы до конца строки
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "repeat please!" << std::endl;
            }
            else // успешный ввод
                return a;
        }
    }

    const char*game(const char**);
    std::string game(std::vector<std::string>);
}
#endif //OOPPROG1_PROG1_H