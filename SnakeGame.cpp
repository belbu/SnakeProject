
#include "SnakeGame.h"
#include "Board.h"
#include "Snake.h"
#include "Apple.h"
#include "Livello.h"
#include <iostream>
#include <fstream>
#include <ctime>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;
bool Bonus = false;

SnakeGame::SnakeGame(int mapHeight, int mapWidth, int snakeLength, int level) : board(mapHeight,mapWidth),
   snake(board.getScreenRows(), board.getScreenCols(), snakeLength, board.getWindow()),
   apple(board.getWindow(),board.getScreenRows(),board.getScreenCols()){
   Bonus = false;
   this->gameon = true;
   this->score = 0;
   this->speed = level;
   this->level = level;
   this->isPaused = false;
   std::ifstream file("punteggio.txt");
   if (file) {  // Se il file esiste ed è leggibile legge l highestScore
      file >> this->highestScore;
      if (file.fail()) { // Se la lettura non è andata a buon fine imposta un valore di default
         this->highestScore = 0;
      }
   } else {
      this->highestScore = 0;  // Se il file non esiste, imposta 0
   }

   file.close();
}

void SnakeGame::CheckAppleCollision() {
   coordinates head = snake.get_head();
   if (head.row == apple.GetPosition().row && head.col == apple.GetPosition().col) {
      NewApplePosition();
      this -> score = score + 1;
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
   NewApplePosition();

   int input = KEY_RIGHT;

   int tickCount = 0;

   nodelay(stdscr, TRUE);
   timeout(0);

   while (gameon) {
      int TICKS_PER_MOVE = 8 - speed;
      int ch = getch();
      if (ch != ERR) {
         if (ch == ' ') {
            PauseGame();
         } else if (ch == 'q') {
            this->gameon = false;
            newHighestScore();
            Classifica();
            break;
         } else if (!isPaused && (ch == KEY_UP || ch == KEY_DOWN || ch == KEY_LEFT || ch == KEY_RIGHT)) {
            if (snake.CanChangeDirection(ch)) input = ch;
         }
      }

      if (!isPaused) {
         if (tickCount >= TICKS_PER_MOVE) {
            snake.setDiredction(input);
            gameon = snake.Move();

            if (!gameon) {
               scoreMultiplier();
               newHighestScore();
               Classifica();
               break;
            }

            CheckAppleCollision();
            board.printAll(this->score,this->highestScore,this->level);
            snake.Draw();
            apple.drawApple();
            board.refreshScreen();

            if (!board.Timer()) {
               gameon = false;
               scoreMultiplier();
               newHighestScore();
               Classifica();
               break;
            }
            tickCount = 0;
         }
         napms(50/speed); //10
         tickCount++;
      } else {
         napms(100/speed); //50
      }
   }
}


void SnakeGame::newHighestScore() {
   if (this->score > this->highestScore) {
      this->highestScore = this->score;
      ofstream outputFile;  // salvataggio su file
      outputFile.open("punteggio.txt");
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
            // Usa la lista livelli per muoverti avanti/indietro
            // esempio: cerca il livello partendo da current level
            NodoLivello* currentNodo = listaLivelli.getLivello(this->level);
            NodoLivello* targetNodo = nullptr;

            if (newLevel > this->level) {
               // cerca avanti
               NodoLivello* temp = currentNodo;
               while(temp && temp->numero < newLevel) temp = temp->next;
               targetNodo = temp;
            } else if (newLevel < this->level) {
               // cerca indietro
               NodoLivello* temp = currentNodo;
               while(temp && temp->numero > newLevel) temp = temp->prev;
               targetNodo = temp;
            }

            if (targetNodo) {
               this->speed = targetNodo->numero;
               this->level = targetNodo->numero;
               mvprintw(centerY + 3, centerX - 10, "Velocità cambiata a %d", this->speed);
               this->score = 0;
               board.ResetTimer();
               refresh();
               napms(700);
            }
         }
         isPaused = false;
      } else if (ch == ' ') {
         isPaused = false;
      } else if (ch == 'q') {
         this->gameon = false;
         newHighestScore();
         Classifica();
         break;
      }
   }
   if (this->gameon) {
      board.StartTimer();
   }
}
void SnakeGame::scoreMultiplier() {
   this -> score = score * this -> level ;
   Bonus = true ;
   //ciao
}

void SnakeGame::resetScore() {
   this->score = 0;
}

void SnakeGame::setLevel(int newLevel) {
   this->level = newLevel;
}

void SnakeGame::setSpeed(int newSpeed) {
   this->speed = newSpeed;
}

void SnakeGame::stopGame() {
   this->gameon = false;
}

int SnakeGame::getLevel() const { //getter per poter leggere il livello corrente nonostante le modifiche
   return this->level;
}
