#ifndef ARVORE_H
#define ARVORE_H

#include "No.h"
#include "NoFP.h"
#include "PilhaEncad.h"

class Arvore
{
private:
    No* raiz;
    bool heuristica;

public:
    //heuristica ou sem heuristica
    Arvore(bool heuristica = false);
    ~Arvore();
    void iniciarBusca();
    void setarArvore();
    void resetarArvore();
    void imprimeSolucao();
    void buscaProfundidade();
    bool auxProfundidade(No* n, PilhaEncad *abertos, PilhaEncad *fechados, int *cont);
};

#endif