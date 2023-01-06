#ifndef FILAENCAD_H_INCLUDED
#define FILAENCAD_H_INCLUDED
#include "NoFP.h"

using namespace std;

class FilaEncad
{
private:
    NoFP *inicio;
    NoFP *fim;      /// ponteiros para os No's extremos
    int tam;
public:
    FilaEncad();
    ~FilaEncad();
    NoFP* getInicio();           /// retorna valor do primeiro No
    void enfileira(NoFP* n);   /// insere No no fim
    NoFP* desenfileira();        /// elimina No do inicio
    bool vazia();
    void imprime(bool temHeuristica=false, bool eAEstrela = false);         /// verifica se fila esta vazia
    NoFP* get(int k);
    int getTam(){return this->tam;};
    void setTam(){this->tam += 1;};
};

#endif // FILAENCAD_H_INCLUDED
