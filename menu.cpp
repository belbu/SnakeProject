#include <curses.h>
#include "menu.h"
#include "SnakeGame.h"
#include <iostream>
#include <fstream>
using namespace std;

menu::menu() : game(nullptr) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

}

menu::~menu() {
    if (game) delete game;
    endwin();
}

void menu::initScreen() {
    endwin(); // Chiude qualsiasi finestra esistente
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    refresh();
}

void menu::startGame() {
    bool playAgain = true;

    while (playAgain) {
        clear();
        printw("----- NEW GAME -----\n");
        printw("Press any key to start...");
        refresh();
        nodelay(stdscr, FALSE);
        getch();
        clear();

        if (game) {
            delete game;
            game = nullptr;
        }

        game = new SnakeGame(20, 40, 6, 1);
        game->run();

        initScreen();
        clear();
        printw("----- GAME OVER -----\n");
        printw("Your score: %d\n\n", game->getScore());
        printw("1. Play Again\n");
        printw("2. Return to Menu\n");
        printw("3. Quit Game\n");
        printw("Choose an option: ");
        refresh();

        int choice;
        do {
            choice = getch();
        } while (choice < '1' || choice > '3');

        switch (choice) {
            case '1': continue;  // Continua il loop
            case '2': playAgain = false; break;
            case '3': playAgain = false; break;
        }
    }
    showMenu();
}

void menu::showMenu() {
    initScreen();

    bool show = true;
    while (show) {

        clear();
        printw("----- SNAKE MENU -----\n");
        printw("1 Start game\n");
        printw("2 See ranking\n");
        printw("3 Quit\n");
        printw("Choose an option\n");
        refresh();

        int choice = getch();
        if (choice >= '1' && choice <= '3') {
            int user_input = choice - '0';
            if (user_input == 1) {
                startGame();
                return;
            }
            else if (user_input == 2) {
                showHighScores();
                break;
            }
            else if (user_input == 3) {
                show = false;
            }
            else {
                printw("\nPress a valid key...\n");
                getch();
            }
        }
    }
}

void menu::showHighScores() {
    initScreen();
    clear();

    std::ifstream file("punteggio.txt");
    int highestScore = 0;

    if (file && file.peek() != std::ifstream::traits_type::eof()) {
        file >> highestScore;
        if (file.fail()) highestScore = 0;
    }
    file.close();

    printw("HIGH SCORE: %d\n\n", highestScore);
    printw("Press any key to return to menu...");
    refresh();

    nodelay(stdscr, FALSE);

    getch();

    showMenu();
}
