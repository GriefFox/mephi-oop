# установка версии CMake
cmake_minimum_required(VERSION 3.16)
# название проекта (обязательно)
project(oopprog1)
# установка стандарта языка - C++20
set(CMAKE_CXX_STANDARD 23)
# установка флагов компилятора: CMAKE_CXX_FLAGS += -Wall -Wextra
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")
# создание библиотеки prog
add_library(prog prog.hpp prog.cpp)
# подключение библиотеки prog1 ко всем таргетам, создаваемым далее
# альтернатива: target_link_libraries(main prog)
link_libraries(prog)
# создание исполняемого файла
add_executable(main main.cpp dia.cpp)