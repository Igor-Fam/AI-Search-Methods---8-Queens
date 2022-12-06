#include "No.h"
#include "Tabuleiro.h"
#include "iostream"
#include "vector"

using namespace std;

No::No(int coluna, bool heuristica, Tabuleiro* t){

    if(t != nullptr){
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                this->tabuleiro->matriz[i][j] = t->matriz[i][j];
    } else {
        this->tabuleiro = new Tabuleiro(heuristica);
    }

    this->tabuleiro->adicionaRainha(coluna);

    if(heuristica){
        this->h = this->tabuleiro->h;
    }
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
        vector<int> colunasFilhos = this->tabuleiro->verificaDisponiveis();

        for (int i = 0; i < colunasFilhos.size(); i++)
        {
            cout << colunasFilhos[i] << " - ";
            filhos[i] = new No(colunasFilhos[i], this->h, this->tabuleiro);
        }
    }
}

void No::imprimeFilhos(){
    for (int i = 0; i < sizeof(filhos)/sizeof(No); i++)
    {
        filhos[i]->tabuleiro->imprimeTabuleiro();
    }
    
}