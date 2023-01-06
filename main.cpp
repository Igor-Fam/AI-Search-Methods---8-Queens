#include <iostream>
#include <vector>

#include "./include/Tabuleiro.h"
#include "./include/No.h"
#include "./include/Arvore.h"

using namespace std;

int main(){
    // Cria arvore sem heuristica
    Arvore* a = new Arvore(true);
    a->iniciarBusca();
    // a->imprimeSolucao();
    // a->buscasInformadas(false, false);
}

