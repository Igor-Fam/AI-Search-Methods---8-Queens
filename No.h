#ifndef NO_H
#define NO_H

#include "Tabuleiro.h"
#include "vector"

class No
{
private:
    vector<No*> filhos;
    int h = 0; //heuristica

protected:
    Tabuleiro* tabuleiro;

public:
    //coluna a inserir rainha, heuristica ou não, estado anterior (se houver)
    No(int coluna, bool heuristica, Tabuleiro* t = nullptr); 
    ~No();
    bool visitaNo(int coluna = -1); //se passar coluna, gera apenas um filho (backtracking)
    void imprimeFilhos();
    void imprimeTabuleiro(){tabuleiro->imprimeTabuleiro();};
};




#endif