#include "SnakeGame.h"
#include "menu.h"
int main() {
    // menu Menu;
    // Menu.showMenu();

    int mapHeight = 25;
    int mapWidth = 45;
    int snakeLength = 5;
    SnakeGame game(mapHeight, mapWidth, snakeLength,1);
    game.run();
    return 0;
}



// int mapHeight = 25;
// int mapWidth = 45;
// int snakeLength = 5;
// SnakeGame game(mapHeight, mapWidth, snakeLength,1);
// game.run();
// return 0;

//      g++ main.cpp Snake.cpp menu.cpp Board.cpp SnakeGame.cpp Apple.cpp -lncurses -o Snake