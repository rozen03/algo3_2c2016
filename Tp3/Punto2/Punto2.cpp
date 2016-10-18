#include "clases.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <set>
#include <tuple>
#include <utility>
#include <limits>

using namespace std;

//Tipos
typedef vector<int> vint;
typedef vector<nodo > vnod;

//Variables
Mochila mochila;
vint RecorridoActual;
int distanciaRecorrida
vnod PokeParadas;
vnod Gimnasios;
int xactual;
int yactual;
//funciones
nodo*	GimMasCercano(); //devuelve el  gimnasio mas cercano. Si devuelve 0 es porque no se le puede ganar
nodo*	PokeParadaMasCercana(); //devuelve el id de la pokeparada mas cercana.
void	moverse(*nodo);//actualiza la posicion actual, y el recorrido

int main(){
	//comienza en ALGUN LADO. Por ej; la primera pokeparada
	/*
		ARMAR ESTA COSA
	*/
	nodo* proxLugar;

	while(!Gimnasios.empty()){//mientras sigan existiendo gimnasios que no pasaron  
		proxLugar = GimMasCercano();
		if(proxGim==null){ //no le puedo ganar al gimnasio mas cercano
			proxLugar = PokeParadaMasCercana();
		}


	}
}