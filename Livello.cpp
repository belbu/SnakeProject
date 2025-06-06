#include "Livello.h"
#include <iostream>

ListaLivelli::ListaLivelli() : head(nullptr), tail(nullptr) {
    // Livelli predefiniti
    aggiungiLivello(1, "Facilissimo");
    aggiungiLivello(2, "Facile");
    aggiungiLivello(3, "Medio");
    aggiungiLivello(4, "Difficile");
    aggiungiLivello(5, "Molto Difficile");
    aggiungiLivello(6, "Estremo");

}

ListaLivelli::~ListaLivelli() {
    NodoLivello* current = head;
    while (current) {
        NodoLivello* temp = current;
        current = current->next;
        delete temp;
    }
}

void ListaLivelli::aggiungiLivello(int numero, const std::string& descrizione) {
    NodoLivello* nuovo = new NodoLivello{numero, descrizione, nullptr, nullptr};
    if (!head) {
        head = tail = nuovo;
    } else {
        tail->next = nuovo;
        nuovo->prev = tail;
        tail = nuovo;
    }
}

NodoLivello* ListaLivelli::getLivello(int numero) {
    NodoLivello* current = head;
    while (current) {
        if (current->numero == numero)
            return current;
        current = current->next;
    }
    return nullptr;
}

void ListaLivelli::stampaLivelli() {
    NodoLivello* current = head;
    while (current) {
        std::cout << current->numero << " - " << current->descrizione << std::endl;
        current = current->next;
    }
}
NodoLivello* ListaLivelli::getLivelloVicino(NodoLivello* start, int targetNumero) {
    if (!start) return nullptr;

    if (start->numero == targetNumero) return start;

    NodoLivello* current = start;

    if (targetNumero > start->numero) {
        // Scorri avanti
        while (current && current->numero < targetNumero) {
            current = current->next;
        }
        if (current && current->numero == targetNumero) return current;
    } else {
        // Scorri indietro
        while (current && current->numero > targetNumero) {
            current = current->prev;
        }
        if (current && current->numero == targetNumero) return current;
    }

    return nullptr;
}