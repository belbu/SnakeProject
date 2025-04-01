#include <curses.h>
#include "Board.hpp"
#include <chrono>

Board::Board(int height, int width, int level) {
    initscr();              // Inizializza lo schermo
    cbreak();               // Disabilita il buffering di linea
    noecho();               // Disabilita l'echo dell'input
    keypad(stdscr, TRUE);   // Abilita l'uso dei tasti speciali
    curs_set(0);            // Nasconde il cursore
    timeout(100);           // Imposta un timeout per l'input

    this->startY = (LINES - height) / 2;
    this->startX = (COLS - width) / 2;


    this->win = newwin(height, width, this->startY, this->startX);
    // box(win, 0, 0);
    // wrefresh(win);
    this->level = level;
    this->width = width;
    this->height = height;
    // score(0);
    this->startTime = time(nullptr); //
}

void Board::initializeBoard() {
    box(this->win,0,0);
    curs_set(0);
    wrefresh(win);

}


void Board::printHighestScore(int highestScore) {
    mvprintw(this->startY + this->height + 1, this->startX,"highest score: %d", highestScore);
}

int Board::Timer() {
    int difference = time(nullptr) - startTime;
    int remainingTime = 120 - difference; // 2 minuti totali
    if (remainingTime < 0) remainingTime = 0;
    mvprintw(this->startY - 2, this->startX + (this->width / 2) - 5, "Time: %02d:%02d", remainingTime / 60, remainingTime % 60);
    refresh();
    if (remainingTime > 0) return 1;
    else return 0;
}

void Board::score(int score) {
    mvprintw(this->startY - 1,this->startX,"score: %d",score);
}

void Board::printLevel() {
    mvprintw(this->startY - 1, this->startX + this->width - 10, "level: %d",this->level);
}

void Board::drawBorder() {
    werase(win);
    box(win, 0, 0);
}

Board::~Board() {
    delwin(this->win);     //elimina la finestra
    endwin();
}

WINDOW* Board::getWindow() const {
    return win;
}

void Board::refreshScreen() {
    wrefresh(win);
}

int Board::getScreenCols() const {
    return getmaxx(win);
}

int Board::getScreenRows() const {
    return getmaxy(win);
}




