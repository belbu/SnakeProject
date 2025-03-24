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

    void find_next_tail(); //trova la prossima coda quando snake si sposta
public:
    Snake(int screen_rows, int screen_cols, int starting_length, WINDOW* win);
    ~Snake();
    void ChangeDirection(int key);
    void Draw();
    bool Move();
    bool CheckSelfCollision(const coordinates& new_head) const; //ritorna true se lo snake mangia se stesso
    coordinates get_head();
    coordinates* GetBody(int& bodyLength) const;
};



#endif //SERPENTE_H
