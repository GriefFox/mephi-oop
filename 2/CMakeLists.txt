# установка версии CMake
cmake_minimum_required(VERSION 3.16)

find_package(Catch2 3 REQUIRED)
# название проекта (обязательно)
project(oopprog2)
# установка стандарта языка - C++20
set(CMAKE_CXX_STANDARD 23)
# установка флагов компилятора: CMAKE_CXX_FLAGS += -Wall -Wextra
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")
# создание библиотеки prog

add_library(rouce Table.hpp Table.cpp Resource.hpp Resource.cpp)
# подключение библиотеки prog1 ко всем таргетам, создаваемым далее
# альтернатива: target_link_libraries(main prog)
link_libraries(rouce)

add_executable(main main.cpp)
