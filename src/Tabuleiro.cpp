#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>

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

void Tabuleiro::imprimeTabuleiro(bool temHeuristica, bool aEstrela){
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
    imprimeCustoAcumulado(temHeuristica, aEstrela);
}

int Tabuleiro::somaCustoAcumulado(bool temHeuristica, bool aEstrela){
    int soma = 0;
    if(aEstrela){
        soma = custoAcumuladoHeur[N-1];
        //cout << "soma inicial: " << soma << endl;
    }
    return accumulate(std::begin(custoAcumulado) , std::end(custoAcumulado), soma);
}

void Tabuleiro::imprimeCustoAcumulado(bool temHeuristica, bool aEstrela){
    cout << endl;
    cout << "Custo Total da Solução: " << endl;
    if(!aEstrela && !temHeuristica){
        for (int i = 0; i < N; i++) {
            if(i == 0){
                cout << "(";
            }

            cout << custoAcumulado[i];

            if(i != N-1){
                cout << ", ";
            }
            else{
                cout << ")";
            }
        }
    }
    else {
        cout << "Custos Normais da Solução: " << endl;
        for (int i = 0; i < N; i++) {
            if(i == 0){
                cout << "(";
            }
            cout << custoAcumulado[i];
            if(i != N-1){
                cout << ", ";
            }
            else{
                cout << ")";
            }
        }
        cout << endl << "Custos Heuristicas da Solução: " << endl;
        for (int j = 0; j < N; j++) {
            if(j == 0){
                cout << "(";
            }
            cout << custoAcumuladoHeur[j];
            if(j != N-1){
                cout << ", ";
            }
            else{
                cout << ")";
            }
        }
    }
    cout << endl << "Somado: " << somaCustoAcumulado(temHeuristica, aEstrela) << endl;
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
    bool temRainha = false;
    for(int i = 0; i < N; i++){
        if(matriz[linha][i] == 'Q'){
            this->colunaRainha = i;
            temRainha = true;
            break;
        }
    }
    if (!temRainha)
        this->colunaRainha = 0;
}

bool Tabuleiro::verificaImpasse(){
    for (int i = 0; i < N; i++){
        if(matriz[linha+1][i] == 'F'){
            return false;
        }
    }
    return true;
}