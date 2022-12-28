#include <iostream>
#include <vector>

#include "../include/No.h"
#include "../include/Tabuleiro.h"

using namespace std;

No::No(int linha, int coluna, bool heuristica, Tabuleiro* t){
    this->tabuleiro = new Tabuleiro(linha, heuristica);
    if(t != nullptr){
        this->tabuleiro->quantF = t->getQuantF();
        this->tabuleiro->quantA = t->getQuantA();
        this->tabuleiro->quantQ = t->getQuantQ();
        this->tabuleiro->setLinha(t->getLinha()+1);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                this->tabuleiro->matriz[i][j] = t->matriz[i][j];
    }

    if (coluna >= 0){
        this->calculaCusto(coluna);
        this->tabuleiro->adicionaRainha(coluna);
    }

    if(heuristica){
        this->h = this->tabuleiro->h;
    }
}

No::~No(){
    for (int i = 0; i < filhos.size(); i++)
        delete filhos[i];
}

bool No::visitaNo(int coluna){

    //verifica se e solucao
    if(this->tabuleiro->verificaResolvido()){
        cout << "Solucao encontrada: " << endl << endl;
        this->tabuleiro->imprimeTabuleiro();
        return true;
    }

    //gera filhos
    if(coluna == -1){ //nao e backtracking, gera todos os filhos
        vector<int> colunasFilhos = this->tabuleiro->verificaDisponiveis1();
        for (int i = 0; i < colunasFilhos.size(); i++)
        {
            filhos.push_back(new No(this->tabuleiro->getLinha(), colunasFilhos[i], this->h, this->tabuleiro));
        }
    }
    return false;
}

bool No::visitaNo(){
    //verifica se e solucao
    if(this->tabuleiro->verificaResolvido()){
        cout << "Solucao encontrada: " << endl << endl;
        this->tabuleiro->imprimeTabuleiro();
        return true;
    }

    //gera regras aplicaveis
    regras = this->tabuleiro->verificaDisponiveis();
    
    return false;
}

No* No::adicionaNo(int coluna){
    No* n = new No(this->tabuleiro->getLinha(), coluna, this->h, this->tabuleiro);
    filhos.push_back(n);

    return n;
}

void No::imprimeFilhos(){
    for (int i = 0; i < filhos.size(); i++)
    {
        cout << "Filho " << i << endl;
        filhos[i]->tabuleiro->imprimeTabuleiro();
    } 
}

int No::calculaHeuristica(){
    return this->tabuleiro->h;
}

void No::calculaCusto(int colunaAtual){
    this->tabuleiro->verificaColunaRainha();
    int colunaAnterior = this->tabuleiro->colunaRainha;
    this->custo = N - 1 - abs(colunaAnterior-colunaAtual);
}

/*

Custo do no atual = 
Q A A A A A A A
7 6 5 4 3 2 1 0

A Q A A A A A A
6 7 6 5 4 3 2 1

A A Q A A A A A
5 6 7 6 5 4 3 2

A A A Q A A A A
4 5 6 7 6 5 4 3

*/
