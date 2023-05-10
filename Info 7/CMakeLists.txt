#cmake_minimum_required(VERSION 3.22)

project(test)

set(SRC Main.cpp Source/board.cpp Source/mask.cpp Source/type.cpp Source/view.cpp)
set(HEADERS Header/board.h Header/mask.h Header/type.h Header/view.h)

add_executable(test ${SRC} ${HEADERS})