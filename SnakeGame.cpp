
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
   this->speed = level;
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
      this -> score ++ ;
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

   int currentDirection = KEY_RIGHT;
   int pendingDirection = KEY_RIGHT;

   int tickCount = 0;
   const int TICKS_PER_MOVE = 8; //TODO MODIFICA QUESTO PER CAMBIARE VELOCITA (PIU GRANDE = PIU LENTO)

   nodelay(stdscr, TRUE);
   timeout(0);

   while (gameon) {
      int ch = getch();
      if (ch != ERR) {
         if (ch == ' ') {
            PauseGame();
         } else if (ch == 'q') {
            this->gameon = false;
            newHighestScore();
            Classifica();
            break;
         } else if (!isPaused &&
                    (ch == KEY_UP || ch == KEY_DOWN || ch == KEY_LEFT || ch == KEY_RIGHT)) {
            // Verifica che la nuova direzione NON sia opposta a quella corrente
            if (!(currentDirection == KEY_UP && ch == KEY_DOWN) &&
                !(currentDirection == KEY_DOWN && ch == KEY_UP) &&
                !(currentDirection == KEY_LEFT && ch == KEY_RIGHT) &&
                !(currentDirection == KEY_RIGHT && ch == KEY_LEFT)) {
               pendingDirection = ch;
                }
                    }
      }

      if (!isPaused) {
         if (tickCount >= TICKS_PER_MOVE) {
            // Applica la nuova direzione valida
            currentDirection = pendingDirection;
            snake.ChangeDirection(currentDirection);
            gameon = snake.Move();

            if (!gameon) {
               ScoreMultiplier();
               newHighestScore();
               Classifica();
               break;
            }

            CheckAppleCollision();
            board.printLevel();
            board.score(score);
            board.printHighestScore(highestScore);
            board.drawBorder();
            snake.Draw();
            apple.drawApple();
            board.refreshScreen();

            if (!board.Timer()) {
               gameon = false;
               break;
            }

            newHighestScore();
            tickCount = 0;
         }

         napms(10/speed);
         tickCount++;
      } else {
         napms(50/speed);
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
   ofstream outputFile;
   outputFile.open("classifica.txt", ios::app);
   outputFile << this->level << " " << this->score << endl;
   outputFile.close();
}

int SnakeGame::getScore() {
   return this->score;
}

int SnakeGame::getHighestScore() {
   return this->highestScore;
}

void SnakeGame::PauseGame() {
   isPaused = true;
   board.StopTimer();

   int centerY = board.getStartY() + (board.getHeight() / 2);
   int centerX = board.getStartX() + (board.getWidth() / 2) - 5;

   while (isPaused) {
      mvprintw(centerY, centerX, "   PAUSA   ");
      mvprintw(centerY + 1, centerX - 10, "Premi [1-6] per cambiare livello");
      mvprintw(centerY + 2, centerX - 10, "Spazio per continuare, q per uscire");
      refresh();

      int ch = getch();
      if (ch >= '1' && ch <= '6') {
         int newLevel = ch - '0';
         if (newLevel != this->level) {
            this->speed = newLevel;
            this->level = newLevel;
            mvprintw(centerY + 3, centerX - 10, "Velocità cambiata a %d", this->speed);
            this->score = 0;
            board.ResetTimer();
            refresh();
            napms(700);
         }
         isPaused = false;
      } else if (ch == ' ') {
         isPaused = false;
      } else if (ch == 'q') {
         this->gameon = false;
         newHighestScore();  // Aggiorna eventuale record
         Classifica();       // Salva la partita nella classifica
         break;              // Esci immediatamente dal menu di pausa
      }
      board.setLevel(this->level);
   }

   if (this->gameon) {  // Se non abbiamo deciso di uscire
      board.StartTimer();
   }
}

void SnakeGame::ScoreMultiplier() {
   this->score = this->score * speed ;
}
