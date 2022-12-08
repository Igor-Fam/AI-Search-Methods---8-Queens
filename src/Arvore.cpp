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

Arvore::~Arvore(){
    delete raiz;
    delete solucao;
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
        cout << "A árvore já tem nó raiz!" << endl;
        return;
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
        backtracking(raiz, 0);
        break;
    case 2:
        buscaLargura();
        break;
    case 3:
        buscaProfundidade();
        break;
    }
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

    if(!auxProfundidade(abertos->getTopo()->getInfo(), abertos, fechados, &cont, 0)){
        cout << "Solucao nao encontrada!" << endl;
    }
}

bool Arvore::auxProfundidade(No* n, PilhaEncad *abertos, PilhaEncad *fechados, int *cont, int nivel){
    if(n->visitaNo(-1)){
        solucao = n->getTabuleiro();
        nivelSolucao = nivel;
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
        if(auxProfundidade(abertos->getTopo()->getInfo(), abertos, fechados, cont, nivel+1)){
            return true;
        }
    }

    return false;
}

bool Arvore::buscaLargura(){

    No *S = raiz;
    S->setNivel(0);
    S->setId(0);
    No *n = S;

    NoFP *nf = new NoFP(n);
    NoFP *s = new NoFP(S);

    FilaEncad *abertos = new FilaEncad();
    abertos->enfileira(s);

    FilaEncad *fechados = new FilaEncad();

    bool fracasso = false;
    bool sucesso = false;

    int cont = 1;

    while (!(sucesso || fracasso))
    {
        if (abertos->vazia())
        {
            fracasso = true;
        }
        else
        {
            nf = abertos->desenfileira();
            n = nf->getInfo();

            if(n->visitaNo()){
                solucao = n->getTabuleiro();
                nivelSolucao = n->getNivel();
                sucesso = true;
            }
        
            cout << n->getId() << " Pai: " << endl;
            cout << "Nivel: " << n->getNivel() << endl;
            n->getTabuleiro()->imprimeTabuleiro();

            queue<int> regras = n->getRegras();
    
            while (!regras.empty()){
                No* aux = n->adicionaNo(regras.front());
                aux->setId(cont);
                aux->setNivel(n->getNivel() + 1);
                NoFP *auxF = new NoFP(aux);
                abertos->enfileira(auxF);
                cout << aux->getId() << " Filho:" << ": " << endl;
                aux->getTabuleiro()->imprimeTabuleiro();
                regras.pop();
                cont++;
            }

            fechados->enfileira(nf);

            cout << "Abertos: ";
            abertos->imprime();
            cout << "Fechados: ";
            fechados->imprime();
            
        }
    }

    return false;
}

