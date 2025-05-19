#include <curses.h>
#include "Snake.h"



Snake::Snake(int screen_rows, int screen_cols, int starting_length, WINDOW* win) {
    this->screen_cols = screen_cols;
    this->screen_rows = screen_rows;
    this->length = starting_length;
    this->win = win;
    this->direction = R;
    position = new coordinates[starting_length];

    //crea matrice rows*cols per mappare snae
    body = new bool*[screen_rows];
    for (int i = 0; i < screen_rows; i++) {
        body[i] = new bool[screen_cols];
        for (int j = 0; j < screen_cols; j++) {
            body[i][j] = false;
        }
    }
    // setta posizione iniziale centrata
    int start_row = screen_rows / 2;
    int start_col = screen_cols / 2;
    for (int i = 0; i < starting_length; i++) {
        body[start_row][start_col + i] = true;
        position[i] = {start_row,start_col + i};
    }

    this->tail.row = start_row;
    this->tail.col = start_col;
    this->head.col = start_col + starting_length - 1;
    this->head.row = start_row;

}

Snake::~Snake() {
    for (int i = 0; i < screen_rows; i++) {
        delete[] body[i];
    }
    delete[] body;
    // delete[] position;
}

bool Snake::CheckSelfCollision(const coordinates& new_head) const {
    return this->body[new_head.row][new_head.col];
}

bool Snake::Move() {
    coordinates new_head{
        this->head.row,
        this->head.col
    };

    if (this->direction == U) new_head.row--;
    if (this->direction == D) new_head.row++;
    if (this->direction == L) new_head.col--;
    if (this->direction == R) new_head.col++;

    //gestione bordi per effetto pacman
    if (new_head.row < 1) new_head.row = screen_rows - 2;
    else if (new_head.row >= screen_rows - 1) new_head.row = 1;
    if (new_head.col < 1) new_head.col = screen_cols - 2;
    else if (new_head.col >= screen_cols - 1) new_head.col = 1;

    //controllo se la testa è già occupata
    if (CheckSelfCollision(new_head)) {
        printw("Game Over! Collisione con se stesso.\n");
        refresh();
        getch();
        endwin();
        return false;
    }
    //elimino la coda dalla mappa e aggiungo la testa
    body[this->tail.row][this->tail.col] = false;

    body[new_head.row][new_head.col] = true;
    this->head.row = new_head.row;
    this->head.col = new_head.col;
    //scala tutti i componenti di snake di 1 nell array in modo da avere la prossima coda all indice 0
    for (int i = 0; i < length - 1; i++) {
        position[i] = position [i+1];
    }
    tail.row = position[0].row;
    tail.col = position[0].col;
    position[length-1].col = new_head.col;
    position[length-1].row = new_head.row;

    return true;
}

void Snake::ChangeDirection(int key) {
    switch (key) {
        case KEY_UP:    if (direction != D) direction = U; break;
        case KEY_DOWN:  if (direction != U) direction = D; break;
        case KEY_LEFT:  if (direction != R) direction = L; break;
        case KEY_RIGHT: if (direction != L) direction = R; break;
    }
}

void Snake::Draw() {
    start_color();
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    for (int i = 0; i < screen_rows; i++) {
        for (int j = 0; j < screen_cols; j++) {
            if (body[i][j]) {
                if (i == this->head.row && j == this->head.col) {
                    wattron(win, COLOR_PAIR(2));
                    mvwaddch(win,i,j,'X');
                    wattroff(win, COLOR_PAIR(2));
                }else {
                    wattron(win, COLOR_PAIR(2));
                    mvwaddch(win, i, j, 'O');
                    wattroff(win, COLOR_PAIR(2));
                }
            }
        }
    }
}

coordinates Snake::get_head() {
    return this->head;
}

void Snake::GetBody(coordinates* buffer, int& bodyLength) const {
    bodyLength = this->length;
    for (int i = 0; i < bodyLength; i++) {
        buffer[i] = position[i];
    }
}

int Snake::getlength() {
    return this->length;
}

void Snake::reset() {
    direction = R;
}
