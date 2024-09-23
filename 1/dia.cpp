#include "dia.hpp"
#include <stdio.h>
#include <iostream>
#include <string>
#include "prog.hpp"
using namespace Prog1;


void chr_dia(){
    const char * evil = "1234567890!@#{}$%^&*()[]/\\|=+ ";
    std::cout << "Input number of cities" << std::endl;
    int b = get<int>();
    char **inp = new char*[b+1]{}; 
    bool fl = 0;
    for (int i=0; i<b; i++){
        std::string buf;
        std::cin >> buf;
        if (std::cin.eof()){
            for (int j=0;j<i;j++){
                char *& c =inp[j];
                delete[] c;
            }
            char **& tmp = inp;
            delete[] tmp;
            throw std::runtime_error("Failed to read: EOF");
        }
        else if (std::cin.bad()){
            for (int j=0;j<i;j++){
                char *& c =inp[j];
                delete[] c;
            }
            char **& tmp = inp;
            delete[] tmp;
            throw std::runtime_error(std::string("Failed to read: ") + strerror(errno));
        }
        for (int j = 0; j< 30;j++){
            int test = buf.contains(evil[j]);
            if (test != 0){
                fl = 1;
                std::cout << "Evil character found! Repeat please" << std::endl;
                break;
            }
        }
        if (fl){
            i--;
            fl = 0;
            continue;
        }
        inp[i] = new char[buf.length()+1];
        strcpy(inp[i], buf.c_str());
    }
    const char * res;
    try {                
        res = game((const char **) inp);
    } catch(...) {
        for (int i = 0; i<b;i++){
          delete[] inp[i];
        }
        delete[] inp;
        throw;
    }
    printf("Result: %s\n", res);
    for (int i = 0; i<b;i++){
        delete[] inp[i];
    }
    delete[] inp;
    delete[] res;
}

void string_dia(){
    std::string res;
    std::cout << "Input number of cities" << std::endl;
    int b = get<int>();
    std::vector<std::string> inp(b);
    int fl = 0;
    for (int i=0; i<b; i++){
        std::string & buf = inp[i];
        std::cin >> buf;
        if (std::cin.eof()){
            throw std::runtime_error("Failed to read: EOF");
        }
        else if (std::cin.bad()){
            throw std::runtime_error(std::string("Failed to read: ") + strerror(errno));
        }
        for (int j = 0; j< 30;j++){
            const char * evil = "1234567890!@#{}$%^&*()[]/\\|=+ ";
            int test = buf.contains(evil[j]);
            if (test != 0){
                fl = 1;
                std::cout << "Evil character found! Repeat please" << std::endl;
                break;
            }
        }
        if (fl){
            i--;
            fl = 0;
            continue;
        }
    }
    res = game(inp);
    std::cout << "Result: " << res << std::endl; // вывод результата
}
