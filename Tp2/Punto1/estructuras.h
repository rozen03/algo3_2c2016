#ifndef __NODO__
#define __NODO__
#include <iostream>
#include <queue>
using namespace std;
class Eje;
class Nodo {
public:
  unsigned int indice;
  priority_queue<Eje> ejes;
  Nodo(unsigned int indice) : indice(indice){};

private:
};
#endif
