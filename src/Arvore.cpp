#include <iostream>
#include <vector>

#include "../include/Arvore.h"
#include "../include/No.h"

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
        raiz = new No(-1, -1, heuristica);
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
        buscaProfundidade();
        break;
    }
}

void Arvore::buscaProfundidade(){
    if (raiz == nullptr){
        cout << "A arvore esta vazia!" << endl;
        return;
    }

    PilhaEncad *abertos = new PilhaEncad();
    NoFP *n = new NoFP(raiz);
    abertos->empilha(n);
    PilhaEncad *fechados = new PilhaEncad();
    int cont = 0;
    raiz->setId(cont);

    cout << "Abertos: ";
    abertos->imprime();
    cout << "Fechados: ";
    fechados->imprime();

    cont += 1;

    if(!auxProfundidade(abertos->getTopo()->getInfo(), abertos, fechados, &cont)){
        cout << "Solucao nao encontrada!" << endl;
    }
}

bool Arvore::auxProfundidade(No* n, PilhaEncad *abertos, PilhaEncad *fechados, int *cont){
    if(n->visitaNo()){
        return true;
    }

    NoFP *aux = abertos->desempilha();
    fechados->empilha(aux);
    for (No* f : n->getFilhos()){
        f->setId(*cont);
        NoFP *faux = new NoFP(f);
        abertos->empilha(faux);
        *cont += 1;
    }

    cout << "Abertos: ";
    abertos->imprime();
    cout << "Fechados: ";
    fechados->imprime();

    for (No* f : n->getFilhos()){
        if(auxProfundidade(abertos->getTopo()->getInfo(), abertos, fechados, cont)){
            return true;
        }
    }

    return false;
}