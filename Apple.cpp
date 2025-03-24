#include "Apple.h"
#include <cstdlib>
#include <curses.h>
#include <ctime>

Apple::Apple(WINDOW* win, int screen_rows, int screen_cols) {
    std::srand(std::time(0));

    this->icon = '$';
    this->win = win;
    this->screen_cols = screen_cols;
    this->screen_rows = screen_rows;
    random_position();
}

void Apple::random_position() {
    this->position.row = std::rand() % (this->screen_rows - 2) + 1; // Evita i bordi
    this->position.col = std::rand() % (this->screen_cols - 2) + 1;
}

void Apple::drawApple() {
    mvwaddch(this->win,this->position.row, this->position.col, this->icon);
    wrefresh(this->win);
}

coordinates Apple:: GetPosition() const {
    return position;
}

