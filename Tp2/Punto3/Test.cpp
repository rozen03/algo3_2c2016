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

void testNoConexo(int rep){
	ofstream res("NoConexo.txt");
	for(int j = 10; j<251; j+= 10){
		string js = to_string(j);
		srand(time(NULL));
		string ts = "test"+ js+"noConexo.txt";
		std::ofstream test10obj(ts);
		cerr<<ts<<"...";
		test10obj << j<<" "<<j-1<< " \n";
		for ( int i = 1; i < j; i++) {
			if(i == j-2)continue;//hay una estacion que no va a funcionarw
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
	    cerr<<"ok."<<endl;
	}
	res.close();
}	

void testConexoVariosCaminos(int rep){
	ofstream res("Conexomultcam.txt");
	for(int j = 10; j<251; j+= 10){
		string js = to_string(j);
		srand(time(NULL));
		string ts = "test"+ js+"Conexomultcam.txt";
		std::ofstream test10obj(ts);
		int b = rand()%100 + 1;
		int bs = b*j;
		test10obj << j<<" "<<bs<< " \n";
		for ( int i = 1; i < bs; i++) {
			int origen;
			int destino;
			int tiempo;
			if(i < j){
				origen= i;
				destino=i+1;
				tiempo= 1;
			}else{
				origen = rand()%10 +1;
				destino = rand()%10 + 1;
				tiempo = rand()%10 +2;
			}
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
 //testConexo1camino(1);
 //testNoConexo(1);
	testConexoVariosCaminos(1);
}
