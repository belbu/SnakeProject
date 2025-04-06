#ifndef APPLE_H
#define APPLE_H
#include <ctime>
#include "Board.hpp"
#include "Snake.h"

class Apple {
protected:
    char icon;
    coordinates position;
    int screen_rows, screen_cols;
    WINDOW* win;
public:
    Apple(WINDOW* win, int screen_rows, int screen_cols);
    void random_position();
    void drawApple();
    coordinates GetPosition() const;
};



#endif //APPLE_H
