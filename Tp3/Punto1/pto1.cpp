#include "clases.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <set>
#include <tuple>
#include <utility>
#include <limits>
#include <math>

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
	//Quiero cortar o en el caso de que ya hay una solucion mejor o cuando ya recorri todos los gimnasios.
	if (MinActual>= MinGlobal || GimRecorridos == Gimnasios.size()){
		return;
	}
 	//Voy A un gimnasio o a una pokeparada.
	for (int i = 0; i < Maximo(Gimnasios.size(), PokeParadas.size()) ; ++i){
			//esto elige de donde salimos
			if(RecorridoActual.empty()) {
				if(i<PokeParadas.size()){
				nodo pp = PokeParadas[i];
				//si es posible ir con el gimnasio, marco y voy y desmarco
					if(puedoIrPP(pp)){
						pp.Recorrer()=true;
						RecorridoActual.push_back(pp.Indice());
						voyPP(pp);
						pp.Recorrer()=false;
						RecorridoActual.pop_back();
					}
			 	}	
			}	


			if(i<Gimnasios.size()){
				nodo gim = Gimnasios[i];
				//si es posible ir con el gimnasio, marco y voy y desmarco
				if (puedoIrG(gim)){
					gim.Recorrer()=true;

					voyGym(gim);
					gim.Recorrer()=false;
				}
			}
			//Voy a pokeparadas
			if(i<PokeParadas.size()){
				nodo pp = PokeParadas[i];
				//si es posible ir a pokeparada, marco y voy y desmarco
				if(puedoIrPP(pp)){
					voyPP(pp);
				}
			}
			
				
	}	
	return;
}

bool puedoIrPP( nodo p){
	return !mochila.EstaLLena() && (p.Recorrido() == false);
}

bool puedoIrG(nodo p){
	return mochila.DamePeso() >= -(p.DamePociones()) && (p.Recorrido() == false);
}

int distancia(nodo o, nodo f) {
	int x = o.CordenadaX() - f.CordenadaX();
	int y = o.CordenadaY() - f.CordenadaY();
	int pre = pow(x, 2) + pow(y, 2);
	return sqrt(pre);
}


void voyPP(nodo p) {
	pp.Recorrer()=true;
	nodo origen = BuscarNodo(RecorridoActual.back());
	int dist = Distancia(origen, p)
	MinActual += dist;
	RecorridoActual.push_back(p.Indice());
	int pociones = p.DamePociones();
	mochila.usarMochila(pociones);
	BT();
	MinActual -= dist;
	RecorridoActual.pop_back();
	pp.Recorrer()=false;
	RecorridoActual.push_back(p.Indice());
	mochila.usarMochila(-pociones);
}

void voyGym(nodo g) {
	pp.Recorrer()=true;
	nodo origen = BuscarNodo(RecorridoActual.back());
	int dist = Distancia(origen, p)
	MinActual += dist;
	RecorridoActual.push_back(p.Indice());
	BT();
	MinActual -= dist;
	RecorridoActual.pop_back();
	pp.Recorrer()=false;
	RecorridoActual.push_back(p.Indice());

} 