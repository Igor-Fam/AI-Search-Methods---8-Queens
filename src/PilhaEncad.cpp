#include <iostream>
#include <cstdlib>
#include "../include/PilhaEncad.h"

using namespace std;

PilhaEncad::PilhaEncad()
{
    topo = NULL;
}

// destrutor
PilhaEncad::~PilhaEncad()
{
    NoFP* p = topo;
    while(topo != NULL)
    {
        topo = p->getProx();
        delete p;
        p = topo;
    }
}

void PilhaEncad::empilha(NoFP* n)
{
    n->setProx(topo);
    topo = n;
}

NoFP* PilhaEncad::desempilha()
{
    NoFP* p;
    if(topo != NULL)
    {
        p = topo;
        topo = p->getProx();
        return p;
    }
    else
    {
        cout << "ERRO: Pilha vazia!" << endl;
        exit(1);
    }
}

NoFP* PilhaEncad::getTopo()
{
    if(topo != NULL)
        return topo;
    else
    {
        cout << "Pilha vazia!" << endl;
        exit(1);
    }
}

bool PilhaEncad::vazia()
{
    if(topo == NULL)
        return(true);
    else
        return(false);
}

void PilhaEncad::imprime()
{
    if (topo != NULL){
        NoFP *p = topo;
        while (p != NULL){
            cout << p->getInfo()->getId() << ", ";
            p = p->getProx();
        }
    }
    cout << endl;
}