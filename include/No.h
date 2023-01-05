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
    int nivel;
    int Id;
    int custo;
    int custoHeur = 1000; //heuristica
    int custoStar = 1000;

protected:
    Tabuleiro* tabuleiro;

public:
    //coluna a inserir rainha, heuristica ou não, estado anterior (se houver)
    No(int linha, int coluna, bool heuristica, Tabuleiro* t = nullptr);
    ~No();
    bool visitaNo(); //se passar coluna, gera apenas um filho (backtracking)
    bool visitaNo(int coluna,  bool temHeuristica = false);
    No* adicionaNo(int coluna,  bool temHeuristica = false);
    void imprimeFilhos();
    void imprimeTabuleiro(){tabuleiro->imprimeTabuleiro();};
    vector<No*> getFilhos(){ return filhos; };

    queue<int> getRegras(){ return regras; };
    Tabuleiro* getTabuleiro(){ return tabuleiro; };
    int getNivel() {return nivel;};
    void setNivel(int nivel) {this->nivel = nivel;};
    int getId() {return Id;};
    void setId(int id) {this->Id = id;};
    void calculaHeuristica();
    void calculaCusto(int coluna);
    void calculaCustoEstrela();

};

#endif