#include "dsu.cpp"
#include "../estructuras.h"
#include <queue>
#include <fstream>
#include "../eje.h"

using namespace std;

 int kruskal(priority_queue<Eje > Ejes, unsigned int n){
	;
	 int res=0;
	dsu conj(n);
	while(!Ejes.empty() ){
		
		Eje e= Ejes.top();
		cout<< e.damePeso()<< endl;
		Ejes.pop();

		//ver como se llamas los Nodos extremos del Eje podrian ser inicio y fin?!
		Nodo * nUno=e.dameNodo();
		Nodo * nDos=e.dameElOtroNodoPorfa(nUno);
		
		unsigned int nu = nUno->indice;
		unsigned int nd = nDos->indice;
		if(conj.find(nu) != conj.find(nd)){

			res= res + e.damePeso();
			
			conj.unir(nu, nd);
			}
		}
	
	int j=1;
	bool b=true;
	int e=conj.find(1);
	
	while(j<n && b){
		int h=conj.find(j);
		
		if(e!=h){
			
			b=false;
		}
		j++;
	}
	if (!b){
		res= -1;
	}
	
	return res;

}


int solu( unsigned int n, vector<Eje *> ejes){

	priority_queue<Eje> aristas;
	
	for(unsigned int j=0; j< ejes.size(); j++){
		
		aristas.push(*ejes[j]);
	}


	int res= kruskal(aristas,n);
	return res;
}

/*
int main(int agrc, char *argv[]){

	vector<Nodo *> nodos;
	vector<Eje *> ejes;

	parsearInput(nodos, ejes, 2);

	unsigned int n= nodos.size();
	solu(n, ejes);
	return 0;
}
*/


