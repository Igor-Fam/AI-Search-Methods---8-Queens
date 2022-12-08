#ifndef PILHAENCAD_H_INCLUDED
#define PILHAENCAD_H_INCLUDED
#include "NoFP.h"

using namespace std;

class PilhaEncad
{
private:
    NoFP *topo;

public:
    PilhaEncad();
    ~PilhaEncad();
    NoFP* getTopo();
    void empilha(NoFP* n);
    NoFP* desempilha();
    bool vazia(); 
    void imprime();
};

#endif 