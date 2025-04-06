#include <curses.h>
#include "menu.h"
#include "SnakeGame.h"
#include <iostream>
#include <fstream>
using namespace std;

menu::menu() : game(nullptr) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

}

menu::~menu() {
    if (game) delete game;
    endwin();
}

void menu::initScreen() {
    endwin(); // Chiude qualsiasi finestra esistente
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    refresh();
}

void menu::startGame() {
    bool playAgain = true;

    while (playAgain) {
        clear();
        printw("----- NEW GAME -----\n");
        printw("Press any key to start...");
        refresh();
        nodelay(stdscr, FALSE);
        getch();
        clear();

        if (game) {
            delete game;
            game = nullptr;
        }

        game = new SnakeGame(20, 40, 7, 1);
        game->run();

        initScreen();
        clear();
        printw("----- GAME OVER -----\n");
        printw("Your score: %d\n\n", game->getScore());
        printw("1. Play Again\n");
        printw("2. Return to Menu\n");
        printw("3. Quit Game\n");
        printw("Choose an option: ");
        refresh();

        int choice;
        do {
            choice = getch();
        } while (choice < '1' || choice > '3');

        switch (choice) {
            case '1': continue;
            case '2': playAgain = false; break;
            case '3': playAgain = false; HighScoreLoaded(); exit(EXIT_SUCCESS); break;
        }
    }
    showMenu();
}

void menu::showMenu() {
    initScreen();

    bool show = true;
    while (show) {
        clear();
        printw("----- SNAKE MENU -----\n");
        printw("1 Start game\n");
        printw("2 See ranking\n");
        printw("3 Quit\n");
        printw("Choose an option\n");
        refresh();

        int choice = getch();
        if (choice >= '1' && choice <= '3') {
            int user_input = choice - '0';
            if (user_input == 1) {
                startGame();
                return;
            }
            else if (user_input == 2) {
                showClassifica();
                break;
            }
            else if (user_input == 3) {
                show = false;
                HighScoreLoaded();
            }
            else {
                printw("\nPress a valid key...\n");
                getch();
            }
        }
    }
}

void menu::showClassifica() {
    initScreen();
    clear();

    std::ifstream file("classifica.txt");
    std::vector<std::pair<int, int>> punteggi_con_partita;

    int punteggio;
    int numero_partita = 1;

    while (file >> punteggio) {
        punteggi_con_partita.push_back({punteggio, numero_partita});
        numero_partita++;
    }

    file.close();

    if (punteggi_con_partita.empty()) {
        printw("Nessun punteggio disponibile.\n");
    } else {
        // Ordina in base al punteggio, decrescente
        std::sort(punteggi_con_partita.begin(), punteggi_con_partita.end(),
                  [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                      return a.first > b.first;
                  });

        printw("----- CLASSIFICA -----\n\n");
        for (size_t i = 0; i < punteggi_con_partita.size(); ++i) {
            printw("Partita n.%d: %d punti\n", punteggi_con_partita[i].second, punteggi_con_partita[i].first);
        }
    }

    printw("\nPremi un tasto per tornare al menu...");
    refresh();
    nodelay(stdscr, FALSE);
    getch();
    showMenu();
}

void menu::HighScoreLoaded() {
    int highestScore = game->getHighestScore();
    std::cout << "Highscore caricato: " << highestScore << std::endl;
}
