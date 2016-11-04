#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include "ej1.cpp"
#include "../estructuras.h"


#define ya chrono::high_resolution_clock::now

using namespace std;

void testCompConexas(int rep, int puedoRomper, int cantCompCon){
	ofstream res("resCompConexas.txt");
	int f=200;
	int c=200;

	for (int k = 1; k < cantCompCon; ++k){

		ofstream test("testCompConexas.txt");
		test<<f<<" "<<c<<" "<< puedoRomper<<"\n";
		int sol=0;
		for (int i = 1; i <= f; ++i){

			for (int j = 1; j <= c; ++j){
				if(j==2 && i==2) {test<<"o";}
				else{
					if(i==199 && j== 2){
						test<<"x";
					}
					else{
						if(((i==1 && j!= c ) || i==f )|| j==1 ){
							test<< "#";
						}
						else if (j==c){
							test<< "#"<<" \n";
						}
						else{
							if(200-j<=k+2){

								if (j%2==1){
									test<<".";
								}
								else{
									test<<"#";

								}

							}
							else{
								test<<".";
							}
						}
					}
				}

			}

		}
		test.close();

		vector<Nodo *> nodos;
		vector<Eje *> ejes;

		parsearAux(nodos, ejes, 2, "testCompConexas.txt");

		unsigned int n= nodos.size();
		for (int i = 0; i <= rep; ++i){
			int solpar;
			auto start= ya();
			Solucion(nodos, ejes, puedoRomper);
			auto end= ya();
			solpar = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() / rep;
			sol = sol +solpar;
		}
		res<<sol<<" \n";

	}
}

void testSoloFilas(int rep){
	int c=6;
	ofstream res("resSoloFilas.txt");
	for (int f =4; f <= 52; f=f+2){

		int sol=0;

		ofstream test("testSoloFilas.txt");
		test<<f <<" "<< c <<" "<< "0" <<" \n";
		for (int i = 1; i <= f; ++i){

			for (int j = 1; j <= c; ++j){
				if(j==2 && i==2){
					test<<"o";
				}
				else if(i==f-1 && j==c-1){
					test<<"x"
				}
				else{
					if(((i==1 && j!= c ) || i==f )|| j==1 ){
						test<< "#";
					}
					else if (j==c){
						test<< "#"<<" \n";
					}
					else{
						test<<".";
					}
				}
			}
		}
		test.close();

		vector<Nodo *> nodos;
		vector<Eje *> ejes;

		parsearAux(nodos, ejes, 2, "testSoloFilas.txt");

		unsigned int n= nodos.size();
		for (int i = 0; i <= rep; ++i){
			int solpar;
			auto start= ya();
			Solucion(nodos, ejes, 0);
			auto end= ya();
			solpar = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() / rep;
			sol = sol +solpar;
		}
		res<<sol<<" \n";

	}
}

void testSoloFilasConComp(int rep, int puedoRomper){
	int c=6;
	ofstream res("resSoloFilas.txt");
	for (int f =4; f <= 52; f=f+2){

		int sol=0;
		int cantCompCon= (f/2);
		for(int k=1; k<= cantCompCon; k++){
			ofstream test("testSoloFilasConComp.txt");
			test<<f <<" "<< c <<" "<< "0" <<" \n";
			for (int i = 1; i <= f; ++i){

				for (int j = 1; j <= c; ++j){
					if(j==2 && i==2) {test<<"o";}
					else{
						if(i==2 && j== c-1){
							test<<"x";
						}
						else{
							if(((i==1 && j!= c ) || i==f )|| j==1 ){
								test<< "#";
							}
							else if (j==c){
								test<< "#"<<" \n";
							}
							else{
								if(f-i<=k+2){

									if (i%2==1){
										test<<".";
									}
									else{
										test<<"#";

									}

								}
								else{
									test<<".";
								}
							}
						}
					}

				}

			}
			test.close();
		}

		vector<Nodo *> nodos;
		vector<Eje *> ejes;

		parsearAux(nodos, ejes, 2, "testSoloFilas.txt");

		unsigned int n= nodos.size();
		for (int i = 0; i <= rep; ++i){
			int solpar;
			auto start= ya();
			Solucion(nodos, ejes, puedoRomper);
			auto end= ya();
			solpar = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() / rep;
			sol = sol +solpar;
		}
		res<<sol<<" \n";

	}
}



void testSoloColumnas(int rep){
	int f= 4;
	ofstream res("resSoloColumnas.txt");
	for (int c = 10; c <= 250; c=c+10){

		int sol=0;

		ofstream test("testSoloColumnas.txt");
		test<<f <<" "<< c << " "<< "0"<< " \n";
		for (int i = 1; i <= f; ++i){

			for (int j = 1; j <= c; ++j){
				if(i==2 && j==2){
					test<<"o";
				}
				else if(i==f-1 && j==c-1){
					test<<"x";
				}
				else{

					if(((i==1 && j!= c ) || i==f )|| j==1 ){
						test<< "#";
					}
					else if (j==c){
						test<< "#"<<" \n";
					}
					else{
						test<<".";
					}
				}
			}
		}
		test.close();

		vector<Nodo *> nodos;
		vector<Eje *> ejes;

		parsearAux(nodos, ejes, 2, "testSoloColumnas.txt");

		unsigned int n= nodos.size();
		for (int i = 0; i <= rep; ++i){
			int solpar;
			auto start= ya();
			Solucion(nodos, ejes,0);
			auto end= ya();
			solpar = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() / rep;
			sol = sol +solpar;
		}
		res<<sol<<" \n";

	}

}

void testSoloColumnasConComp(int rep, int puedoRomper){
	int cf=6;
	ofstream res("resSoloFilas.txt");
	for (int c =4; f <= 52; f=f+2){

		int sol=0;
		int cantCompCon= (c/2);
		for(int k=1; k<= cantCompCon; k++){
			ofstream test("testSoloFilasConComp.txt");
			test<<f <<" "<< c <<" "<< "0" <<" \n";
			for (int i = 1; i <= f; ++i){

				for (int j = 1; j <= c; ++j){
					if(j==2 && i==2) {test<<"o";}
					else{
						if(i==f-1 && j== 2){
							test<<"x";
						}
						else{
							if(((i==1 && j!= c ) || i==f )|| j==1 ){
								test<< "#";
							}
							else if (j==c){
								test<< "#"<<" \n";
							}
							else{
								if(c-j<=k+2){

									if (j%2==1){
										test<<".";
									}
									else{
										test<<"#";

									}

								}
								else{
									test<<".";
								}
							}
						}
					}

				}

			}
			test.close();
		}

		vector<Nodo *> nodos;
		vector<Eje *> ejes;

		parsearAux(nodos, ejes, 2, "testSoloFilas.txt");

		unsigned int n= nodos.size();
		for (int i = 0; i <= rep; ++i){
			int solpar;
			auto start= ya();
			Solucion(nodos, ejes, puedoRomper);
			auto end= ya();
			solpar = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() / rep;
			sol = sol +solpar;
		}
		res<<sol<<" \n";

	}
}


int main(){

	testCompConexas(1,1,4);
	testSoloColumnas(1);
	testSoloFilasConComp();
	return 0;
}
