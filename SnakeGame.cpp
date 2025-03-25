#include "SnakeGame.h"
#include "Board.hpp"
#include "Snake.h"
#include "Apple.h"
#include <iostream>
#include <fstream>
using namespace std;

SnakeGame::SnakeGame(int mapHeight, int mapWidth, int snakeLength, int level) : board(mapHeight,mapWidth,level),
   snake(board.getScreenRows(), board.getScreenCols(), snakeLength, board.getWindow()),
   apple(board.getWindow(),board.getScreenRows(),board.getScreenCols()){
   this->gameon = true;
   this->score = 0;
   this->level = level;
   this->highestScore = 0; //da modificare
}

void SnakeGame::CheckAppleCollision() {
   coordinates head = snake.get_head();

   if (head.row == apple.GetPosition().row && head.col == apple.GetPosition().col) {
      this->score++;
      NewApplePosition();
   }
}

void SnakeGame::NewApplePosition() {
   bool valid = false;
   while (!valid) {
      apple.random_position();

      int bodyLength;
      coordinates* body = snake.GetBody(bodyLength);
      valid = true;
      for (int i = 0; i < bodyLength && valid; i++) {
         if (body[i].row == apple.GetPosition().row && body[i].col == apple.GetPosition().col) {
            valid = false;
         }
      }
      delete[] body;
   }
}


void SnakeGame::run() {
   int key;
   int last_key = KEY_RIGHT;

   while (gameon) {
      board.initializeBoard();

      key = getch();

      if (key == 'q') {
         this->gameon = false;
         break;
      }
      if (key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT || key == KEY_RIGHT) {
         last_key = key;
      }

      snake.ChangeDirection(last_key);
      gameon = snake.Move();
      if (gameon) {
         CheckAppleCollision();
         board.printLevel();
         board.score(this->score);
         board.printHighestScore(this->highestScore);
         board.drawBorder();
         snake.Draw();
         apple.drawApple();
         board.refreshScreen();
         newHighestScore();
      }
      napms(70);
   }

   if (!gameon) {
      endwin();
   }
}


void SnakeGame::newHighestScore() {
   if (this->score > this->highestScore) {
      this->highestScore = this->score;
      ofstream outputFile; /* Dichiarazione di tipo */
      outputFile.open("punteggio.txt"); /* Apertura del file */
      outputFile << this->highestScore;
      outputFile.close();
   }
}


