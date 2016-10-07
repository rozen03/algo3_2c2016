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

int Bfs(vector<Nodo *>& nodos){
	vector<int> pred(nodos.size(), -1);
	vector<int> orden(nodos.size(), -1);
	vector<Eje *> ejesAux(nodos.size(), NULL);
	//como consumo la cola de prioridad guardo el eje, representa el eje
	//que une a la iesima posicion del arreglo pred con el valor del nodo.
	queue<tuple<int, int> > list;
	tuple<int, int> prim(0, -3);
	list.push(prim);
	int next = 0;
	while(!list.empty()){
		tuple<int, int> aux = list.front();
		list.pop();
		int nod = get<0>(aux);
		int padre = get<1>(aux);
		if(orden[nod] == -1){
			pred[nod] = padre;
			orden[nod] = next;
			next++;
			Nodo* nodin = nodos[nod];
			vector<Eje *> ejesNodin = nodin -> ejejes;
			//agregamos los ejes que estan conectados
			for(unsigned int i=0 ; i<ejesNodin.size(); i++){
				Eje * ejeaux = ejesNodin[i];
				Nodo * nodoaux = ejeaux ->dameElOtroNodoPorfa(nodin);
				int acomp = nodoaux -> indice;
				//si ya lo tagee o estoy bajando a una instancia invalida, reconstruir una pared
				if(orden[acomp] != -1 || nodoaux->nivel < nodin->nivel) continue;
				// estamos en el mismo nivel pero estoy rompiendo una pared, tendria que subir de nivel
				if(nodoaux -> nivel == nodin -> nivel &&  nodoaux -> esPared) continue;
				tuple<int, int> arist(acomp, nod);
				list.push(arist);
			}
		}
	}


	int x= nodos.size()-1;
	int res=2;
	int aux = 0;

	while(aux < nodos.size()){
		x= pred[x];
		if(x == 0 || x == -1) break;
		res++;
		aux++;
	}
	if(x==-1){
		return -1;
	}
	else{
		return res;
	}
}

int Solucion(vector<Nodo *>& nodos, vector<Eje *>& ejes, int p){
	int res=p*2*nodos.size();
	int nores = res;
	for(int i=0; i<=p; i++){

		int respar=Bfs(nodos);
		if(p != i) clonarUltimoNivel(nodos,ejes);
		if(respar< res && respar!=-1){
			res=respar;
		}
	}
	if(res==nores){
		res=-1;
	}
	return res;
}
uint64_t rdtsc() {
  unsigned int lo, hi;
  __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
  return ((uint64_t)hi << 32) | lo;
}
int main(int argc, char *argv[]) {
	std::vector<Nodo *> nodos;
	std::vector<Eje *> ejes;
	int repeticiones=10;
	uint64_t begin, end, elapsed_secs, elapsed_final;
	//for (size_t f = 5; f < 18; f++) {
	//	for (size_t c = 5; c <f+1 ; c++) {
	int f,c,p;
	f=20;
	c=20;
	p=50;
			for (size_t i = p; i < (f-2)*(c-2) -1; i++) {
				elapsed_secs = 0;
				for (size_t k = 0; k < repeticiones; k++) {
					int paredes= parsearInput(nodos,ejes,f,c,p,p+i);
					begin = rdtsc();
					Solucion(nodos,ejes,paredes);
					end = rdtsc();
					elapsed_secs += end - begin;
					ejes.clear();
					nodos.clear();
				}
				elapsed_final = elapsed_secs / repeticiones;
				cout<<f<<'|'<<c<<'|'<<p+i<<'|'<<elapsed_final<<endl;
			}
	//	}
	//}

	//for (size_t i = 0; i < paredes; i++) {
	/* code */
	/* code */
	//cout<<"clono"<<endl;
	//clonarUltimoNivel(nodos,ejes);
	//}

	//Imprimir(nodos);
	return 0;
}
