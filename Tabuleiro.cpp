#include "Tabuleiro.h"
#include "iostream"
#include "vector"

using namespace std;

Tabuleiro::Tabuleiro(bool r){
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            this->matriz[i][j] = 'F';
        }
    }
    this->proxLinha = 0;
    this->ignorarRestricoes = r;
}

void Tabuleiro::adicionaRainha(int coluna){
    if(coluna < 0 || coluna > N-1){
        cout << "Posicao invalida!";
        return;
    }

    if(matriz[proxLinha][coluna] != 'F'){
        if(this->ignorarRestricoes){
            this->h = this->h+2;
        } else {
            cout << "Posicao indisponivel!";
            return;
        }
    }

    for (int i = proxLinha; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if(i == proxLinha || j == coluna || j - coluna == i - proxLinha || j - coluna == proxLinha - i){
                matriz[i][j] = 'Q';
            }
        }
    }
    
    matriz[proxLinha][coluna] = 'A';
    proxLinha = proxLinha + 1;
}

void Tabuleiro::imprimeTabuleiro(){
    cout << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

vector<int> Tabuleiro::verificaDisponiveis(){
    vector<int> disponiveis;
    
    for (int i = 0; i < N; i++)
    {
        if(matriz[proxLinha][i] == 'F'){
            disponiveis.push_back(i);
        }
    }
    
    return disponiveis;
}

bool Tabuleiro::verificaImpasse(){
    for (int i = 0; i < N; i++){
        if(matriz[proxLinha][i] == 'F'){
            return false;
        }
    }
    return true;
}