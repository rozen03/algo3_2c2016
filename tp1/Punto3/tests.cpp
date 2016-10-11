#include "ej3.cpp" //ver q onda
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<chrono>

#define ya chrono::high_resolution_clock::now

using namespace std;
/*
void testPesoMejorCaso(int rep){
	ofstream res("resultadosoPesoMejorCaso.txt");
	for(int j = 2; j<51; j+= 2){
		string js = to_string(j);
		srand(time(NULL));
		string ts = "test"+ js+"PesoMca.txt";
		std::ofstream test10obj(ts);
		test10obj << "1 50 \n";
		test10obj << j<< "\n";
		for ( int i = 0; i < 50; i++) {
			int C= 1;
			int p=51;
			int v=rand()%10000000+1;
			test10obj<< C<< " "<< p<< " "<<v << endl;
		}
		test10obj.close();
		res<< j <<' ';
		int sol= 0;
		int valorar;
		for(int i = 0; i <= rep; i++){
			int solpar;
			vector<Mochila> mochilas;
			vector<Tesoro> cofre;
			lecturaDatosAux(ts, mochilas,cofre);
			auto start = ya();
			valorar = solucion(mochilas, cofre);
			auto end = ya();
			solpar = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() / rep;
			sol = sol +solpar;
		}
		res<<sol<<" & "<<valorar<<"\n";
	}
	res.close();
}
*/
void testObjAleatorios(int rep){
	ofstream res("resultadoObjAl.txt");
	for(int j = 2; j<51; j+= 2){
		string js = to_string(j);
		srand(time(NULL));
		string ts = "test"+ js+"objAl.txt";
		std::ofstream test10obj(ts);
		test10obj << "1 "<< j<<" \n";
		test10obj << "50 \n";
		for ( int i = 0; i < j; i++) {
			int C= 1;
			int p=rand()%100+1;
			int v=rand()%10000000+1;
			test10obj<< C<< " "<< p<< " "<<v << endl;
		}
		test10obj.close();
		res<< j <<' ';
		int sol= 0;
		int valorar = -1;
		for(int i = 0; i <= rep; i++){
			int solpar;
			vector<Mochila> mochilas;
			vector<Tesoro> cofre;
			lecturaDatosAux(ts, mochilas,cofre);
			auto start = ya();
			valorar = solucion(mochilas, cofre);
			auto end = ya();
			solpar = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() / rep;
			sol = sol +solpar;
		}
		res<<j<<" & "<<sol<<" & \n";
	}
	res.close();
}
/*
void testObjPesoRango(int rep){
	ofstream res("resultadosObjPesoRango.txt");
	for(int j = 2; j<51; j+= 2){
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
		res<<" j "<<sol<<" & \n";
	}
	res.close();
}

void testObjMejorCaso(int rep){
	ofstream res("resultadosoObjMejorCaso.txt");
	for(int j = 2; j<51; j+= 2){
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
		res<<j<<" & " <<sol<<" & \n";
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

void testCantMoch(int rep){
	ofstream res("resultadoCantMoch.txt");
	for(int j = 1; j < 4; j++) {
		string js = to_string(j);
		srand(time(NULL));
		string ts = "test"+ js+"CantMoch.txt";
		std::ofstream test(ts);
		test << j <<" "<< 50<<" \n";
		if (j==1) {
			test<<"50 \n";
		}
		else{
			if (j==2) {
				test<<"50 50 \n";
			}
				else{
					test<<"50 50 50 \n";
				}
			}
		for ( int i = 0; i < 50; i++) {
			int C= 1;
			int p=rand()%100+1;
			int v=rand()%10000000+1;
			test<< C<< " "<< p<< " "<<v << endl;
		}
		test.close();
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
		res<< j <<" & "<<sol<<" & \n";
	}
res.close();
}

void testMochDistPeso(int rep){
	ofstream res("soluMochDistPeso.txt");
	for(int j = 2; j<51; j+= 2){
		string js = to_string(j);
		srand(time(NULL));
		string ts = "test"+ js+"MochDistPeso.txt";
		std::ofstream test(ts);
		test << "1 "<< 50<<" \n";
		test << j<< " \n";
		for ( int i = 0; i < 50; i++) {
			int C= 1;
			int p=rand()%100+1;
			int v=rand()%10000000+1;
			test<< C<< " "<< p<< " "<<v << endl;
		}
		test.close();
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
		res<<j<<" & "<<sol<<" & \n";
	}
	res.close();

}
*/

void testMismoPesoPor1(int rep){
	ofstream res("soluMismoPesoPor1.txt");
	for(int j = 2; j<51; j+= 2){
		string js = to_string(j);
		srand(time(NULL));
		string ts = "testMochDistPeso1Moch.txt";
		string ta = "testMochDistPeso2Moch.txt";
		string tb = "testMochDistPeso3Moch.txt";
		std::ofstream test(ts);
		ofstream testa(ta);
		ofstream testb(tb);
		test << "1 "<< 50<<" \n";
		testa<<"2 50\n";
		testb<<"3 50\n";
		testa<<"1 "<<j<<"\n";
		testb<<"1 1 "<<j<<"\n";
		test << j<< " \n";
		for ( int i = 0; i < 50; i++) {
			int C= 1;
			int p=rand()%100+1;
			int v=rand()%10000000+1;
			test<< C<< " "<< p<< " "<<v << endl;
			testa<< C<< " "<< p<< " "<<v << endl;
			testb<< C<< " "<< p<< " "<<v << endl;
		}
		test.close();
		res<< j <<' ';
		long sol= 0;
		long sola = 0;
		long solb = 0;
		for(int i = 0; i <= rep; i++){
			long solpar;
			long solpara;
			long solparb;
			vector<Mochila> mochilas;
			vector<Tesoro> cofre;
			lecturaDatosAux(ts,mochilas,cofre);			
			vector<Mochila> mochilasa;
			vector<Tesoro> cofrea;
			lecturaDatosAux(ta,mochilasa,cofrea);
			vector<Mochila> mochilasb;
			vector<Tesoro> cofreb;
			lecturaDatosAux(tb,mochilasb,cofreb);			
			auto start = ya();
			solucion(mochilas, cofres);
			auto end = ya();			
			auto starta = ya();
			solucion(mochilasa, cofresa);
			auto enda = ya();			
			auto startb = ya();
			solucion(mochilasb, cofresb);
			auto endb = ya();
			solpar = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() / rep;
			solpara = chrono::duration_cast<std::chrono::nanoseconds>(enda-starta).count() / rep;
			solparb = chrono::duration_cast<std::chrono::nanoseconds>(endb-startb).count() / rep;
			sol = sol +solpar;
			sola = sola +solpara;
			solb = solb +solparb;
		}
		res<< j <<" & " <<sol<<" & "<<sola<<" & "<<solb<<"\n";
	}
	res.close();
}

int main(){
	//testObjAleatorios(1);
	//testObjPesoRango(1000);
	//testObjMejorCaso(1000);
	//testPesoMoch(1000);
	//testCantMoch(1000);
	//testPesoMejorCaso(1);
	//testMochDistPeso(1000);
	//testMismoPesoPor1(1000);
return 0;
}
