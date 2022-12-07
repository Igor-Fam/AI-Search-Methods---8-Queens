#include <iostream>
#include <vector>
#include <queue>

#include "../include/Arvore.h"
#include "../include/No.h"

using namespace std;

Arvore::Arvore(bool heuristica){
    this->heuristica = heuristica;
    raiz = nullptr;
    solucao = nullptr;
    nivelSolucao = 0;
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
    
    bool sucesso = false;
    switch (busca)
    {
    case 1:
        sucesso = backtracking(raiz, 0);
        break;
    case 2:
        // buscaLargura();
        break;
    case 3:
        sucesso = buscaProfundidade(raiz, 0);
        break;
    }

    imprimeSolucao();
}

void Arvore::imprimeSolucao(){
    if (solucao == nullptr){
        cout << "Solucao nao encontrada!" << endl;
    }
    else {
        cout << "Estado solucao no nivel " << nivelSolucao << endl;
        solucao->imprimeTabuleiro();
    }
}

bool Arvore::backtracking(No* atual, int nivel)
{
    if (atual->visitaNo()){ //no atual é o no solucao
        solucao = atual->getTabuleiro();
        nivelSolucao = nivel;
        return true;
    }
    cout << "Nivel " << nivel << endl;
    atual->getTabuleiro()->imprimeTabuleiro();
    
    bool sucesso = false;
    queue<int> regras = atual->getRegras();
    
    while (!(regras.empty() || sucesso)){
        int regra = regras.front();
        regras.pop();
        atual->adicionaNo(regra);
        sucesso = backtracking(atual->getFilhos().back(), nivel+1);
    }
    return sucesso;
}

bool Arvore::buscaProfundidade(No* n, int nivel){
    if(n->visitaNo()){
        solucao = n->getTabuleiro();
        nivelSolucao = nivel;
        return true;
    }

    queue<int> regras = n->getRegras();
    while (!regras.empty()){
        n->adicionaNo(regras.front());
        regras.pop();
    }

    for (No* f : n->getFilhos()){
        if(buscaProfundidade(f, nivel+1)){
            return true;
        }
    }

    return false;
}
