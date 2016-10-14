#include "ej1.cpp"
#include "ej1P.cpp"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>

#define ya chrono::high_resolution_clock::now

using namespace std;


void test(int rep){
	srand(time(NULL));
	ofstream res("solu1Test.txt");

		/* //Para Debugear casos particulares
		// int i = 3;
		// int j = 3;
		// string is = to_string(i);
		// string  js= to_string(j);
		// string ts="testArq"+is+"Can"+js+".txt";
		// ofstream input(ts);
		// input << i <<" "<< j<<"\n";
		// 	int v =1;
		// for(int l = 0; l < i; l++){
		// 	input << v<<" ";
		// 	v = v+1;
		// }
		// input<<"\n";
		// 	v =4;
		// for(int l = 0; l < j; l++){
		// 	input << v<<" ";
		// 	v = v+1;
		// }
		// input <<"\n";
		// input.close();
		// res<< "Arq"<<is<<"-Can"<<js;
		// long sol = 0;
		// int valor = -2;
		// for(int x = 0; x<=rep; x++){
		// 	long solpar;
		// 	list<long> arq;
		// 	list<long> can;
		// 	lecturaDatos(ts, arq, can);
		// 	auto start = ya();
		// 	valor = solucion(arq, can);
		// 	auto end = ya();
		// 	solpar = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
		// 	sol = sol +solpar;
		// }
		// res<<" " << sol/rep<<" & " <<valor<<"\n";
	*/	
	
	

	for(int i=0; i<6 ; i++){
		for(int j=0; j+i<=6; j++ ){
			if( i == 0 && j == 0) continue;
			string is = to_string(i);
			string  js= to_string(j);
			string ts="testArq"+is+"Can"+js+".txt";
			ofstream input(ts);
			input << i <<" "<< j<<"\n";
			for(int l = 0; l < i; l++){
				int v =rand()%20+1;
				input << v<<" ";
			}
			input<<"\n";
			for(int l = 0; l < j; l++){
				int v =rand()%20+1;
				input << v<<" ";
			}
			input <<"\n";
			input.close();
			res<< "Arq"<<is<<"-Can"<<js;
			long sol = 0;
			int valor = -2;
			long valorp = -2;
			long solp = 0;
			cerr<< "Arq"<<is<<"-Can"<<js;
			for(int x = 0; x<rep; x++){
				long solpar;
				long solparp;
				vector<int> arq;
				vector<int> can;
				lecturaDatos(ts, arq, can);
				cerr<<" Pase lectura Datos ";
				list<long> arqa;
				list<long> cana;
				//lecturaDatosP(ts, arqa, cana);
				auto start = ya();
				//valor = solucion(arq, can);
				auto end = ya();
				auto startp = ya();
				//valorp = solucionP(arqa, cana);
				auto endp = ya();
				solpar = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
				sol = sol +solpar;
				solparp = chrono::duration_cast<std::chrono::nanoseconds>(endp-startp).count();
				solp = solp +solparp; 
			}
			cerr<<"...Terminado"<<endl;
			res<<" " << sol/rep<<" & " <<valor<<"& el que anda & "<<solp/rep<<" & "<<valorp<<"\n";
			
			//cout<< "termine " << ts<<endl;
		}
	}	
}



int main(){
	test(1);
	
return 0;	
	}
