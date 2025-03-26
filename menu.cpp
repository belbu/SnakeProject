#include <curses.h>
#include "menu.h"
#include "SnakeGame.h"
#include <iostream>
#include <fstream>
using namespace std;

menu::menu() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
}

menu::~menu() {
    endwin();
}

void menu::startGame(int snakeLength) {
    clear();
    printw("Game is starting, press a key to continue...\n");
    refresh();
    getch();
    endwin();
    int mapHeight = 20;
    int mapWidth = 40;
    SnakeGame game(mapHeight, mapWidth, snakeLength,1);
    game.run();
}

void menu::showMenu() {
    int choice;
    int snakeLength = 4;

    bool show = true;
    while (show) {
        clear();
        printw("----- SNAKE MENU -----\n");
        printw("1 Start game\n");
        printw("2 Visualizza Classifica\n");
        printw("3 Quit\n");
        printw("Choose an option\n");
        refresh();

        choice = getch();
        if (choice >= '1' && choice <= '3') {
            int user_input = choice - '0';
            if (user_input == 1) {
                startGame(snakeLength);
                return;  // ✅ Esce immediatamente
            }
            else if (user_input == 2) {
                clear();
                refresh();
                std::ifstream file("punteggio.txt");
                int highestScore = 0;

                if (file && file.peek() != std::ifstream::traits_type::eof()) {
                    file >> highestScore;
                    if (file.fail()) highestScore = 0;
                }

                file.close();
                std::cout << "Il punteggio massimo è: " << highestScore << std::endl;
                getch();  // 🔹 Aspetta che l'utente prema un tasto prima di continuare
            }
            else if (user_input == 3) {
                return;  // ✅ Esce immediatamente dal menu
            }
            else {
                printw("\nPress a valid key...\n");
                getch();
            }
        }
    }
}



