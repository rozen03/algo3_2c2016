#ifndef __EJE__
#define __EJE__
#include <iostream>
#include <queue>
using namespace std;
class Nodo;
class Eje {
public:
  int indice;
  Nodo *n1;
  Nodo *n2;
  unsigned int peso;
  Eje(unsigned int i, unsigned int p, Nodo *n1, Nodo *n2)
      : indice(i), peso(p), n1(n1), n2(n2){};
  int damePeso(){
	return peso;	
	};
  bool esPared();
  bool esta(Nodo *);
  Nodo *dameElOtroNodoPorfa(Nodo *n) {
    if (n == n1) {
      return this->n2;
    } else {
      return this->n1;
    }
  };
  bool operator<(const Eje e2) const { return this->peso > e2.peso; }
  Nodo *dameNodo(){
	return this->n1;
  }


private:
};
#endif
