#include <iostream>
#include <vector>

#include "Tabuleiro.h"
#include "No.h"
#include "Arvore.h"

using namespace std;

int main(){
    // Tabuleiro* t = new Tabuleiro(0);
    // t->adicionaRainha(1);
    // t->adicionaRainha(4);
    // cout << t->contaDisponiveis();
    // t->imprimeTabuleiro();

    // No* n = new No(0, 0, false);
    // n->visitaNo();
    // n->imprimeTabuleiro();
    // vector<No*> filhos = n->getFilhos();
    // for (int i = 0; i < filhos.size(); i++)
    // {
    //     filhos[i]->visitaNo();
    // }

    // cout << "Imprimindo filhos" << endl;
    // n->imprimeFilhos();
    Arvore* a = new Arvore(false);
    a->iniciarBusca();
}

