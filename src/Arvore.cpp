#include <iostream>
#include <vector>

#include "../include/Arvore.h"

using namespace std;

Arvore::Arvore(bool heuristica){
    this->heuristica = heuristica;
    raiz = nullptr;
}

void Arvore::resetarArvore(){
    delete raiz;
    setarArvore();
}

void Arvore::setarArvore(){
    if (raiz == nullptr){
        raiz = new No(0, 0, heuristica);
    }
}

void Arvore::iniciarBusca(){
    if (raiz != nullptr){
        char escolha = 'N';
        cout << "A árvore já tem nó raiz! Você deseja resetá-la e iniciar uma nova busca? [S/n]" << endl;
        cin >> escolha;

        if (escolha == 'S' || escolha == 's')
            resetarArvore();
    }

    int busca;
    cout << "Escolha a busca: " << endl;
    cout << "1 - Backtracking" << endl;
    cout << "2 - Busca em largura" << endl;
    cout << "3 - Busca em profundidade" << endl;
    cin >> busca;

    while (busca < 1 || busca > 3)
    {
        cout << "Opçao invalida! Escolha outra opcao" << endl;
        cin >> busca;
    }

    setarArvore();
    
    switch (busca)
    {
    case 1:
        // backtracking();
        break;
    case 2:
        // buscaLargura();
        break;
    case 3:
        // buscaProfundidade();
        break;
    }
}

void Arvore::buscaProfundidade(){
    if (raiz == nullptr){
        cout << "A arvore esta vazia!" << endl;
        return;
    }

    if(!auxProfundidade(raiz)){
        cout << "Solucao nao encontrada!" << endl;
    }
}

bool Arvore::auxProfundidade(No* n){
    if(n->visitaNo()){
        return true;
    }

    vector<No*> filhos = n->getFilhos();

    for (int i = filhos.size() - 1; i >= 0; i--){
        No* f = filhos[i];
        if(auxProfundidade(f)){
            return true;
        }
    }

    return false;
}
