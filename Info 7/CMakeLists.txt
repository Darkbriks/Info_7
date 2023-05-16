#cmake_minimum_required(VERSION 3.22)

project(Chess)

set(SRC Main.cpp Source/board.cpp Source/game.cpp Source/historique.cpp Source/mask.cpp Source/type.cpp Source/view.cpp)
set(HEADERS Header/board.h Header/game.h Header/historique.cpp Header/mask.h Header/type.h Header/view.h)

add_executable(Chess ${SRC} ${HEADERS})