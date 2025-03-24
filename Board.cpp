#include <curses.h>
#include "Board.hpp"

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
}

void Board::initializeBoard() {
    box(this->win,0,0);
    wrefresh(win);

}


void Board::printHighestScore(int highestScore) {
    mvprintw(this->startY + this->height + 1, this->startX,"highest score: %d", highestScore);
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




