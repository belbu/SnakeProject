#include "SnakeGame.h"
#include "menu.h"
int main() {
    menu Menu;
    Menu.showMenu();

    // int mapHeight = 25;
    // int mapWidth = 45;
    // int snakeLength = 5;
    // SnakeGame game(mapHeight, mapWidth, snakeLength,1);
    // game.run();
    // return 0;
}



// int mapHeight = 25;
// int mapWidth = 45;
// int snakeLength = 5;
// SnakeGame game(mapHeight, mapWidth, snakeLength,1);
// game.run();
// return 0;

//      g++ main.cpp Snake.cpp menu.cpp Board.cpp SnakeGame.cpp Apple.cpp -lncurses -o Snake


//sistemare il menu: quit non funziona e visualizza classifica non fa vedere niente,
//fare in modo che finita una partita posso decidere se quittare il gioco o startarne un altra
//la seconda partita che faccio è buggata, il serpente si muove male
//scrivere i comandi da per muovere snake e per muoversi nel menu da qualche parte