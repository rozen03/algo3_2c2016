#include "../eje.h"
#include "../estructuras.h"
#include <iostream>
#include <queue>
#include <tuple>
using namespace std;
/*
 *int Bfs(vector<Nodo *>& nodos, vector<int>& predes, vector<int>& ord){
 *	vector<int> pred(nodos.size(), -1);
 *	vector<int> orden(nodos.size(), -1);
 *	vector<tuple<int, int> > list;
 *	tuple<int, int> prim(0, -3);
 *	list.push(prim);
 *	int next = 0;
 *	while(!list.empty()){
 *		tuple<int, int> aux = list.front();
 *		list.pop();
 *		int nod = get<0>(aux);
 *		int pad = get<1>(aux);
 *		if(order[nod] == -1){
 *			pred[nod] = padre;
 *			order[nod] = next;
 *			next++;
 *			Nodo nodin = *(nodos[nod]);
 *			priority_queue<Eje *> ejesNodin = nodin -> ejes;
 *			while(!ejesNodin.empty()){
 *				Eje * ejeaux = ejesNodin.front();
 *				ejesNodin.pop();
 *				Nodo nodoaux = *(ejeaux ->dameElOtroNodoProfa(&nodin));
 *				int acomp = nodoaux -> indice;
 *				tuple<int, int> arist(acomp, nod);
 *			}
 *		}
 *	}
 *	predes = pred;
 *	//pred tiene la informacion de los ejes, la posicion i te dice quien es el padre
 *	//para crear los nodos tenes que tener una copia limpia de los nodos y buscar el eje que
 *	//corresponda, fijarse que como es priority queue por ahi tenes que guardas los ejes que no eran
 *	//en una auxiliar y despues asignarlo devvuelta a los ejes del nodo.
 *	for(int i = 0 i<nodos.size(); i++);
 *	ord = orden;
 *
 *}
 */
int main(int argc, char *argv[]) {
  std::vector<Nodo *> nodos;
  std::vector<Eje *> ejes;
  parsearInput(nodos,ejes,1);

  std::cout << nodos.size() << std::endl;
  std::cout << ejes.size() << std::endl;
  for (size_t i = 0; i < nodos.size(); i++) {
    std::cout << nodos[i]->indice << std::endl;
  }
  for (size_t i = 0; i < ejes.size(); i++) {
    std::cout <<ejes[i]->n1->indice<<" "<<ejes[i]->n2->indice<<" "<<ejes[i]->peso  << std::endl;
  }
 }
