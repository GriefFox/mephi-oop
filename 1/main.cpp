#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
// #include <stdio.h>
// #include <string>
#include "prog.hpp"
#include "dia.hpp"
using namespace Prog1;

//TODO вынести функции диалога в отедельный файл


// основная функция
int main() {
    int ch;
    try {
        while (true){
            std::cout << "1. to use const char *" << std::endl << "2. to use std::string" << std::endl;
            std::cout << "3. to exit " << std::endl;
            ch = get<int>();
            switch (ch) {
                case 1:
                {
                    chr_dia();
                    // free((void*)res);
                    break;
                }
                case 2:
                {
                    string_dia();
                    break;
                }
                case 3:
                    return 0;
            }
        }
    }
    catch(const std::bad_alloc& ba) { // в случае ошибок выделения памяти
        std::cerr << "Not enough memory" << std::endl;
        // erase(matrix);
        return 1;
    }
    catch(const std::exception& e) { // в случае прочих исключений
        std::cerr << e.what() << std::endl;
        // erase(matrix);
        return 1;
    }
    return 0;
}