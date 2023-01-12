#include <iostream>
#include <vector>
#include <queue>
#include <chrono>

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
    cout << "4 - Busca Ordenada" << endl;
    cout << "5 - Busca Gulosa" << endl;
    cout << "6 - Busca A*" << endl;
    cin >> busca;

    while (busca < 1 || busca > 6)
    {
        cout << "Opçao invalida! Escolha outra opcao" << endl;
        cin >> busca;
    }

    setarArvore();

    auto start = chrono::steady_clock::now();
    auto end = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(end - start);

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
    case 4:
        start = chrono::steady_clock::now();
        buscaOrdenada();
        end = chrono::steady_clock::now();
        elapsed_ms = chrono::duration_cast<chrono::milliseconds>(end - start);
        cout << "Tempo gasto: " << elapsed_ms.count() / 1000.0000 << " s" << endl;
        break;
    case 5:
        start = chrono::steady_clock::now();
        buscaGulosa();
        end = chrono::steady_clock::now();
        elapsed_ms = chrono::duration_cast<chrono::milliseconds>(end - start);
        cout << "Tempo gasto: " << elapsed_ms.count() / 1000.0000 << " s" << endl;
        break;
    case 6:
        start = chrono::steady_clock::now();
        buscaAestrela();
        end = chrono::steady_clock::now();
        elapsed_ms = chrono::duration_cast<chrono::milliseconds>(end - start);
        cout << "Tempo gasto: " << elapsed_ms.count() / 1000.0000 << " s" << endl;
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
            quickSort(abertos);
            abertos->imprime();
            cout << "Fechados: ";
            fechados->imprime();
        }
    }

    return false;
}


void Arvore::buscaOrdenada(){

    bool temHeuristica = false;
    bool eAEstrela = false;
    buscasInformadas(temHeuristica,eAEstrela);

}

void Arvore::buscaGulosa(){

    bool temHeuristica = true;
    bool eAEstrela = false;
    buscasInformadas(temHeuristica,eAEstrela);

}

void Arvore::buscaAestrela(){

    bool temHeuristica = true;
    bool eAEstrela = true;
    buscasInformadas(temHeuristica,eAEstrela);

}

void Arvore::buscasInformadas(bool temHeuristica, bool eAEstrela) {

    if (raiz == nullptr){
        cout << "A arvore esta vazia!" << endl;
        return;
    }

    No *S = raiz;
    S->setNivel(0);
    S->setId(0);
    S->setCusto(0);
    No *n = S;

    NoFP *nf = new NoFP(n);
    NoFP *s = new NoFP(S);

    FilaEncad *abertos = new FilaEncad();
    abertos->enfileira(s);

    FilaEncad *fechados = new FilaEncad();

    cout << "Abertos: ";
    abertos->imprime(temHeuristica, eAEstrela);
    cout << "Fechados: ";
    fechados->imprime(temHeuristica, eAEstrela);
    cout << endl;

    int cont = 1;
    int nivel = 0;
    int custoAcumulado = 0;

    if(!auxBuscasInformadas(abertos->getInicio()->getInfo(), abertos, fechados, temHeuristica, eAEstrela, &cont, nivel, custoAcumulado)){
        cout << "Solucao nao encontrada!" << endl;
    }
}

bool Arvore::auxBuscasInformadas(No* n, FilaEncad *abertos, FilaEncad *fechados, bool temHeuristica, bool eAEstrela, int *cont, int nivel, int custoAcumulado) {

    if(n->visitaNo(-1, temHeuristica, eAEstrela)){
        solucao = n->getTabuleiro();
        nivelSolucao = nivel;
        return true;
    }

    NoFP *aux = abertos->desenfileira();
    fechados->enfileira(aux);
    for (No* f : n->getFilhos()){
        f->setId(*cont);
        NoFP *faux = new NoFP(f);
        abertos->enfileira(faux);
        *cont += 1;
    }

    quickSort(abertos, temHeuristica, eAEstrela);

    cout << "Abertos: ";
    abertos->imprime(temHeuristica, eAEstrela);
    cout << "Fechados: ";
    fechados->imprime(temHeuristica, eAEstrela);

    for (No* f : n->getFilhos()){
        int custoTemp = aux->getInfo()->getCusto();
        if (temHeuristica)
        {
            int custoTemp = aux->getInfo()->getCustoHeur();
        }
        if (eAEstrela)
        {
            int custoTemp = aux->getInfo()->getCustoStar();
        }
        if(auxBuscasInformadas(abertos->getInicio()->getInfo(), abertos, fechados, temHeuristica, eAEstrela, cont, nivel+1, custoAcumulado + custoTemp)){
            return true;
        }
    }

    return false;

}

void Arvore::quickSort(FilaEncad *abertos, bool temHeuristica, bool eAEstrela)
{
    int n = abertos->getTam();
    auxQuickSort(abertos, 0, n - 1, temHeuristica, eAEstrela);
}

void Arvore::auxQuickSort(FilaEncad *abertos, int p, int q, bool temHeuristica, bool eAEstrela)
{
    //Verificando se o início é maior que o final
    if (p < q)
    {
        int j = 0;
        //Começando o particionamento para iniciar o valor de j
        if (eAEstrela){
            j = particionamentoStar(abertos, p, q);
        }
        else if (temHeuristica && !eAEstrela){
            j = particionamentoHeur(abertos, p, q);
        }
        else {
           j = particionamento(abertos, p, q);
        }

        //Chamadas recursivas para dividir a lista e particioná-la
        auxQuickSort(abertos, p, j - 1, temHeuristica, eAEstrela);
        auxQuickSort(abertos, j + 1, q, temHeuristica, eAEstrela);
    }
}

int Arvore::particionamento(FilaEncad *abertos, int p, int q)
{
    int i = p - 1, j = q;
    //Escolhe o ponteiro
    int v = abertos->get(q)->getInfo()->getCusto();

    while (1)
    {
        //Percorrer o vetor até encontrar um elemento menor do que o pivô
        while (abertos->get(++i)->getInfo()->getCusto() < v)
        {
        }
        //Percorrer o vetor até encontrar um elemento maior do que o pivô
        while (v < abertos->get(--j)->getInfo()->getCusto())
        {
            if (j == p)
                break;
        }
        //Se os índices i e j se cruzarem o programa para
        if (i >= j)
            break;
        //Troca o elemento da esquerda com o da direita
        troca(abertos->get(i), abertos->get(j));
    }
    //Troca o elemento da esquerda com o último elemento
    troca(abertos->get(i), abertos->get(q));
    return i;
}

int Arvore::particionamentoHeur(FilaEncad *abertos, int p, int q)
{
    int i = p - 1, j = q;
    //Escolhe o ponteiro
    int v = abertos->get(q)->getInfo()->getCustoHeur();

    while (1)
    {
        //Percorrer o vetor até encontrar um elemento menor do que o pivô
        while (abertos->get(++i)->getInfo()->getCustoHeur() < v)
        {
        }
        //Percorrer o vetor até encontrar um elemento maior do que o pivô
        while (v < abertos->get(--j)->getInfo()->getCustoHeur())
        {
            if (j == p)
                break;
        }
        //Se os índices i e j se cruzarem o programa para
        if (i >= j)
            break;
        //Troca o elemento da esquerda com o da direita
        troca(abertos->get(i), abertos->get(j));
    }
    //Troca o elemento da esquerda com o último elemento
    troca(abertos->get(i), abertos->get(q));
    return i;
}

int Arvore::particionamentoStar(FilaEncad *abertos, int p, int q)
{
    int i = p - 1, j = q;
    //Escolhe o ponteiro
    int v = abertos->get(q)->getInfo()->getCustoStar();

    while (1)
    {
        //Percorrer o vetor até encontrar um elemento menor do que o pivô
        while (abertos->get(++i)->getInfo()->getCustoStar() < v)
        {
        }
        //Percorrer o vetor até encontrar um elemento maior do que o pivô
        while (v < abertos->get(--j)->getInfo()->getCustoStar())
        {
            if (j == p)
                break;
        }
        //Se os índices i e j se cruzarem o programa para
        if (i >= j)
            break;
        //Troca o elemento da esquerda com o da direita
        troca(abertos->get(i), abertos->get(j));
    }
    //Troca o elemento da esquerda com o último elemento
    troca(abertos->get(i), abertos->get(q));
    return i;
}

//Inverte os valores de dois objetos do tipo Art.
void Arvore::troca(NoFP *a, NoFP *b)
{
    //Criando variável auxiliar
    NoFP *aux = new NoFP(a->getInfo());
    aux->setProx(a->getProx());

    //Passando os valores de b para a
    a->setInfo(b->getInfo());

    //passando os valores da variável auxiliar para b
    b->setInfo(aux->getInfo());
}