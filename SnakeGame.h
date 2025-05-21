
#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include "Board.h"
#include "Snake.h"
#include "Apple.h"
#include <ctime>


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
    bool isPaused;
    void Classifica() ;
    int speed;

public:
    SnakeGame(int mapHeight, int mapWidth, int snakeLength,int level);
    void run();
    int getScore();
    int getHighestScore();
    void PauseGame();
    void ScoreMultiplier();
};



#endif //SNAKEGAME_H
