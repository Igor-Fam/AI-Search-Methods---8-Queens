#include "Tabuleiro.h"
#include "iostream"
#include "No.h"

using namespace std;

int main(){
    // Tabuleiro* t = new Tabuleiro();
    // t->adicionaRainha(1);
    // t->adicionaRainha(4);
    // cout << t->contaDisponiveis();
    // t->imprimeTabuleiro();

    No* n = new No(0, false);
    n->visitaNo();
    n->imprimeTabuleiro();
    n->imprimeFilhos();
}

