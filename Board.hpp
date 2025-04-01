#include <curses.h>


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
    int startTime; //
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
};



#endif //MAPPA_H
