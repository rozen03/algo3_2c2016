#include "clases.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <set>
#include <tuple>
#include <utility>
#include <limits>

using namespace std;

//Statics
static int MAX = numeric_limits<int>::max();

//Tipos
typedef vector<int> vint;
typedef vector<nodo > vnod;

//Statics
static int MAX = numeric_limits<int>::max();

//variables globales
int MinGlobal;
int MinActual;
vint RecorridoGlobal;
vint RecorridoActual;
vnod PokeParadas;
vnod Gimnasios;
int GimRecorridos;
Mochila mochila;


//declaracion de funciones
void BT();
void LecturaDeDatos();
void voyPP();
void voyGym(); 
bool puedoIrG();
bool puedoIrPP();
int distancia();


//funciones

int main(){
	MinGlobal = MAX;

}

void BT(){

	if (MinActual>= MinGlobal || GimRecorridos == Gimnasios.size()){
		return;
	}

	for (int i = 0; i < Maximo(Gimnasios.size(), PokeParadas.size()) ; ++i){
			if(!RecorridoGlobal.size()){
				if(i<Gimnasios.size()){
					nodo gim = Gimnasios[i];
					if (puedoIrG(gim)){
						gim.Recorrer()=true;
						voyGym(gim);
						gim.Recorrer()=false;
					}
				}
			}
			if(i<PokeParadas.size()){
				nodo pp = PokeParadas[i];
				if(puedoIrPP()){
					pp.Recorrer()=true;
					voyPP(pp);
					pp.Recorrer()=false;
				}
			}
			
				
	}	
	return;
}



