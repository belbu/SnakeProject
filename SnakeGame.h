
#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include "Board.h"
#include "Snake.h"
#include "Apple.h"
#include "Livello.h"
#include <ctime>


class SnakeGame {
protected:
    Board board;
    Snake snake;
    Apple apple;
    ListaLivelli listaLivelli;
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
    void setLevel(int newLevel);
    void setSpeed(int newSpeed);
    void scoreMultiplier();
    void resetScore();
    void stopGame();
};



#endif //SNAKEGAME_H
