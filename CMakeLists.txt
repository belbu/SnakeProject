cmake_minimum_required(VERSION 3.30)
project(Snake)

set(CMAKE_CXX_STANDARD 20)

add_executable(Snake main.cpp
        Board.cpp
        Board.hpp
        Snake.cpp
        Snake.h
        Apple.cpp
        Apple.h
        SnakeGame.cpp
        SnakeGame.h
        menu.cpp
        menu.h
)
