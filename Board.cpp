#include <curses.h>
#include "Board.h"
#include <ctime>

Board::Board(int height, int width) {
    initscr();              // Inizializza lo schermo
    cbreak();               // Disabilita il buffering di linea
    noecho();               // Disabilita l'echo dell'input
    keypad(stdscr, TRUE);   // Abilita l'uso dei tasti speciali
    curs_set(0);            // Nasconde il cursore
    timeout(100);           // Imposta un timeout per l'input

    this->startY = (LINES - height) / 2;
    this->startX = (COLS - width) / 2;


    this->win = newwin(height, width, this->startY, this->startX);
    this->width = width;
    this->height = height;

    totalDuration = 120; // 2 minuti
    initialDuration = 120;
    time(&startTime);
    frozenTime = totalDuration;
    timerActive = true;
}


void Board::printHighestScore(int highestScore) {
    mvprintw(this->startY + this->height + 1, this->startX,"highest score: %d", highestScore);
}

bool Board::Timer() {
    if (!timerActive) {
        // modalità pausa, mostra tempo congelato
        mvprintw(this->startY - 2, this->startX + (this->width / 2) - 5,
                "Time: %02d:%02d", frozenTime / 60, frozenTime % 60);
        refresh();
        return (frozenTime > 0);
    }

    time_t currentTime;
    time(&currentTime);
    double elapsed = difftime(currentTime, startTime); //calcola tempo trascorso
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
        time(&currentTime); //prende il tempo corrente
        frozenTime = totalDuration - static_cast<int>(difftime(currentTime, startTime)); //calcola tempo rimanente
        timerActive = false;
    }
}

void Board::StartTimer() {
    if (!timerActive) {
        time(&startTime);
        startTime -= (totalDuration - frozenTime); //reimposta startTime al tempo corrente - il tempo già usato
        timerActive = true;
    }
}

void Board::score(int score) {
    mvprintw(this->startY - 1,this->startX,"score: %d",score);
}


void Board::printLevel(int level) {
    mvprintw(this->startY - 1, this->startX + this->width - 10, "level: %d",level);
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

void Board::printAll(int _score, int highestScore, int level) {
    printLevel(level);
    score(_score);
    printHighestScore(highestScore);
    drawBorder();
}








