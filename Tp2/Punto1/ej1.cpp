#include "../eje.h"
#include "../estructuras.h"
#include <iostream>
#include <queue>
using namespace std;

int main(int argc, char *argv[]) {
  std::vector<Nodo *> nodos;
  std::vector<Eje *> ejes;
  parsearInput(nodos,ejes,2);
  std::cout << nodos.size() << std::endl;
  std::cout << ejes.size() << std::endl;
  for (size_t i = 0; i < nodos.size(); i++) {
    std::cout << nodos[i]->indice << std::endl;
  }
  for (size_t i = 0; i < ejes.size(); i++) {
    std::cout <<ejes[i]->n1->indice<<" "<<ejes[i]->n2->indice<<" "<<ejes[i]->peso  << std::endl;
  }
 }
