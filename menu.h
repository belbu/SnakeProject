#ifndef MENU_H
#define MENU_H

class SnakeGame;

class menu {
public:
    menu();
    ~menu();
    void showMenu();
    void startGame();
    void showClassifica();
    void HighScoreLoaded();
    void initScreen();

private:
    SnakeGame* game;
};

#endif // MENU_H
