
#include "SnakeGame.h"
#include "Board.hpp"
#include "Snake.h"
#include "Apple.h"
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

SnakeGame::SnakeGame(int mapHeight, int mapWidth, int snakeLength, int level) : board(mapHeight,mapWidth,level),
   snake(board.getScreenRows(), board.getScreenCols(), snakeLength, board.getWindow()),
   apple(board.getWindow(),board.getScreenRows(),board.getScreenCols()){
   this->gameon = true;
   this->score = 0;
   this->level = level;
   this->isPaused = false;
   std::ifstream file("punteggio.txt");
   if (file) {  // Se il file esiste ed è leggibile
      file >> this->highestScore;  // Legge il valore numerico
      if (file.fail()) { // Se la lettura non è andata a buon fine
         this->highestScore = 0; // Imposta un valore di default
      }
   } else {
      this->highestScore = 0;  // Se il file non esiste, imposta 0
   }

   file.close();  // Chiude il file
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
      valid = true;

      int bodyLength = snake.getlength();
      coordinates* body = new coordinates[bodyLength];
      snake.GetBody(body, bodyLength);

      for (int i = 0; i < bodyLength && valid; i++) {
         if (body[i].row == apple.GetPosition().row &&
             body[i].col == apple.GetPosition().col) {
            valid = false;
             }
      }
      delete[] body;
   }
}


void SnakeGame::run() {
   gameon = true;
   score = 0;
   snake.reset();
   apple.random_position();

   int key;
   int last_key = KEY_RIGHT;

   while (gameon) {
      timeout(100);
      int ch = getch();
      if (ch != ERR) {
         if (ch == ' ') {
            PauseGame();
         } else if (ch == 'q') {
            this->gameon = false;
            Classifica();
            break;
         } else if (!isPaused && (ch == KEY_UP || ch == KEY_DOWN || ch == KEY_LEFT || ch == KEY_RIGHT)) {
            key = ch;
         }
      }
      if (!isPaused){
         if (key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT || key == KEY_RIGHT) {
            last_key = key;
         }
         if (!isPaused) {
            snake.ChangeDirection(last_key);
            gameon = snake.Move();
         }
         if (gameon) {
            CheckAppleCollision();
            board.printLevel();
            board.score(this->score);
            board.printHighestScore(this->highestScore);
            board.drawBorder();
            snake.Draw();
            apple.drawApple();
            board.refreshScreen();
            int time = board.Timer();
            newHighestScore();
            if (!time) {
               gameon = false;
            }
         }
         if (!gameon) {
            Classifica();
            break;
         }
         napms(75);
      }
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

void SnakeGame::Classifica() {
   ofstream outputFile; /* Dichiarazione di tipo */
   outputFile.open("classifica.txt" , ios :: app ); /* Apertura del file */
   outputFile << this->score << endl;
   outputFile.close();
}


int SnakeGame::getScore() {
   return this->score;
}

int SnakeGame::getHighestScore() {
   return this->highestScore;
}

void SnakeGame::PauseGame() {
   isPaused = !isPaused;
   if (isPaused) {
      board.StopTimer();
   }else board.StartTimer();
}