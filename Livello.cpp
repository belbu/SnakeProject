#include "Livello.h"
#include <iostream>

ListaLivelli::ListaLivelli() : head(nullptr), tail(nullptr) {
    // Livelli predefiniti
    aggiungiLivello(1, "Facile - Partenza tranquilla");
    aggiungiLivello(2, "Medio - Un po' più veloce");
    aggiungiLivello(3, "Difficile - Sfida intensa");
    aggiungiLivello(4, "Estremo - Solo per esperti");
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
