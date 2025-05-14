#include <curses.h>
#include <iostream>
#include <fstream>
#include "menu.h"
#include "SnakeGame.h"
#include "Livello.h"

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
    endwin();
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    refresh();
}

void menu::startGame() {
    bool playAgain = true;
    ListaLivelli listaLivelli;

    while (playAgain) {
        clear();
        printw("----- SELEZIONE LIVELLO -----\n");
        printw("Scegli un livello:\n");

        // Stampa i livelli sulla console
        NodoLivello* temp = listaLivelli.getLivello(1);
        while (temp) {
            printw("%d - %s\n", temp->numero, temp->descrizione.c_str());
            temp = temp->next;
        }

        printw("Inserisci il numero del livello (1-4): ");
        refresh();

        int livello = 1;
        do {
            livello = getch() - '0';  // Converte il carattere in un numero
        } while (livello < 1 || livello > 4);  // Assicura che il livello sia valido (da 1 a 4)

        NodoLivello* livelloScelto = listaLivelli.getLivello(livello);
        if (!livelloScelto) {
            printw("Livello non valido. Riprova.\n");
            refresh();
            getch();  // Attende un tasto per continuare
            continue;
        }

        clear();
        printw("Hai scelto il livello: %s\n", livelloScelto->descrizione.c_str());
        printw("Premi un tasto per iniziare...\n");
        refresh();
        getch();  // Attende un tasto per iniziare
        clear();

        if (game) {
            delete game;
            game = nullptr;
        }


        int speed = livelloScelto->numero; // Oppure 7 - livelloScelto->numero
        if (speed < 1) speed = 1;
        game = new SnakeGame(20, 40, 15, speed);
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
        } while (choice < '1' || choice > '3');  // Accetta solo le opzioni valide

        switch (choice) {
            case '1': continue;  // Se si sceglie '1', si continua a giocare
            case '2': playAgain = false; break;  // Se si sceglie '2', si esce dal ciclo di gioco
            case '3': playAgain = false; HighScoreLoaded(); exit(EXIT_SUCCESS); break;  // Se si sceglie '3', si esce dal gioco
        }
    }

    showMenu();  // Torna al menu principale
}

void menu::showMenu() {
    initScreen();

    bool show = true;
    while (show) {
        clear();
        artwork();
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
            } else if (user_input == 2) {
                showClassifica();
                break;
            } else if (user_input == 3) {
                show = false;
                HighScoreLoaded();
            }
        } else {
            printw("\nPress a valid key...\n");
            getch();
        }
    }
}

void menu::showClassifica() {
    initScreen();
    clear();

    std::ifstream file("classifica.txt");
    int livelli[100];
    int punteggi[100];
    int partite[100];
    int count = 0;

    int livello, punteggio;
    int numero_partita = 1;

    while (file >> livello >> punteggio && count < 100) {
        livelli[count] = livello;
        punteggi[count] = punteggio;
        partite[count] = numero_partita++;
        count++;
    }

    file.close();

    // Ordina i punteggi in modo decrescente (bubble sort)
    for (int i = 0; i < count - 1; ++i) {
        for (int j = i + 1; j < count; ++j) {
            if (punteggi[i] < punteggi[j]) {
                std::swap(punteggi[i], punteggi[j]);
                std::swap(partite[i], partite[j]);
                std::swap(livelli[i], livelli[j]);  // Aggiunto anche lo swap dei livelli!
            }
        }
    }

    if (count == 0) {
        printw("Nessun punteggio disponibile.\n");
    } else {
        printw("----- CLASSIFICA -----\n\n");
        for (int i = 0; i < count; ++i) {
            printw("Partita n.%d, Livello %d, %d punti\n", partite[i], livelli[i], punteggi[i]);
        }
    }

    printw("\nPremi un tasto per tornare al menu...");
    refresh();
    nodelay(stdscr, FALSE);
    getch();
    showMenu();
}


void menu::HighScoreLoaded() {
    if (game) {
        int highestScore = game->getHighestScore();
        std::cout << "Highscore caricato: " << highestScore << std::endl;
    }
}

void menu::artwork() {
    printw(R"(
  ____  _   _    _    _  __ _____
 / ___|| \ | |  / \  | |/ /| ____|
 \___ \|  \| | / _ \ | ' / |  _|
  ___) | |\  |/ ___ \| . \ | |___
 |____/|_| \_/_/   \_\_|\_\|_____|

        === MAIN MENU ===
)");

}
