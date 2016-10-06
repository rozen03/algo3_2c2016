#include "../eje.h"
#include "../estructuras.h"
#include <iostream>
#include <queue>
#include <tuple>
using namespace std;
int Bfs(vector<Nodo *>& nodos){
	vector<int> pred(nodos.size(), -1);
	vector<int> orden(nodos.size(), -1);
	vector<Eje *> ejesAux(nodos.size(), NULL);
	//como consumo la cola de prioridad guardo el eje, representa el eje
	//que une a la iesima posicion del arreglo pred con el valor del nodo.
	vector<tuple<int, int, Eje *> > list;
	tuple<int, int, Eje *> prim(0, -3, NULL);
	list.push(prim);
	int next = 0;
	while(!list.empty()){
		tuple<int, int, Eje *> aux = list.front();
		list.pop();
		int nod = get<0>(aux);
		int pad = get<1>(aux);
		int ej = get<2>(aux);
		if(order[nod] == -1){
			Eje * ejeaux = buscarEje(nodos, padre, nod);
			pred[nod] = padre;
			order[nod] = next;
			ejesAux[nod] = ej;
			next++;
			Nodo nodin = *(nodos[nod]);
			priority_queue<Eje *> ejesNodin = nodin -> ejes;
			while(!ejesNodin.empty()){
				Eje * ejeaux = ejesNodin.front();
				ejesNodin.pop();
				Nodo nodoaux = *(ejeaux ->dameElOtroNodoProfa(&nodin));
				int acomp = nodoaux -> indice;
				tuple<int, int, Eje*> arist(acomp, nod, ejeaux);
			}
		}
	}
	predes = pred;
	//pred tiene la informacion de los ejes, la posicion i te dice quien es el padre
	//para crear los nodos tenes que tener una copia limpia de los nodos y buscar el eje que
	//corresponda, fijarse que como es priority queue por ahi tenes que guardas los ejes que no eran
	//en una auxiliar y despues asignarlo devvuelta a los ejes del nodo.
	vector<Nodo *> nodosNuevos;
	for(int i = 0; i<nodos.size(); i++){
		Nodo * aux = new Nodo(i);
		nodosNuevos.push_back(aux);
	}
	//creo un arreglo para ver si ya meti el eje que conecta dos vertices, por ejemplo el 12 lo meteria dos veces sin darme cuenta si no hago esto
	vector<int> metido(nodos.size(), -1);
	//son dos fors por que necesitaba inicializar el arreglo primero.
	for(int i = 0; i < nodos.size(); i++){
		if(metido[i] == -1){
			Eje * ejeaux = ejes[i];
			int pad = pred[i];
			metido[i] = 0;
			metido[pad] = 0;
			Nodo * hijo = nodosNuevos[i];
			Nodo * padre = nodosNuevos[pad];
			hijo -> ejes.push(ejeaux);
			padre -> ejes.push(ejeaux);
		}
	}
	nodos = nodosNuevos;
}

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
