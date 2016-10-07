//#include "../estructuras.h"
#include "estructuras_test.h"
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;
void Imprimir(vector<Nodo *>& nodos){

	for(int i=0; i<nodos.size(); i++){
			cout<< nodos[i]->indice;
			vector<Eje *> vectEjes = nodos[i]->ejejes;
			for(int j=0; j<vectEjes.size(); j++){
				Nodo * nodin = vectEjes[j]->dameNodo();
				cout <<"("<< nodin->indice<<", "<<vectEjes[j]->dameElOtroNodoPorfa(nodin)->indice<<")";
			}
			cout<< " "<<endl;
		}
}
int main(int argc, char *argv[]) {
  std::vector<Nodo *> nodos;
  std::vector<Eje *> ejes;
  parsearInput(nodos,ejes,10,10,2,false);

  cout<<"fin parsear"<<endl;
  return 0;
 }
