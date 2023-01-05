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

    auxBuscasInformadas(temHeuristica, eAEstrela, &cont);

}

bool Arvore::auxBuscasInformadas(bool temHeuristica, bool eAEstrela, int *cont) {

    //Ordena as filas de acordo com o custo critério
    if (eAEstrela)
    {
        //orderby(custoStar)
    }
    if (eAEstrela)
    {
        //orderby(custoHeur)
    }
    else
    {
        //orderby(custo)
    }

    return false;
}


// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------


// void ListaEncad::quickSort(int *comp, int *mov, float *tempo)
// {

//     Art *A = new Art[n];
//     Artists *p = primeiro;

//     //Iniciando a contagem do tempo
//     t_ini = time(NULL);

//     //Copiando informações da lista para o vetor de struct
//     for (int i = 0; i < n; i++)
//     {
//         strncpy(A[i].id, p->getId(), 22);
//         A[i].genres = p->getGenres();
//         A[i].name = p->getName();
//         A[i].popularity = p->getPopularity();
//         A[i].followers = p->getFollowers();
//         A[i].tamName = p->getTamName();
//         A[i].tamGenres = p->getTamGenres();
//         A[i].tamPulaLinha = p->getTamPulaLinha();
//         p = p->getProx();
//     }

//     //Chamando a função auxiliar para iniciar o quickSort
//     auxQuickSort(A, 0, n - 1, comp, mov);

//     //voltando o ponteiro para o inicial
//     p = primeiro;

//     //Passando as informações do vetor de struct para a lista
//     for (int i = 0; i < n; i++)
//     {
//         p->setId(A[i].id);
//         p->setGenres(A[i].genres);
//         p->setName(A[i].name);
//         p->setPopularity(A[i].popularity);
//         p->setFollowers(A[i].followers);
//         p->setTamGenres(A[i].tamGenres);
//         p->setTamPulaLinha(A[i].tamPulaLinha);
//         p->setTamName(A[i].tamName);
//         p = p->getProx();
//     }

//     //Deletando vetor alocado
//     delete[] A;

//     cout << "Concluido!" << endl;

//     //Fim da contagem do tempo
//     t_fim = time(NULL);

//     //Verificando se a lista está ordenada
//     // ordenado();

//     //Contando tempo necessário para execução
//     *tempo = t_fim - t_ini;

//     // cout << "Tempo para quickSort: " << *tempo << "s" << endl;
// }

// void ListaEncad::auxQuickSort(Art A[], int p, int q, int *comp, int *mov)
// {
//     //Verificando se o início é maior que o final
//     if (p < q)
//     {
//         //Começando o particionamento para iniciar o valor de j
//         int j = particionamento(A, p, q, comp, mov);
//         //Chamadas recursivas para dividir a lista e particioná-la
//         auxQuickSort(A, p, j - 1, comp, mov);
//         auxQuickSort(A, j + 1, q, comp, mov);
//     }
// }

// int ListaEncad::particionamento(Art A[], int p, int q, int *comp, int *mov)
// {
//     int i = p - 1, j = q;
//     //Escolhe o ponteiro
//     int v = A[q].followers;

//     while (1)
//     {
//         //Percorrer o vetor até encontrar um elemento menor do que o pivô
//         while (A[++i].followers < v)
//         {
//             (*comp)++;
//         }
//         //Percorrer o vetor até encontrar um elemento maior do que o pivô
//         while (v < A[--j].followers)
//         {
//             if (j == p)
//                 break;
//             (*comp)++;
//         }
//         //Se os índices i e j se cruzarem o programa para
//         if (i >= j)
//             break;
//         //Troca o elemento da esquerda com o da direita
//         troca(&A[i], &A[j]);
//         (*mov)++;
//     }
//     //Troca o elemento da esquerda com o último elemento
//     troca(&A[i], &A[q]);
//     (*mov)++;

//     return i;
// }


