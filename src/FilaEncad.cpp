#include <iostream>
#include <cstdlib>
#include "../include/FilaEncad.h"

using namespace std;

FilaEncad::FilaEncad()
{
    inicio = NULL;
    fim = NULL;
    tam = 0;
}

FilaEncad::~FilaEncad()
{
    NoFP *p = inicio;
    while (inicio != NULL)
    {
        inicio = p->getProx();
        delete p;
        p = inicio;
    }
    fim = NULL;
}

bool FilaEncad::vazia()
{
    if (inicio == NULL)
        return true;
    else
        return false;
}

void FilaEncad::enfileira(NoFP *n)
{
    n->setProx(NULL);
    if (fim == NULL)
        inicio = n;
    else
        fim->setProx(n);
    fim = n;
    setTam();
}

NoFP *FilaEncad::getInicio()
{
    if (inicio != NULL)
        return inicio;
    else
    {
        cout << "Fila vazia!" << endl;
        exit(1);
    }
}

NoFP *FilaEncad::desenfileira()
{
    NoFP *p;
    if (inicio != NULL)
    {
        p = inicio;
        inicio = p->getProx();
        if (inicio == NULL)
            fim = NULL;
        tam -= 1;
        return p;
    }
    else
    {
        cout << "ERRO: Fila Vazia!" << endl;
        exit(1);
    }
}

void FilaEncad::imprime(bool temHeuristica, bool eAEstrela)
{
    if (inicio != NULL)
    {
        NoFP *p = inicio;
        while (p != NULL)
        {
            if(temHeuristica && eAEstrela){
                cout << p->getInfo()->getId() << " ("  << p->getInfo()->getCustoStar() << ") , ";
            }
            if(temHeuristica && !eAEstrela){
                cout << p->getInfo()->getId() << " ("  << p->getInfo()->getCustoHeur() << ") , ";
            }
            else{
                cout << p->getInfo()->getId() << " ("  << p->getInfo()->getCusto() << ") , ";
            }
            p = p->getProx();
        }
        cout << endl;
    }
}

NoFP* FilaEncad::get(int k)
{
    NoFP *p = inicio;
    int i = 0;
    while (i < k && p != NULL)
    {
        i++;
        p = p->getProx();
    }
    if (p == NULL)
    {
        cout << "ERRO: Indice inválido!" << endl;
        exit(1);
    }
    else {
        return p;
    }
}
