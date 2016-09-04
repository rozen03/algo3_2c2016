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

void testPesoMoch(int rep){
	ofstream res("resultadosPesoMoch.txt");

	string t ="PesoMoch2-5-5.txt";
	std:: ofstream ts(t);
	ts<< "3 50 \n";
	ts<<"2 5 5\n";	

	string a="PesoMoch10-5.txt";
	std::ofstream as(a);	
	as<< "2 50 \n";
	as<<"10 5\n";

	string b="PesoMoch2-25.txt";
	std::ofstream bs(b);
	bs<< "2 50 \n";
	bs<<"2 25\n";			
	
	string c="PesoMoch50.txt";
	std::ofstream cs(c);
	cs<< "1 50 \n";
	cs<<"50 \n"; 

	srand(time(NULL));
	for(int j=0; j<50;j++){
		int c=1;
		int p= rand()%5+1;
		int v= rand()%10000000+1;
		ts<< c <<" "<< p<< " "<< v <<endl;
		as<< c <<" "<< p<< " "<< v <<endl;
		bs<< c <<" "<< p<< " "<< v <<endl;
		cs<< c <<" "<< p<< " "<< v <<endl;	
	}
	ts.close();
	as.close();
	bs.close();
	cs.close();
	res<<"2-5-5 \n";
	int sol= 0;
	for(int i = 0; i <= rep; i++){
		int solpar;
		auto start = ya();
		solucion(t);
		auto end = ya();
		solpar = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() / rep;
		sol = sol +solpar;
		}
	res<<sol<<" & \n";
	ts.close();
	res<<"10-5\n";
	sol= 0;
	for(int i = 0; i <= rep; i++){
		int solpar;
		auto start = ya();
		solucion(a);
		auto end = ya();
		solpar = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() / rep;
		sol = sol +solpar;
		}
	res<<sol<<" & \n";
	as.close();
	res<<"2-25\n";
	sol= 0;
	for(int i = 0; i <= rep; i++){
		int solpar;
		auto start = ya();
		solucion(b);
		auto end = ya();
		solpar = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() / rep;
		sol = sol +solpar;
		}
	res<<sol<<" & \n";
	bs.close();
	res<<"50\n";
	sol= 0;
	for(int i = 0; i <= rep; i++){
		int solpar;
		auto start = ya();
		solucion(c);
		auto end = ya();
		solpar = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() / rep;
		sol = sol +solpar;
		}
	res<<sol<<" & \n";
	cs.close();
	res.close();
	
}

int main(){
	testObjAleatorios(1000);
	testObjPesoRango(1000);
	testObjMejorCaso(1000);
	testPesoMoch(1000);
return 0;
}
