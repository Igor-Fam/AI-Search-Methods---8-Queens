#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "vector"

using namespace std;

class Tabuleiro
{
private:
    int matriz [8][8];
    int proxLinha;
    bool ignorarRestricoes;
    int h;
public:
    friend class No;
    Tabuleiro(bool r = false);
    ~Tabuleiro(){ delete [] matriz; }
    void adicionaRainha(int coluna);
    bool verificaResolvido(){ return proxLinha == 8; };
    bool verificaImpasse();
    void imprimeTabuleiro();
    vector<int> verificaDisponiveis();
};













#endif