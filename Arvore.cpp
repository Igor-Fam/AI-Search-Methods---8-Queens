#include <iostream>
#include <vector>

#include "Arvore.h"

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
    cin >> busca;

    while (busca < 1 || busca > 2)
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
    }
}
