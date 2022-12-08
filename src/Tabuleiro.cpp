#include <iostream>
#include <vector>

#include "../include/Tabuleiro.h"

using namespace std;

Tabuleiro::Tabuleiro(int linha, bool r){
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            this->matriz[i][j] = 'F';
        }
    }
    this->linha = linha;
    this->ignorarRestricoes = r;
}

void Tabuleiro::adicionaRainha(int coluna){
    if(coluna < 0 || coluna > N-1){
        cout << "Posicao invalida!" << endl;
        return;
    }

    if(matriz[linha][coluna] != 'F'){
        if(this->ignorarRestricoes){
            this->h = this->h+2;
        } else {
            cout << "Posicao indisponivel!" << endl;
            return;
        }
    }

    for (int i = linha; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if(i == linha || j == coluna || j - coluna == i - linha || j - coluna == linha - i){
                matriz[i][j] = 'A';
            }
        }
    }
    
    matriz[linha][coluna] = 'Q';
}

void Tabuleiro::imprimeTabuleiro(){
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

queue<int> Tabuleiro::verificaDisponiveis(){
    queue<int> disponiveis;
    
    for (int i = 0; i < N; i++)
    {
        if(matriz[linha+1][i] == 'F'){
            disponiveis.push(i);
        }
    }
    
    return disponiveis;
}

vector<int> Tabuleiro::verificaDisponiveis1(){
    vector<int> disponiveis;
    
    for (int i = 0; i < N; i++)
    {
        if(matriz[linha+1][i] == 'F'){
            disponiveis.push_back(i);
        }
    }
    
    return disponiveis;
}

bool Tabuleiro::verificaImpasse(){
    for (int i = 0; i < N; i++){
        if(matriz[linha+1][i] == 'F'){
            return false;
        }
    }
    return true;
}