#ifndef LIVELLO_H
#define LIVELLO_H

#include <string>

struct NodoLivello {
    int numero;
    std::string descrizione;
    NodoLivello* prev;
    NodoLivello* next;
};

class ListaLivelli {
public:
    ListaLivelli();
    ~ListaLivelli();
    void aggiungiLivello(int numero, const std::string& descrizione);
    NodoLivello* getLivello(int numero);
    void stampaLivelli();

private:
    NodoLivello* head;
    NodoLivello* tail;
};

#endif // LIVELLO_H
