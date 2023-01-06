#ifndef ARVORE_H
#define ARVORE_H

#include "No.h"

#include "PilhaEncad.h"
#include "Tabuleiro.h"
#include "NoFP.h"
#include "FilaEncad.h"
class Arvore
{
private:
    No* raiz;
    bool heuristica;
    Tabuleiro *solucao;
    int nivelSolucao;

public:
    //heuristica ou sem heuristica
    Arvore(bool heuristica = false);
    ~Arvore();
    void iniciarBusca();
    void setarArvore();
    void resetarArvore();
    void imprimeSolucao();
    void buscaOrdenada();
    void buscaGulosa();
    void buscaAestrela();
    void buscasInformadas(bool temHeuristica = false, bool eAEstrela = false);
    void buscaProfundidade();
    void quickSort(FilaEncad *abertos);
    void auxQuickSort(FilaEncad *abertos, int p, int q);
    void troca(NoFP *a, NoFP *b);
    int particionamento(FilaEncad *abertos, int p, int q);
    bool auxProfundidade(No* n, PilhaEncad *abertos, PilhaEncad *fechados, int *cont, int nivel);
    bool backtracking(No *atual, int nivel);
    bool buscaLargura();
    bool auxBuscasInformadas(No* n, FilaEncad *abertos, FilaEncad *fechados, bool temHeuristica, bool eAEstrela, int *cont, int nivel=0, int custoAcumulado=0);

};

#endif