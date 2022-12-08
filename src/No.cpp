#include <iostream>
#include <vector>

#include "../include/No.h"
#include "../include/Tabuleiro.h"

using namespace std;

No::No(int linha, int coluna, bool heuristica, Tabuleiro* t){
    this->tabuleiro = new Tabuleiro(linha, heuristica);
    if(t != nullptr){
        this->tabuleiro->setLinha(t->getLinha()+1);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                this->tabuleiro->matriz[i][j] = t->matriz[i][j];
    }


    if (coluna >= 0){
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