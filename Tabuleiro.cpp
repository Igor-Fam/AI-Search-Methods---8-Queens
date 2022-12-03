#include "Tabuleiro.h"
#include "iostream"
#include "vector"

using namespace std;

Tabuleiro::Tabuleiro(bool r){
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            this->matriz[i][j] = 0;
        }
    }
    this->proxLinha = 0;
    this->ignorarRestricoes = r;
}

void Tabuleiro::adicionaRainha(int coluna){
    if(coluna < 0 || coluna > 7){
        cout << "Posicao invalida!";
        return;
    }

    if(matriz[proxLinha][coluna] != 0){
        if(this->ignorarRestricoes){
            this->h = this->h+2;
        } else {
            cout << "Posicao indisponivel!";
            return;
        }
    }

    for (int i = proxLinha; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(i == proxLinha || j == coluna || j - coluna == i - proxLinha || j - coluna == proxLinha - i){
                matriz[i][j] = 2;
            }
        }
    }
    
    matriz[proxLinha][coluna] = 1;
    proxLinha = proxLinha + 1;
}

void Tabuleiro::imprimeTabuleiro(){
    cout << endl;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

vector<int> Tabuleiro::verificaDisponiveis(){
    vector<int> disponiveis;
    
    for (int i = 0; i < 8; i++)
    {
        if(matriz[proxLinha][i] == 0){
            disponiveis.push_back(i);
        }
    }
    
    return disponiveis;
}

bool Tabuleiro::verificaImpasse(){
    for (int i = 0; i < 8; i++){
        if(matriz[proxLinha][i] == 0){
            return false;
        }
    }
    return true;
}