#ifndef MENU_H
#define MENU_H

#include <curses.h>

class menu {
protected:
    void startGame(int snakeLength);
    void setLength(int& snakeLength);
public:
    menu();
    ~menu();
    void showMenu();

};



#endif //MENU_H
