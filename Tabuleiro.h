#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "vector"

#define N 8

using namespace std;

class Tabuleiro
{
private:
    char matriz [N][N];
    int proxLinha;
    bool ignorarRestricoes;
    int h;
public:
    friend class No;
    Tabuleiro(bool r = false);
    ~Tabuleiro();
    void adicionaRainha(int coluna);
    bool verificaResolvido(){ return proxLinha == N; };
    bool verificaImpasse();
    void imprimeTabuleiro();
    vector<int> verificaDisponiveis();
};













#endif