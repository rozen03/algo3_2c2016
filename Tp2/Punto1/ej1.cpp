#include "../eje.h"
#include "../estructuras.h"
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;
// Busqueda lineal return

void Imprimir(vector<Nodo *> &nodos) {
	for (int i = 0; i < nodos.size(); i++) {
		cout << nodos[i]->indice;
		vector<Eje *> vectEjes = nodos[i]->ejejes;
		for (int j = 0; j < vectEjes.size(); j++) {
			Nodo *nodin = vectEjes[j]->dameNodo();
			cout << "(" << nodin->indice << ", "
			<< vectEjes[j]->dameElOtroNodoPorfa(nodin)->indice << ")";
		}
		cout << " " << endl;
	}
}

int Bfs(vector<Nodo *> &nodos) {
	vector<int> pred(nodos.size(), -1);
	vector<int> orden(nodos.size(), -1);
	// como consumo la cola de prioridad guardo el eje, representa el eje
	// que une a la iesima posicion del arreglo pred con el valor del nodo.
	queue<tuple<int, int>> list;
	tuple<int, int> prim(0, -3);
	int primerFinal = -1;
	list.push(prim);
	int next = 0;
	// BFS normal, salvo los if del for anidado.
	while (!list.empty()) {
		tuple<int, int> aux = list.front();
		list.pop();
		int nod = get<0>(aux);
		int padre = get<1>(aux);
		if (orden[nod] == -1) {
			pred[nod] = padre;
			orden[nod] = next;
			next++;
			Nodo *nodin = nodos[nod];
			vector<Eje *> ejesNodin = nodin->ejejes;
			// me fijo si es final, si lo es corto el bfs por que ya encontre la
			// primer solucion y ya marque todo lo que tenia que marcar.
			if (nodin->esFinal) {
				primerFinal = nod;
				break;
			}
			// agregamos los ejes que estan conectados
			for (unsigned int i = 0; i < ejesNodin.size(); i++) {
				Eje *ejeaux = ejesNodin[i];
				Nodo *nodoaux = ejeaux->dameElOtroNodoPorfa(nodin);
				int acomp = nodoaux->indice;
				// si ya lo tagee o estoy bajando a una instancia invalida, reconstruir
				// una pared
				if (orden[acomp] != -1 || nodoaux->nivel < nodin->nivel)
				continue;
				// estamos en el mismo nivel pero estoy rompiendo una pared, tendria que
				// subir de nivel
				if (nodoaux->nivel == nodin->nivel && nodoaux->esPared)
				continue;
				tuple<int, int> arist(acomp, nod);
				list.push(arist);
			}
		}
	}

	int x = primerFinal;
	// res es los nodos que atravece, empiezo en uno por que en el while
	// no sumo el ultimo nodo.
	int res = 1;
	int aux = 0;
	// uso un aux por que era mas facil de programar y entende, como mucho tenes
	// que recorrer todo el grafo, n-1 nodos

	if (primerFinal == -1) {
		res = -1;
	} else {
		while (aux < nodos.size()) {
			x = pred[x];
			res++;
			aux++;
			if (x == 0 || x == -1)
			break;
		}
	}
	return res;
}

int Solucion(vector<Nodo *> &nodos, vector<Eje *> &ejes, int p) {
	int res = p * 2 * nodos.size();
	// quiero una res que sea lo mas grande posible, probablemente no tengo
	// que multiplicar por p para tener algo lo suficientemente grande pero por
	// las dudas y para no pensar de mas...
	if (p == 0)
	res = 2 * nodos.size();
	// not not not // como res va a ir cambiando creo una copia, si es igual no
	// había solucion.
	int nores = res;
	for (int i = 0; i < p; i++) {
		clonarUltimoNivel(nodos, ejes);
	}
	int res = Bfs(nodos);
	if (res == nores) {
		res = -1;
	}
	return res;
}
/*
int main(int argc, char *argv[]) {
  std::vector<Nodo *> nodos;
  std::vector<Eje *> ejes;

  int p = 0;
  p = parsearInput(nodos,ejes,1);
  int res = Solucion(nodos, ejes, p);
  cout<<res<<endl;

  return 0;
 }
*/
