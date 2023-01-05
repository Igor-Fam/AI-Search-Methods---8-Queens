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
    this->quantF = N * N;
    this->quantA = 0;
    this->quantQ = 0;
}

void Tabuleiro::adicionaRainha(int coluna){
    if(coluna < 0 || coluna > N-1){
        cout << "Posicao invalida!" << endl;
        return;
    }

    if(matriz[linha][coluna] != 'F'){
        cout << "Posicao indisponível!" << endl;
        return;
    }

    if(matriz[linha][coluna] != 'Q'){
        matriz[linha][coluna] = 'Q';
        quantQ += 1;
        quantF -= 1;
    }

    for (int i = linha; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if((i == linha || j == coluna || j - coluna == i - linha || j - coluna == linha - i) & (matriz[i][j] != 'A' & matriz[i][j] != 'Q')){
                matriz[i][j] = 'A';
                quantA += 1;
                quantF -= 1;
            }
        }
    }
    
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
    cout << "QuantF: " << quantF << endl;
    cout << "QuantA: " << quantA << endl;
    cout << "QuantQ: " << quantQ << endl;
    cout << "Total esperado: " << N * N << endl;
    cout << "Total da solucao: " << quantF + quantA + quantQ << endl;
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


void Tabuleiro::verificaColunaRainha(){
    for(int i = 0; i < N; i++){
        if(matriz[linha][i] == 'Q'){
            this->colunaRainha = i;
            break;
        }
    }
}

bool Tabuleiro::verificaImpasse(){
    for (int i = 0; i < N; i++){
        if(matriz[linha+1][i] == 'F'){
            return false;
        }
    }
    return true;
}