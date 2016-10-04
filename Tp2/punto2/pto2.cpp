#include "dsu.cpp"
#include "../estructuras.h"
#include <queue>
#include <fstream>
#include "../eje.h"

using namespace std;

unsigned int kruskal(priority_queue<Eje *> Ejes, unsigned int n){
	while(!Ejes.empty()){
		cout<< "entre al 1er while"<<endl;
		Eje * t= Ejes.top();
		cout<<t->peso<< endl;
		Ejes.pop();
		}
	cout<<"kruskal"<<endl;
	unsigned int res=0;
	cout<< "int"<<endl;
	dsu conj;
	cout<< "int"<<endl;
	conj.init(n);
	cout<<"init"<<endl;
	while(!Ejes.empty()){
		cout<<"entre al 2do while"<<endl;
		Eje e= *Ejes.top();
		Ejes.pop();
		//ver como se llamas los Nodos extremos del Eje podrian ser inicio y fin?!
		Nodo * nUno=e.dameNodo();
		Nodo * nDos=e.dameElOtroNodoPorfa(nUno);
		cout<<"me rompi"<<endl;
		unsigned int nu = nUno->indice;
		unsigned int nd = nDos->indice;
		if(conj.find(nu) != conj.find(nd)){
			cout<<"entre al if del while"<<endl;
			res=+e.damePeso();
			conj.unir(nu, nd);
		}
		cout<<"sali del while"<<endl;
	return res;
	}

}


int solu( unsigned int n, vector<Eje *> ejes){
cout <<"entre a la solu"<< endl
	priority_queue<Eje *> aristas;
	for(unsigned int j=0; j< ejes.size(); j++){
		cout<<ejes[j]->peso<<endl;
		aristas.push(ejes[j]);
	}
	cout<<"sali del maldito for"<< endl;
	int res= kruskal(aristas,n);
	return res;
}

int main(int agrc, char *argv[]){
	cout<< "entre al puto main" <<endl;
	vector<Nodo *> nodos;
	vector<Eje *> ejes;
	cout<<"hola"<<endl;
	parsearInput(nodos, ejes, 2);
	cout<< "sali de parsear inputos"<< endl;
	unsigned int n= nodos.size();
	solu(n, ejes);
	return 0;
}
