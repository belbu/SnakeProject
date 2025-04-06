#include <curses.h>
#include <ctime>


#ifndef MAPPA_H
#define MAPPA_H

class Board {
protected:
    WINDOW* win;
    int startX;
    int startY;
    int level;
    int width;
    int height;
    time_t startTime;      // Momento di inizio/conteggio
    int totalDuration;     // Durata totale in secondi (es. 120)
    int frozenTime;        // Tempo rimanente quando in pausa
    bool timerActive;      // Stato del timer
    int initialDuration;  // Valore fisso (es. 120)
    int remainingTime;    // Variabile dinamica
public:
    Board(int height, int width, int level);
    ~Board();
    void drawBorder();
    void refreshScreen();
    WINDOW* getWindow() const;  //const in modo da non modificare l oggetto su cui è chiamata
    int getScreenRows() const;  //restituisce righe finestra
    int getScreenCols() const; //restituisce colonne finestra
    void score(int score);
    void printLevel();
    void printHighestScore(int highestScore);
    void initializeBoard();
    int Timer();
    void StopTimer();
    void StartTimer();
    int getStartY() const;
    int getStartX() const;
    int getWidth() const;
    int getHeight() const;

};



#endif //MAPPA_H
