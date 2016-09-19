#include "ej3.cpp" //ver q onda
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<chrono>

#define ya chrono::high_resolution_clock::now

using namespace std;

void testConexo1camino(int rep){
	ofstream res("Conexo1cam.txt");
	for(int j = 10; j<251; j+= 10){
		string js = to_string(j);
		srand(time(NULL));
		string ts = "test"+ js+"Conexo1cam.txt";
		std::ofstream test10obj(ts);
		test10obj << j<<" "<<j-1<< " \n";
		for ( int i = 1; i < j; i++) {
			int origen= i;
			int destino=i+1;
			int tiempo=rand()%10+1;
			test10obj<< origen<< " "<< destino<< " "<<tiempo << endl;
		}
		test10obj.close();
		res<< j <<' ';
		int sol= 0;
    int valor = -3;
    vector<vector<tuple<int,int> > > matriz;
  	vector<int> estaciones;
  	lecturaDatos(ts, matriz);
		for(int i = 0; i <= rep; i++){
			int solpar;
			auto start = ya();
			valor = caminoMinimo(matriz,estaciones);
			auto end = ya();
			solpar = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() / rep;
			sol = sol +solpar;
		}
		res<<sol<<" & "<< valor <<" \n";
	}
	res.close();
}

int main(){
testConexo1camino(1);

}
