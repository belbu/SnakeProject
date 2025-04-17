#include <curses.h>
#include "Board.hpp"
#include <ctime>

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
    totalDuration = 20; // 2 minuti
    initialDuration = 120;
    time(&startTime);
    frozenTime = totalDuration;
    timerActive = true;
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
    if (!timerActive) {
        // Modalità pausa - mostra tempo congelato
        mvprintw(this->startY - 2, this->startX + (this->width / 2) - 5,
                "Time: %02d:%02d", frozenTime / 60, frozenTime % 60);
        refresh();
        return (frozenTime > 0);
    }

    time_t currentTime;
    time(&currentTime);
    double elapsed = difftime(currentTime, startTime);
    int remainingTime = totalDuration - static_cast<int>(elapsed);

    if (remainingTime < 0) remainingTime = 0;

    // Aggiorna display
    mvprintw(this->startY - 2, this->startX + (this->width / 2) - 5,
            "Time: %02d:%02d", remainingTime / 60, remainingTime % 60);
    refresh();

    return (remainingTime > 0);
}

void Board::StopTimer() {
    if (timerActive) {
        time_t currentTime;
        time(&currentTime);
        frozenTime = totalDuration - static_cast<int>(difftime(currentTime, startTime));
        timerActive = false;
    }
}

void Board::StartTimer() {
    if (!timerActive) {
        time(&startTime);
        startTime -= (totalDuration - frozenTime);
        timerActive = true;
    }
}

void Board::score(int score) {
    mvprintw(this->startY - 1,this->startX,"score: %d",score);
}

void Board::setLevel(int level) {
    this->level = level;
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

void Board::ResetTimer() {
    time(&startTime); // Imposta startTime all'orario corrente
    frozenTime = totalDuration; // Reimposta frozenTime
    timerActive = true; // Riattiva il timer se era in pausa
}


int Board::getStartY() const { return startY; }
int Board::getStartX() const { return startX; }
int Board::getWidth() const { return width; }
int Board::getHeight() const { return height; }






