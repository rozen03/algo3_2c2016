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

char DarLetra(Nodo * aux){
	char res = '.';
	if(aux -> esPared){
		res = '#';
	}
	else if(aux -> esFinal){
		res = 'x';
	 }
	 return res;
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
			cout<<"quiero ver cual es el nodo que estoy actualizando"<<endl;
			cout<<DarLetra(nodin)<<" su indice "<<nodin -> indice << " su nivel "<<nodin -> nivel;
			cout<<" es final? "<< nodin -> esFinal << " esPared? "<< nodin -> esPared<<endl;
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
				cout<<"quiero ver que nodos agrego o no "<<endl;
			    cout<<DarLetra(nodoaux)<<" su indice "<<nodoaux -> indice << " su nivel "<<nodoaux -> nivel;
			    cout<<" es final? "<< nodoaux -> esFinal << " esPared? "<< nodoaux -> esPared<<endl;
				int acomp = nodoaux->indice;
				// si ya lo tagee o estoy bajando a una instancia invalida, reconstruir
				// una pared
				if (orden[acomp] != -1 || nodoaux->nivel < nodin->nivel)
				continue;
				// estamos en el mismo nivel pero estoy rompiendo una pared, tendria que
				// subir de nivel
				if (nodoaux->nivel == nodin->nivel && nodoaux->esPared)
				continue;
				cout<<"agregue al nodo "<<acomp<<endl;
				tuple<int, int> arist(acomp, nod);
				list.push(arist);
			}
			cout<<"Voy al prox elemento de la lista"<<endl;
		}
	}

	int x = primerFinal;
	// res es los nodos que atravece, empiezo en uno por que en el while
	// no sumo el ultimo nodo.
	int res = 0;
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


void ImprimirNivel(vector<Nodo *> nodos, int f, int c){
	for(int i = 0; i<nodos.size(); i++){
		Nodo * aux = nodos[i];
		char letra = DarLetra(aux);
		if(i % f-2 == 0) cout<<"\n";
		cout<< letra<<" ";
	}
}

void mostrarNiveles(vector<Nodo *> nodos, int p, int f, int c){
	vector<Nodo *> copia;
	vector<vector<Nodo *> > Niveles(p+1, copia);
	for(int i = 0; i< nodos.size(); i++){
		Nodo * aux = nodos[i];
		int piso = aux -> nivel;
		Niveles[piso].push_back(aux);
	}
	for(int i = 0; i< Niveles.size(); i++){
		cout<<"En el piso "<< i<<" tenemos la siguiente configuración\n";
		vector<Nodo *> plataforma = Niveles[i];
		ImprimirNivel(plataforma, f, c);
		cout<<endl;
	}
}

int Solucion(vector<Nodo *> &nodos, vector<Eje *> &ejes, int p, int f, int c) {
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
		//mostrarNiveles(nodos,p, f, c);
		clonarUltimoNivel(nodos, ejes);
	}
	res = Bfs(nodos);
	if (res == nores) {
		res = -1;
	}
	return res;
}

int main(int argc, char *argv[]) {
  std::vector<Nodo *> nodos;
  std::vector<Eje *> ejes;
  int f;
  int c;
  int p = 0;
  p = parsearInput(nodos,ejes,1, f, c);
  cout<< f <<" "<<c<<endl;
  int res = Solucion(nodos, ejes, p, f, c);
  cout<<res<<endl;

  return 0;
 }
