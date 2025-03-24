#include <curses.h>
#include "menu.h"
#include "SnakeGame.h"

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

void menu::setLength(int& snakeLength) {
    bool valid = false;
    while (!valid) {
        clear();
        printw("Enter the snake length:...\n");
        echo();
        refresh();
        int userLength;
        scanw("%d, &userLength");

        if (userLength > 3 && userLength < 9) {
            snakeLength = userLength;
            printw("Snake length set to %d.\n", snakeLength);
            valid = true;
        }else {
            printw("invalid length, please choose a length between 3 and 10\n");
            printw("Press a key to continue..\n");
            refresh();
            getch();
        }
    }
    noecho();
    printw("press a key to continue");
    getch();
    refresh();

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
    int user_input;
    int choice;
    int snakeLength = 4;

    bool show = true;
    while (show) {
        clear();
        printw("----- SNAKE MENU -----\n");
        printw("1 Start game\n");
        printw("2 Set snake length\n");
        printw("3 Quit\n");
        printw("Choose an option\n");
        refresh();

        choice = getch();
        if (choice >= '1' && choice <= '3') {
            int user_input = choice - '0'; // Converti il carattere in un numero (es: '1' -> 1)
            if (user_input == 1) {
                startGame(snakeLength);
                return;
            }
            else if (user_input == 2) {
                setLength(snakeLength);
                show = false;
            }
            else if (user_input == 3) {
                return;
            }else {
                printw("\nPress a valid key...\n");
                getch();
            }
        }
    }
}



