#include "../eje.h"
#include "../estructuras.h"
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;


//Busqueda lineal return
Eje * buscarEje(vector<Nodo *>& nodos, int padre, int hijo){
	Nodo * elNod = nodos[padre];

	cout<<nodos[padre]->indice<<endl;
	vector<Eje *> ejesNod = elNod -> ejes;
	Eje * res;
	for(unsigned int i= 0; i<ejesNod.size(); i++){
		Eje * ejeAux = ejesNod[i];
		Nodo * nodAux = ejeAux -> dameElOtroNodoPorfa(elNod);
		if(nodAux ->indice == hijo) return ejeAux;
	}
}

int Bfs(vector<Nodo *>& nodos){
	vector<int> pred(nodos.size(), -1);
	vector<int> orden(nodos.size(), -1);
	vector<Eje *> ejesAux(nodos.size(), NULL);
	//como consumo la cola de prioridad guardo el eje, representa el eje
	//que une a la iesima posicion del arreglo pred con el valor del nodo.
	queue<tuple<int, int, Eje *> > list;
	tuple<int, int, Eje *> prim(0, -3, NULL); 
	list.push(prim);
	int next = 0;
	while(!list.empty()){
		tuple<int, int, Eje *> aux = list.front();
		list.pop();
		int nod = get<0>(aux);
		int padre = get<1>(aux);
		Eje * ej = get<2>(aux);
		if(orden[nod] == -1){
			/*Eje * ejeaux;
			if(nod == 0){
				ejeaux = NULL;
			}
			else{
				ejeaux = buscarEje(nodos, padre, nod);
			}*/
			pred[nod] = padre;
			orden[nod] = next;

			ejesAux[nod] = ej;
			next++;
			Nodo* nodin = nodos[nod];
			vector<Eje *> ejesNodin = nodin -> ejes;
			for(unsigned int i=0 ; i<ejesNodin.size(); i++){
				Eje * ejeaux = ejesNodin[i];				
				Nodo * nodoaux = ejeaux ->dameElOtroNodoPorfa(nodin);
				int acomp = nodoaux -> indice;
				if(orden[acomp] != -1) continue;
				tuple<int, int, Eje*> arist(acomp, nod, ejeaux);
				list.push(arist);				
			}
		}
	}
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
	for(int i = 1; i < nodos.size(); i++){
		if(metido[i] == -1){
			Eje * ejeaux = ejesAux[i];
			int pad = pred[i];
			metido[i] = 0;
			metido[pad] = 0;
			Nodo * hijo = nodosNuevos[i];
			
			Nodo * padre = nodosNuevos[pad];
			hijo -> ejes.push_back(ejeaux);
			padre -> ejes.push_back(ejeaux);
		}
	}
	nodos = nodosNuevos;
	/*for(int i=0; i<nodosNuevos.size(); i++){
			cout<< nodosNuevos[i]->indice;
			vector<Eje *> vectEjes = nodosNuevos[i]->ejes;
			for(int j=0; j<vectEjes.size(); j++){
				Nodo * nodin = vectEjes[j]->dameNodo();
				cout <<"("<< nodin->indice<<", "<<vectEjes[j]->dameElOtroNodoPorfa(nodin)->indice<<")";
			}
			cout<< " "<<endl;
	}*/
}

int main(int argc, char *argv[]) {
  std::vector<Nodo *> nodos;
  std::vector<Eje *> ejes;
  parsearInput(nodos,ejes,1);
  /*cout<<"fin parsear"<<endl;
  std::cout << nodos.size() << std::endl;
  std::cout << ejes.size() << std::endl;
  for (size_t i = 0; i < nodos.size(); i++) {
    std::cout << nodos[i]->indice << std::endl;
  }
  for (size_t i = 0; i < ejes.size(); i++) {
    std::cout <<ejes[i]->n1->indice<<" "<<ejes[i]->n2->indice<<" "<<ejes[i]->peso  << std::endl;
  }*/
  Bfs(nodos);
  
  return 0;
 }
