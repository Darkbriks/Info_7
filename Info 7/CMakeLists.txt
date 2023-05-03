cmake_minimum_required(VERSION 3.26)

project(test)

set(SRC main.cpp board.cpp type.cpp view.cpp)
set(HEADERS board.h type.h view.h)

add_executable(test ${SRC} ${HEADERS})