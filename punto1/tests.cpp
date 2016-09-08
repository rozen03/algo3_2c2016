#include "ej1.cpp"
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
			for(int x = 0; x<=rep; x++){
				long solpar;
				list<int> arq;
				list<int> can;
				lecturaDatos(ts, arq, can);
				auto start = ya();
				valor = solucion(arq, can);
				auto end = ya();
				solpar = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
				sol = sol +solpar;
			}
			res<<" " << sol/rep<<" & " <<valor<<"\n";
			cout<< "termine " << ts<<endl;
		}
	}	
}



int main(){
	test(100000);
	
return 0;	
	}
