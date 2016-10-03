#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include "grafos.cpp"
#include "pto2.cpp"

using namespace std;

void testKn(int rep){
	ofstream res("Kn.txt");
	for(int i = 10; i<251; i += 10){
		vector<vector<int> > matriz;
		matriz = CrearConexo(i, (i-1)*(i-2))/i);
		long sol= 0;
		int valor = -3;
		for(int j= 0; j<=rep; j++){
			long solpar = 0;
			auto start = ya();
			valor = caminoMinimo(matriz, estaciones);
			auto end= ya();
			solpar = chrono::duration_cast<chrono::nanoseconds>(end-start).count()/rep;
			sol += solpar;
		}
		res<<i<<" & " <<sol<<" & "<<valor<<" \n";
	}
	res.close();
}

int test200ejes(int rep){
	ofstream res("Conexo200ejes.txt");
	for(int i = 22; i< 199; i += 6){
		vector<vector<tuple<int> > > matriz;
		matriz = CrearConexo(i, 200);
		long sol= 0;
		int valor = -3;
		for(int j= 0; j<=rep; j++){
			long solpar = 0;
			auto start = ya();
			valor = caminoMinimo(matriz, estaciones);
			auto end= ya();
			solpar = chrono::duration_cast<chrono::nanoseconds>(end-start).count()/rep;
			sol += solpar;
		}
		res<<i<<" & "<<sol<<" & "<< valor<<"sin optimizar, optimizado "<<valoropt<<" & "<<solopt<<" \n";
	}
	res.close();
}
