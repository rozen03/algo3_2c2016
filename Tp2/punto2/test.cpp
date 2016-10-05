#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include "pto2.cpp"
#include "../estructuras.h"

#define ya chrono::high_resolution_clock::now

using namespace std;



void parsearAux(vector<Nodo *> & nodos, vector<Eje *> & ejes,int ejercicio, string s){
  
  fstream test;  
  test.open(s);
  int f, c, p;
  test >> c >> f;
    if (ejercicio==1) {
    test >> p;
  }

  char aux;

  int indices[f - 2][c - 2];
  
  char matriz[f - 2][c - 2];
  unsigned int count = 0;
  unsigned int countEjes = 0;

  nodos.resize((f - 2) * (c - 2),NULL);
  ejes.resize((f - 2) * (c - 2)*4,NULL);
  unsigned int nodidex =0;
  
  for (int i = 0; i < f-2; i++) {

    for (int j = 0; j < c-2; j++) {
      indices[i][j] = -1;
      nodos[nodidex] = NULL;
      nodidex++;
        matriz[i][j]= 'a';
    }
  }
  for (int register j = 0; j < c; j++) {
    for (int register i = 0; i < f; i++) {
        test >> aux;
        if (i == 0 || i == f - 1)
          continue;
        if (j == 0 || j == c - 1)
          continue;
        matriz[i - 1][j - 1] =aux;
      }
    }

  for (size_t i = 0; i < f -2; i++) {
    for (size_t j = 0; j <c -2; j++) {
      aux = matriz[i][j];
      if (esPiso(aux)) {
        int index;
        int derecha, abajo;
        // Tomo/inicializo el nodo
        verNodo(i,j,index);
        // Abajo
        if (j < c - 3) {
          aux = matriz[i][j+1];
          if (esPiso(aux)) {
            verNodo(i,j+1,derecha);
            Eje *e = new Eje(countEjes, 0, nodos[index], nodos[derecha]);
            nodos[index]->ejes.push(e);
            nodos[derecha]->ejes.push(e);
            ejes[countEjes]=e;
            countEjes++;
          }
        }
        // derecha
        if (i < f - 3) {
          aux = matriz[i + 1][j];
          if (esPiso(aux)) {
            verNodo(i+1,j,abajo);
            Eje *e = new Eje(countEjes, 0, nodos[index], nodos[abajo]);
            nodos[index]->ejes.push(e);
            nodos[abajo]->ejes.push(e);
            ejes[countEjes]=e;
            countEjes++;
          }
        }
      } else if ((aux - '0' > -1) && (aux - '0' < 10)) {
        int peso = aux - '0';
        int arriba, abajo, izquierda, derecha;
        arriba = -1;
        abajo = -1;
        izquierda = -1;
        derecha = -1;
        // A la derecha
        if (j < c - 3) {
          aux = matriz[i][j + 1];
          if (esPiso(aux)) {
            verNodo(i,j+1,derecha);
          }
        }
        // Abajo
        if (i < f - 3) {
          aux = matriz[i + 1][j];
          if (esPiso(aux)) {
            verNodo(i+1,j,abajo);
          }
        }
        // A la izquierda
        if (0 < j) {
          aux = matriz[i][j - 1];
          if (esPiso(aux)) {
            verNodo(i,j-1,izquierda)
          }
        }
        // arriba
        if (0 < i) {
          aux = matriz[i - 1][j];
          if (esPiso(aux)) {
            verNodo(i-1,j,arriba);
          }
        }
        // conecto los dos nodos
        int a, b;
        a = max(arriba, max(abajo, max(izquierda, derecha)));
        if (a == arriba) {
          b = max(abajo, max(izquierda, derecha));
        } else if (a == abajo) {
          b = max(arriba, max(izquierda, derecha));
        } else if (a == izquierda) {
          b = max(abajo, max(arriba, derecha));
        } else {
          b = max(abajo, max(izquierda, arriba));
        }
        Eje *e = new Eje(countEjes, peso, nodos[a], nodos[b]);
        nodos[a]->ejes.push(e);
        nodos[b]->ejes.push(e);
        ejes[countEjes]=e;
        countEjes++;

      }else if(ejercicio==1 && aux=='#'){
        int arriba, abajo, izquierda, derecha,index;
        // Tomo/inicializo el nodo
        verNodo(i,j,index);
        arriba = -1;
        abajo = -1;
        izquierda = -1;
        derecha = -1;
        // A la derecha
        if (j < c - 3) {
          aux = matriz[i][j + 1];
          if (esPiso(aux)) {
            verNodo(i,j+1,derecha);
          }
        }
        // Abajo
        if (i < f - 3) {
          aux = matriz[i + 1][j];
          if (esPiso(aux)) {
            verNodo(i+1,j,abajo);
          }
        }
        // A la izquierda
        if (0 < j) {
          aux = matriz[i][j - 1];
          if (esPiso(aux)) {
            verNodo(i,j-1,izquierda)
          }
        }
        // arriba
        if (0 < i) {
          aux = matriz[i - 1][j];
          if (esPiso(aux)) {
            verNodo(i-1,j,arriba);
          }
        }
      }
    }
  }
  nodos.resize(count);
  ejes.resize(countEjes);
  test.close();
}



void testSinParedes(int rep){
	
	ofstream res("resSinParedes.txt");
	for (int f = 3; f <= 1000; f=f+10){
		
		int sol=0;

		ofstream test("testSinParedes.txt");
		test<<f <<" "<< f << " \n";
		for (int i = 1; i <= f; ++i){
			
			for (int j = 1; j <= f; ++j){
				
				if(((i==1 && j!= f ) || i==f )|| j==1 ){
					test<< "#";
				}
				else if (j==f){
					test<< "#"<<" \n";
				}
				else{
					test<<".";
				}
			}
		}
		test.close();
		vector<Nodo *> nodos;
		vector<Eje *> ejes;
		
		parsearAux(nodos, ejes, 2, "testSinParedes.txt");

		unsigned int n= nodos.size();		
		for (int i = 0; i <= rep; ++i){
			int solpar;
			auto start= ya();
			solu(n, ejes);	
			auto end= ya();
			solpar = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() / rep;
			sol = sol +solpar;
		}
		res<<sol<<" \n"; 
		
	}	
	
}

void testSoloFilas(int rep){
	int c=4;
	ofstream res("resSoloFilas.txt");
	for (int f = 3; f <= 1000; f=f+10){
		
		int sol=0;

		ofstream test("testSoloFilas.txt");
		test<<f <<" "<< c << " \n";
		for (int i = 1; i <= f; ++i){
			
			for (int j = 1; j <= c; ++j){
				
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
		test.close();
		vector<Nodo *> nodos;
		vector<Eje *> ejes;
		
		parsearAux(nodos, ejes, 2, "testSoloFilas.txt");

		unsigned int n= nodos.size();		
		for (int i = 0; i <= rep; ++i){
			int solpar;
			auto start= ya();
			solu(n, ejes);	
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
	for (int c = 3; c <= 1000; c=c+10){
		
		int sol=0;

		ofstream test("testSoloColumnas.txt");
		test<<f <<" "<< c << " \n";
		for (int i = 1; i <= f; ++i){
			
			for (int j = 1; j <= c; ++j){
				
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
		test.close();
		vector<Nodo *> nodos;
		vector<Eje *> ejes;
		
		parsearAux(nodos, ejes, 2, "testSoloColumnas.txt");

		unsigned int n= nodos.size();		
		for (int i = 0; i <= rep; ++i){
			int solpar;
			auto start= ya();
			solu(n, ejes);	
			auto end= ya();
			solpar = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() / rep;
			sol = sol +solpar;
		}
		res<<sol<<" \n"; 
		
	}

}

void testCompConexas(int rep){
	ofstream res("resCompConexas.txt");
	int f=31;
	int c=31;
	for (int k = 1; k < 31; ++k){
		int sol=0;
		ofstream test("testCompConexas.txt");
		test<<f<<" "<<c<<"\n";
		
		for (int i = 1; i <= f; ++i){

			for (int j = 1; j <= c; ++j){
				
				if(((i==1 && j!= c ) || i==f )|| j==1 ){
					test<< "#";
				}
				else if (j==c){
					test<< "#"<<" \n";
				}
				else{
					if(j<=k+2){
						
						if (j%2==0){
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
		test.close();
		vector<Nodo *> nodos;
		vector<Eje *> ejes;
		
		parsearAux(nodos, ejes, 2, "testCompConexas.txt");

		unsigned int n= nodos.size();		
		for (int i = 0; i <= rep; ++i){
			int solpar;
			auto start= ya();
			solu(n, ejes);	
			auto end= ya();
			solpar = chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() / rep;
			sol = sol +solpar;
		}
		res<<sol<<" \n"; 		
	}
}



int main(){

	testSinParedes(1000);
	testSoloFilas(1000);
	testSoloColumnas(1000);
	testCompConexas(1000);
	return 0;

}
