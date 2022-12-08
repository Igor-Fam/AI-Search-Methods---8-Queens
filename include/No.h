#ifndef NO_H
#define NO_H

#include "Tabuleiro.h"
#include <vector>
#include <queue>

class No
{
private:

    vector<No*> filhos;
    queue<int> regras;
    int h = 0; //heuristica
    int nivel;
    int Id;

protected:
    Tabuleiro* tabuleiro;

public:
    //coluna a inserir rainha, heuristica ou não, estado anterior (se houver)
    No(int linha, int coluna, bool heuristica, Tabuleiro* t = nullptr);
    ~No();
    bool visitaNo(); //se passar coluna, gera apenas um filho (backtracking)
    bool visitaNo(int coluna);
    No* adicionaNo(int coluna);
    void imprimeFilhos();
    void imprimeTabuleiro(){tabuleiro->imprimeTabuleiro();};
    vector<No*> getFilhos(){ return filhos; };

    queue<int> getRegras(){ return regras; };
    Tabuleiro* getTabuleiro(){ return tabuleiro; };
    int getNivel() {return nivel;};
    void setNivel(int nivel) {this->nivel = nivel;};
    int getId() {return Id;};
    void setId(int id) {this->Id = id;};

};

#endif