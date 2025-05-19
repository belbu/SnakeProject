#cmake_minimum_required(VERSION 3.30)
#project(Snake)
#
#set(CMAKE_CXX_STANDARD 20)
#
#add_executable(Snake main.cpp
#        Board.cpp
#        Board.h
#        Apple.cpp
#        Apple.h
#        Livello.cpp
#        Livello.h
#        menu.cpp
#        menu.h
#        Snake.cpp
#        Snake.h
#        SnakeGame.cpp
#        SnakeGame.h
#)
#find_package(Curses REQUIRED)
#include_directories(${CURSES_INCLUDE_DIR})
#target_link_libraries(Snake ${CURSES_LIBRARIES})

cmake_minimum_required(VERSION 3.30)
project(Snake)

# Percorsi per MSYS2/Mingw64
set(NCURSES_INCLUDE_DIR "C:/msys64/mingw64/include/ncurses")
set(NCURSES_LIBRARY "C:/msys64/mingw64/lib/libncursesw.a")

# Configurazione compilazione
add_executable(Snake
        main.cpp
        Board.cpp
        Apple.cpp
        Livello.cpp
        menu.cpp
        Snake.cpp
        SnakeGame.cpp
)

# Collegamento librerie
target_link_libraries(Snake
        ${NCURSES_LIBRARY}
        -lncursesw  # Versione wide char
        -lmenuw     # Menu library
        -lformw     # Form library
)

# Opzioni per linking statico (opzionale)
target_link_options(Snake PRIVATE -static)
