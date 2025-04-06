#ifndef MENU_H
#define MENU_H

#include <curses.h>
#include "SnakeGame.h"

class menu {
protected:
    void startGame();
    SnakeGame* game;
public:
    menu();
    ~menu();
    void showMenu();
    void Changelevel(); //TODO
    void initScreen();
    void showClassifica();
    void HighScoreLoaded();
};



#endif //MENU_H
