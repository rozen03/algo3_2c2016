#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>//reverse
using namespace std;
/*
 Podemos suponer que hay una via entre cada estacion, osea no hay dos vias con el mismo origen y destino?
 * [origen][destino]
 * (x,y) x es el tiempo e y es el predecesor.

 busca la tupla que tenga el valor minimo(sin contar el -1) en el primer elemento
 de la tupla y devuelve la posicion. solo busca en las posiciones que estan en nodos.
 */
int buscarMin(const vector<int>& nodos, const vector<tuple<int, int> >& filaAdy){//O(nodos.size())
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
void sacar(vector<int>& ls, int valor){//O(ls.size())
	int pos;
	for(unsigned int i = 0; i< ls.size();i++){
		if(ls[i]== valor){
			pos = i;
			break;
		}
	}
	ls[pos] = ls[ls.size()-1];
	ls.pop_back();
}

//-1 implica que no son vecinos, y un numero naturla mayor a cero indica el peso del pasar por ahi
//este frena cuando encuentra el minimo en n.
int caminoMinimoOpt(vector<vector<tuple<int,int> > >& matAdy, vector<int>& estaciones){
	unsigned int n = matAdy.size() -  1;
	vector<int> nodosSeguros;
	nodosSeguros.push_back(1);
	vector<int> nodos;
	for(unsigned int i = 2;i<= n;i++) nodos.push_back(i);//O(n)
	while(nodosSeguros.size() != n){//while se hace n veces
		int nodomin;
		nodomin = buscarMin(nodos, matAdy[1]);//O(nodos.size())  **1**
		//que la estacion 1 no este conectada a ninguna, de las que todavia no calculo el minimo
		//si es n entonces ya no tengo por que actualizar otros nodos, ya que n estaria en la zona segura.
		if(nodomin == -1 || nodomin == n) break;
		nodosSeguros.push_back(nodomin);
		sacar(nodos, nodomin);//O(nodos.size())**2**
		for(unsigned int i = 0; i<nodos.size();i++){//O(nodos.size())**3**
			int pos = nodos[i];
			int longi = get<0>(matAdy[1][pos]);
			int longmin = get<0>(matAdy[1][nodomin]);
			int longimin = get<0>(matAdy[nodomin][pos]);
			if(longimin != -1){
				tuple<int, int> aux(longmin+longimin, nodomin);
				if(longi > longmin + longimin || longi == -1) matAdy[1][pos] = aux;
			}
		}
	}
	
	int tiempo = get<0>(matAdy[1][n]);
	int pred = n;
	while(pred != 1 && pred != 0){//O(n) como mucho tiene que ir a n estaciones
		estaciones.push_back(pred);
		pred = get<1>(matAdy[1][pred]);
	}
	estaciones.push_back(pred);
	std::reverse(estaciones.begin(), estaciones.end());
	return tiempo;
/*
 *tanto 1, 2, 3 son lo que pesan en el ciclo, el while es n^2 ya que 1,2,3 se hace n^2 de veces... es una sumatoria de gauss que es O(n^2) 
 * 
 *  
 */
}
//este calcula todos los minimos
int caminoMinimo(vector<vector<tuple<int,int> > >& matAdy, vector<int>& estaciones){
	unsigned int n = matAdy.size() -  1;
	vector<int> nodosSeguros;
	nodosSeguros.push_back(1);
	vector<int> nodos;
	for(unsigned int i = 2;i<= n;i++) nodos.push_back(i);//O(n)
	while(nodosSeguros.size() != n){//while se hace n veces
		int nodomin;
		nodomin = buscarMin(nodos, matAdy[1]);//O(nodos.size())  **1**
		//que la estacion 1 no este conectada a ninguna, de las que todavia no calculo el minimo
		//si es n entonces ya no tengo por que actualizar otros nodos, ya que n estaria en la zona segura.
		if(nodomin == -1) break;
		nodosSeguros.push_back(nodomin);
		sacar(nodos, nodomin);//O(nodos.size())**2**
		for(unsigned int i = 0; i<nodos.size();i++){//O(nodos.size())**3**
			int pos = nodos[i];
			int longi = get<0>(matAdy[1][pos]);
			int longmin = get<0>(matAdy[1][nodomin]);
			int longimin = get<0>(matAdy[nodomin][pos]);
			if(longimin != -1){
				tuple<int, int> aux(longmin+longimin, nodomin);
				if(longi > longmin + longimin || longi == -1) matAdy[1][pos] = aux;
			}
		}
	}
	
	int tiempo = get<0>(matAdy[1][n]);
	int pred = n;
	while(pred != 1 && pred != 0){//O(n) como mucho tiene que ir a n estaciones
		estaciones.push_back(pred);
		pred = get<1>(matAdy[1][pred]);
	}
	estaciones.push_back(pred);
	std::reverse(estaciones.begin(), estaciones.end());
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
		tuple<int, int> elem(tiempo, origen);
		if(pos == -1 || pos > tiempo) filaycolum[origen][destino] = elem;
	}
	matrizAdyacencia = filaycolum;
}
/*
int main(int argc, char *argv[]){
	vector<vector<tuple<int,int> > > matriz;
	string  input = argv[1];
	vector<int> estaciones;
	int sol = -1;
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

*/
