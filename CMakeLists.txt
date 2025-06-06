cmake_minimum_required(VERSION 3.16)
project(Snake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Usa find_package per trovare ncurses
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(Snake
        main.cpp
        Board.cpp
        Apple.cpp
        Livello.cpp
        menu.cpp
        Snake.cpp
        SnakeGame.cpp
)

target_link_libraries(Snake ${CURSES_LIBRARIES})
