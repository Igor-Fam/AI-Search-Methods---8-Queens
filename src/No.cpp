#include <iostream>
#include <vector>

#include "../include/No.h"
#include "../include/Tabuleiro.h"

using namespace std;

No::No(int linha, int coluna, bool heuristica, Tabuleiro* t){
    //Desnecessário fazer posicionamento ignorando as restrições, apenas a heuristica precisa levar isso em conta pro seu cálculo, como não posicionamos em uma, o fator 10*(8-rainhasPoscionadas) garante que o custo vai ser mais alto que resto (se 10 for muito alto, diminuir)
    this->tabuleiro = new Tabuleiro(linha);
    if(t != nullptr){
        this->tabuleiro->quantF = t->getQuantF();
        this->tabuleiro->quantA = t->getQuantA();
        this->tabuleiro->quantQ = t->getQuantQ();
        this->tabuleiro->setLinha(t->getLinha()+1);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                this->tabuleiro->matriz[i][j] = t->matriz[i][j];
    }

    //ideal: obter custo e custoHeur com apenas uma passagem pela matriz pra n ter de criar 2x cada filho na busca A*
    if (coluna >= 0){
        this->calculaCusto(coluna);
        this->tabuleiro->adicionaRainha(coluna);
        //Heuristica só é calculada depois do posicionamento da rainha nas colunas possíveis, pois teria de verificar os custosHeur de todos os filhos de qualquer maneira pra ordenar eles.
        //E além disso elimina a necessidade de verificar posição inválida
        if(heuristica){
            this->calculaHeuristica();
        }
        /*if(aEstrela){
            this->calculaCustoEstrela() ;
        }*/
    }

}

No::~No(){
    for (int i = 0; i < filhos.size(); i++)
        delete filhos[i];
}

bool No::visitaNo(int coluna, bool temHeuristica){

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
            filhos.push_back(new No(this->tabuleiro->getLinha(), colunasFilhos[i], temHeuristica, this->tabuleiro));
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

No* No::adicionaNo(int coluna, bool temHeuristica){
    No* n = new No(this->tabuleiro->getLinha(), coluna, temHeuristica, this->tabuleiro);
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

void No::calculaHeuristica(){
    int casasVazias = this->tabuleiro->getQuantF();
    int casasAtacadas = this->tabuleiro->getQuantA();
    int rainhasPosicionadas = this->tabuleiro->getQuantQ();
    this->custoHeur = casasVazias + casasVazias*casasAtacadas + 10*(8 - rainhasPosicionadas);
}

void No::calculaCusto(int colunaAtual){
    this->tabuleiro->verificaColunaRainha();
    int colunaAnterior = this->tabuleiro->colunaRainha;
    this->custo = N - 1 - abs(colunaAnterior-colunaAtual);
}

void No::calculaCustoEstrela(){
    this->custoStar = this->custo + this->custoHeur;
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