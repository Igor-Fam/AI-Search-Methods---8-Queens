#ifndef ARVORE_H
#define ARVORE_H

#include "No.h"
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
    bool backtracking(No *atual, int nivel);
    bool buscaProfundidade(No* n, int nivel);
    bool buscaLargura();
};

#endif