#include "dsu.cpp"
#include "../estructuras.h"
#include <queue>
#include <fstream>
#include "../eje.h"

using namespace std;

 int kruskal(priority_queue<Eje > Ejes, unsigned int n){
	cout<<"kruskal"<<endl;
	 int res=0;
	dsu conj(n);
	while(!Ejes.empty() ){
		cout<<"entre al while"<<endl;
		Eje e= Ejes.top();
		cout<< e.damePeso()<< endl;
		Ejes.pop();

		//ver como se llamas los Nodos extremos del Eje podrian ser inicio y fin?!
		Nodo * nUno=e.dameNodo();
		Nodo * nDos=e.dameElOtroNodoPorfa(nUno);
		
		unsigned int nu = nUno->indice;
		unsigned int nd = nDos->indice;
		if(conj.find(nu) != conj.find(nd)){
			cout<<"entre al if del while"<<endl;
			cout<< "peso de la nueva arista es "<< e.damePeso()<< endl;
			res= res + e.damePeso();
			cout<< "res = "<<res <<endl;
			conj.unir(nu, nd);
			}
		}
	cout<<"sali del while"<<endl;
	int j=1;
	bool b=true;
	int e=conj.find(1);
	cout<< "padre es " << e <<endl;
	while(j<n && b){
		int h=conj.find(j);
		cout<< "lo comparo con "<< h << endl;
		if(e!=h){
			cout<<"entre al if"<<endl;
			b=false;
		}
		j++;
	}
	if (!b){
		res= -1;
	}
	cout<< "el resultado es "<< res << endl;
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


