#include <curses.h>
#include "Snake.h"

Snake::Snake(int screen_rows, int screen_cols, int starting_length, WINDOW* win) {
    this->screen_cols = screen_cols;
    this->screen_rows = screen_rows;
    this->length = starting_length;
    this->win = win;
    this->direction = R;

    //crea matrice rows*cols
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
}

bool Snake::CheckSelfCollision(const coordinates& new_head) const {
    // Verifica se la nuova posizione della testa è occupata dal corpo del serpente
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

    if (CheckSelfCollision(new_head)) {
        printw("Game Over! Collisione con se stesso.\n");
        refresh();
        getch();
        endwin();
        return false;
    }


    body[this->tail.row][this->tail.col] = false;

    find_next_tail();

    body[new_head.row][new_head.col] = true;
    this->head.row = new_head.row;
    this->head.col = new_head.col;

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
    for (int i = 0; i < screen_rows; i++) {
        for (int j = 0; j < screen_cols; j++) {
            if (body[i][j]) {
                if (i == this->head.row && j == this->head.col) {
                    mvwaddch(win,i,j,'X');
                }else {
                    mvwaddch(win, i, j, 'O');
                }
            }
        }
    }
}


coordinates Snake::get_head() {
    return this->head;
}

coordinates* Snake:: GetBody(int& bodyLength) const {
    // Conta il numero di segmenti del corpo
    bodyLength = 0;
    for (int i = 0; i < screen_rows; i++) {
        for (int j = 0; j < screen_cols; j++) {
            if (body[i][j]) {
                bodyLength++;
            }
        }
    }

    // Alloca un array dinamico per memorizzare le coordinate del corpo
    coordinates* bodySegments = new coordinates[bodyLength];

    // Riempie l'array con le coordinate del corpo
    int index = 0;
    for (int i = 0; i < screen_rows; i++) {
        for (int j = 0; j < screen_cols; j++) {
            if (body[i][j]) {
                bodySegments[index] = {i, j};
                index++;
            }
        }
    }

    return bodySegments;
}

void Snake::reset() {
    direction = R;
}


void Snake::find_next_tail() {
    coordinates next_tail;

    // Controlla tutte e quattro le direzioni per trovare il prossimo segmento del corpo
    int directions[4][2] = {
        {-1, 0}, // Su  (riga decrementata)
        {1, 0},  // Giù (riga incrementata)
        {0, -1}, // Sinistra (colonna decrementata)
        {0, 1}   // Destra   (colonna incrementata)
    };

    for (int i = 0; i < 4; i++) {    //itera sulle 4 posizioni
        next_tail.row = tail.row + directions[i][0];
        next_tail.col = tail.col + directions[i][1];

        // Gestione effetto Pac-Man
        if (next_tail.row < 1) next_tail.row = this->screen_rows - 2;
        else if (next_tail.row >= this->screen_rows -1) next_tail.row = 1;
        if (next_tail.col < 1) next_tail.col = this->screen_cols - 2;
        else if (next_tail.col >= this->screen_cols - 1) next_tail.col = 1;


        if (this->body[next_tail.row][next_tail.col]) {
            tail.row = next_tail.row;
            tail.col = next_tail.col;
            break;
        }
    }
}

//per cercare la nuova coda non bisogna basarsi solamente sulla direzione attuale
//perché il serpente potrebbe cambiare direzione, e la coda potrebbe non essere sempre nella direzione opposta alla testa
// Per trovare correttamente la nuova coda, dobbiamo cercare il prossimo segmento del corpo del serpente in tutte e quattro le direzioni,

//Utilizziamo un array directions per rappresentare le quattro
//Iteriamo su tutte e quattro le direzioni per cercare il prossimo segmento del corpo.
//Se il prossimo segmento è fuori dai limiti della mappa, lo riportiamo all'interno utilizzando l'effetto Pac-Man (trapasso dei bordi).
//Se troviamo un segmento del corpo nella direzione corrente, aggiorniamo la posizione della coda e usciamo dal ciclo.

//VECCHIO CODICE

// void Snake::find_next_tail() {
//     coordinates next_tail;
//     if (this->direction == U) {
//         next_tail.col = tail.col;
//         next_tail.row = tail.row - 1;
//     }
//     else if (this->direction == D) {
//         next_tail.col = tail.col;
//         next_tail.row = tail.row + 1;
//     }
//     else if (this->direction == R) {
//         next_tail.row = tail.row;
//         next_tail.col = tail.col + 1;
//     }
//     else if (this->direction == L) {
//         next_tail.row = tail.row;
//         next_tail.col = tail.col - 1;
//     }
//     //gestione effetto pacman
//     if (next_tail.row < 0) next_tail.row = this->screen_rows - 1;
//     else if (next_tail.row >= this->screen_rows) next_tail.row = 0;
//     if (next_tail.col < 0) next_tail.col = this->screen_cols -1;
//     else if (next_tail.col >= this->screen_cols) next_tail.col = 0;
//
//     if (this->body[next_tail.row][next_tail.col]) {
//         tail.row = next_tail.row;
//         tail.col = next_tail.col;
//     }


// Supponiamo che:
//
//     La mappa abbia dimensioni screen_rows = 20 e screen_cols = 40.
//
//     La coda del serpente si trovi in posizione tail.row = 10, tail.col = 10.
//
//     Il corpo del serpente occupi le posizioni (10, 10), (10, 11), (10, 12).
//
// Passaggi:
//
//     Direzione Su ({-1, 0}):
//
//         Nuova posizione: (10 - 1, 10) = (9, 10).
//
//         Verifica se body[9][10] è true. Se sì, aggiorna la coda e interrompe il ciclo.
//
//     Direzione Giù ({1, 0}):
//
//         Nuova posizione: (10 + 1, 10) = (11, 10).
//
//         Verifica se body[11][10] è true. Se sì, aggiorna la coda e interrompe il ciclo.
//
//     Direzione Sinistra ({0, -1}):
//
//         Nuova posizione: (10, 10 - 1) = (10, 9).
//
//         Verifica se body[10][9] è true. Se sì, aggiorna la coda e interrompe il ciclo.
//
//     Direzione Destra ({0, 1}):
//
//         Nuova posizione: (10, 10 + 1) = (10, 11).
//
//         Verifica se body[10][11] è true. Se sì, aggiorna la coda e interrompe il ciclo.
//
