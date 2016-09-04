#include "ej3.cpp" //ver q onda
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<chrono>

#define ya chrono::high_resolution_clock::now

using namespace std;

void testObjAleatorios(int rep){
	ofstream res("resultadoObjAl.txt");
	for(int j = 10; j<51; j+= 10){
		string js = to_string(j);
		srand(time(NULL));
		string ts = "test"+ js+"objAl.txt";
		std::ofstream test10obj(ts);
		test10obj << "1 "<< j<<" \n";
		test10obj << "20 \n";
		for ( int i = 0; i < j; i++) {
			int C= 1;
			int p=rand()%100+1;
			int v=rand()%10000000+1;
			test10obj<< C<< " "<< p<< " "<<v << endl;
		}
		test10obj.close();
		res<< j <<' ';
		int sol= 0;
		for(int i = 0; i <= rep; i++){
			int solpar;
			auto start = ya();
			solucion(ts);
			auto end = ya();
			solpar = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() / rep;
			sol = sol +solpar;
		}
		res<<sol<<" & \n";
	}
	res.close();
}

void testObjPesoRango(int rep){
	ofstream res("resultadosObjPesoRango.txt");
	for(int j = 10; j<51; j+= 10){
		string js = to_string(j);
		srand(time(NULL));
		string ts = "test"+ js+"objPr.txt";
		std::ofstream test10obj (ts);
		test10obj << "1 "<< j<<" \n";
		test10obj << "20 \n";
		for ( int i = 0; i < j; i++) {
			int C= 1;
			int p=rand()%20+1;
			int v=rand()%10000000+1;
			test10obj<< C<< " "<< p<< " "<<v << endl;
		}
		test10obj.close();
		res<< j <<' ';
		int sol= 0;
		for(int i = 0; i <= rep; i++){
			int solpar;
			auto start = ya();
			solucion(ts);
			auto end = ya();
			solpar = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() / rep;
			sol = sol +solpar;
		}
		res<<sol<<" & \n";
	}
	res.close();
}

void testObjMejorCaso(int rep){
	ofstream res("resultadosoObjMejorCaso.txt");
	for(int j = 10; j<51; j+= 10){
		string js = to_string(j);
		srand(time(NULL));
		string ts = "test"+ js+"objPr.txt";
		std::ofstream test10obj(ts);
		test10obj << "1 "<< j<<" \n";
		test10obj << "20 \n";
		for ( int i = 0; i < j; i++) {
			int C= 1;
			int p=21;
			int v=rand()%10000000+1;
			test10obj<< C<< " "<< p<< " "<<v << endl;
		}
		test10obj.close();
		res<< j <<' ';
		int sol= 0;
		for(int i = 0; i <= rep; i++){
			int solpar;
			auto start = ya();
			solucion(ts);
			auto end = ya();
			solpar = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() / rep;
			sol = sol +solpar;
		}
		res<<sol<<" & \n";
	}
	res.close();
}

void testPesoMoch(int rep){//aca nos aseguramos que todos los objetos entren en la mochila mas chica, asi no varia dependiendo de los objetos que entrar
	/*
	 *quiero que dado cierto p me devuelva (p, tp1, tp2, tp3) donde tpi es tiempo promedio para i mochilas con p peso como producto.
	 * me gustaria que no sea un producto trivial p*1*1 o p*1 a no ser que p sea 1, entonces si interesa... creo esto interesa?-> p/2*2*1
	 */
	 vector<int> d(3);
	//ofstream res(
}

int main(){
	testObjAleatorios(1000);
	testObjPesoRango(100);
	testObjMejorCaso(1000);
return 0;
}
