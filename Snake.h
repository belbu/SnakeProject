#ifndef SERPENTE_H
#define SERPENTE_H
#include <curses.h>

enum DIRECTION {
    U,
    D,
    L,
    R
};

struct coordinates {
    int row;
    int col;
};

class Snake {
protected:
    bool** body;
    DIRECTION direction;
    int length;
    coordinates tail;
    coordinates head;
    int screen_rows, screen_cols;
    WINDOW * win;
    coordinates* position; //array con le coordinate delle parti del serpente

public:
    Snake(int screen_rows, int screen_cols, int starting_length, WINDOW* win);
    ~Snake();
    void Draw();
    bool Move(); //ritorna falso se snake mangia se stesso
    bool CheckSelfCollision(const coordinates& new_head) const;
    coordinates get_head();
    void GetBody(coordinates* buffer, int& bodyLength) const;
    void reset();
    int getlength();
    bool CanChangeDirection(int key);
    void setDiredction(int key);

};



#endif //SERPENTE_H
