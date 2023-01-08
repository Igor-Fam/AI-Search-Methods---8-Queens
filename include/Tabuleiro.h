#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <vector>
#include <queue>

#define N 8

using namespace std;

class Tabuleiro
{
private:
    char matriz [N][N];
    int custoAcumulado [N] { 0 };
    int custoAcumuladoHeur [N] { 0 };
    int linha;
    int colunaRainha;
    int quantA, quantF, quantQ;

public:
    friend class No;
    Tabuleiro(int linha, bool r = false);
    // ~Tabuleiro();
    int getLinha(){ return linha; };
    void setLinha(int linha){ this->linha = linha; };
    void adicionaRainha(int coluna);
    bool verificaResolvido(){ return linha+1 == N; cout << "ue " << linha+1 << endl;};
    bool verificaImpasse();
    void imprimeTabuleiro(bool temHeuristica = false, bool aEstrela = false);
    void imprimeCustoAcumulado(bool temHeuristica, bool aEstrela);

    queue<int> verificaDisponiveis();
    vector<int> verificaDisponiveis1();

    void atualizaHeuristica();
    void verificaColunaRainha();

    int getQuantF() { return quantF; };
    int getQuantA() { return quantA; };
    int getQuantQ() { return quantQ; };

    int  somaCustoAcumulado(bool temHeuristica = false, bool aEstrela = false);

    void setCustoAcumulado(int* custoAntigo) {for(int i=0; i<N; i++) {custoAcumulado[i]=custoAntigo[i]; }; };
//    cout << " Setando " << endl;  printaCustoAcumulado();
    void setCustoAcumuladoHeur(int* custoAntigo) {for(int i=0; i<N; i++) {custoAcumuladoHeur[i]=custoAntigo[i]; }; };

    void atualizaCustoAcumulado(int custoNovo) {this->custoAcumulado[quantQ - 1] = custoNovo;};
//    cout << "Atualizando " << custoAcumulado[quantQ - 1] << endl; printaCustoAcumulado();
    void atualizaCustoAcumuladoHeur(int custoNovo) {this->custoAcumuladoHeur[quantQ - 1] = custoNovo;};

    int* getCustoAcumulado() {return custoAcumulado; };
    int* getCustoAcumuladoHeur() {return custoAcumuladoHeur; };
};

#endif