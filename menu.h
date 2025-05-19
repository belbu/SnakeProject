#ifndef MENU_H
#define MENU_H
#include "SnakeGame.h"

class menu {
public:
    menu();
    ~menu();
    void showMenu();
    void startGame();
    void showClassifica();
    void HighScoreLoaded();
    void initScreen();
    void artwork();

private:
    SnakeGame* game;
};

#endif // MENU_H
