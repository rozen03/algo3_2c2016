#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <tuple>

using namespace std;
/*
 Podemos suponer que hay una via entre cada estacion, osea no hay dos vias con el mismo origen y destino?
 * [origen][destino] 
 * (x,y) x es el tiempo e y es el predecesor.
 
 busca la tupla que tenga el valor minimo(sin contar el -1) en el primer elemento
 de la tupla y devuelve la posicion. solo busca en las posiciones que estan en nodos.
 */
int buscarMin(const vector<int>& nodos, const vector<tuple<int, int> >& filaAdy){
	int min = 1000 * filaAdy.size();/*
	como peor caso es que tenemos que recorrer las n estaciones y que todas pesen 1000, filaAdy es n+1 entonces min nunca va a ser un valor valido
	*/
	int sol = -1;
	for(unsigned int i = 0; i<nodos.size(); i++){
		int pos = nodos[i];
		int tiempo = get<0>(filaAdy[pos]);
		if(tiempo != -1 && min > tiempo){
			 min = tiempo;
			 sol = pos;
		 } 
	}
	return sol;
}

 //funcion que saca el elemento ls[pos]
void sacar(vector<int>& ls, int pos){//O(1)
	ls[pos] = ls[ls.size()-1];
	ls.pop_back();
}

//-1 implica que no son vecinos, y un numero naturla mayor a cero indica el peso del pasar por ahi

int caminoMinimo(vector<vector<tuple<int,int> > >& matAdy, vector<int>& estaciones){
	//creo que  i tiene que ir hasta n, acordate que matAdy es n+1
	int n = matAdy.size() -  1;
	vector<int> vertrec;
	vertrec.push_back(1);
	vector<int> nodos;
	for(int i = 2;i< n;i++) nodos.push_back(i);
	while(vertrec.size() != n){
		int nodomin;
		nodomin = buscarMin(nodos, matAdy[1]);
		//que la estacion 1 no este conectada a ninguna, de las que todavia no calculo el minimo.
		if(nodomin == -1) break; 
		vertrec.push_back(nodomin);
		sacar(nodos, nodomin);
		for(unsigned int i = 0; i<nodos.size();i++){
			int longppali = get<0>(matAdy[1][i]);
			int longppalmin = get<0>(matAdy[1][nodomin]);
			int longimin = get<0>(matAdy[nodomin][i]);
			if(longppali != -1){
				tuple<int, int> aux(longppalmin+longimin, nodomin);
				if(longppali > longppalmin + longimin) matAdy[1][i] = aux;
			}
		}
	}
	
	int tiempo = get<0>(matAdy[1][n]);
	int pred = get<1>(matAdy[1][n]);
	while(pred != 1 ||pred != 0){
		estaciones.push_back(pred);
		tiempo = tiempo + get<0>(matAdy[1][pred]);
		pred = get<1>(matAdy[1][pred]);
	}
	estaciones.push_back(pred);
	return tiempo;
	
}

void lecturaDatos(string input, vector<vector<tuple<int,int> > >& matrizAdyacencia){
	fstream ip;
	ip.open(input);
	int n;
	int m;
	ip>> n >>m;
	tuple<int,int> basura(-1,0);
	vector<tuple<int,int > > fila(n+1, basura);
	vector<vector<tuple<int,int> > > filaycolum(n+1,fila);
	
	for(int i = 0; i<m;i++){
		int origen;
		int destino;
		int tiempo;
		ip >> origen >> destino >> tiempo;
		int pos = get<0>(filaycolum[origen][destino]);
		tuple<int, int> elem(tiempo, 1);
		if(pos == -1 || pos > tiempo) filaycolum[origen][destino] = elem;
	}
	matrizAdyacencia = filaycolum;
}

int main(int argc, char *argv[]){
	vector<vector<tuple<int,int> > > matriz;
	string  input = argv[0];
	vector<int> estaciones;
	int sol;
	
	lecturaDatos(input, matriz);
	
	sol = caminoMinimo(matriz, estaciones);
	
	cout<<sol<<"\n";
	if(sol != -1){
		cout<< estaciones.size()<<"\n";
		for(unsigned int i = 0; i < estaciones.size(); i++) cout<<estaciones[i]<<" ";
	}
	cout<<endl;
	return 0;
}
