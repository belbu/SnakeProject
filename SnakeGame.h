
#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include "Board.hpp"
#include "Snake.h"
#include "Apple.h"


class SnakeGame {
protected:
    Board board;
    Snake snake;
    Apple apple;
    void CheckAppleCollision();
    void NewApplePosition();
    bool gameon;
    int score;
    int level;
    int highestScore;
    void newHighestScore();
public:
    SnakeGame(int mapHeight, int mapWidth, int snakeLength, int level);
    void run();
    int getScore();
};



#endif //SNAKEGAME_H
