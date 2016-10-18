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
nodo	GimMasCercano(); //devuelve el  gimnasio mas cercano. Si devuelve 0 es porque no se le puede ganar
nodo	PokeParadaMasCercana(); //devuelve el id de la pokeparada mas cercana.
void	moverse(*nodo);//actualiza la posicion actual, y el recorrido, y elimina el nodo de vector correspondiente.
float	distancia(*nodo); //calcula la distancia desde la posicion actual hasta el nodo

int main(){
	//comienza en ALGUN LADO. Por ej; la primera pokeparada tambieeeeen fijarse si "es posible"
	/*
		ARMAR ESTA COSA
	*/
	nodo proxLugar;

	while(!Gimnasios.empty()){//mientras sigan existiendo gimnasios que no pasaron  
		proxLugar = GimMasCercano();
		if(proxGim==0){ //no le puedo ganar al gimnasio mas cercano
			proxLugar = PokeParadaMasCercana();
		}
		moverse(proxLugar);

	}


	//Devolver distanciaRecorrida y RecorridoActual
}


nodo GimMasCercano(){//AAAAA NO SE SI USAR PUNTEROS
	nodo min = 0;
	for (int i = 0; i < Gimnasios.size(); ++i){
		if(mochila.DameCapacidad()>=Gimnasios[i].damePociones()){//verifico que puedo vencer este gimnacio 
			if(min==0){
				min = Gimnasios[i];
			}
			else{
				if(distancia(min)>distancia(Gimnasios[i])){
					min = Gimnasios[i];		
				}
			}
		}
	}

	return min;

}

nodo PokeParadaMasCercana(){
	nodo min =0;

	for (int i = 0; i < PokeParadas.size(); ++i){
		if(min==0){
				min = PokeParadas[i];
			}
			else{
				if(distancia(min)>distancia(PokeParadas[i])){
					min = PokeParadas[i];		
				}
		}
	}
	return min;
}


float distancia(nodo f) {
	int x = xactual - f.CordenadaX();
	int y = xactual - f.CordenadaY();
	int pre = pow(x, 2) + pow(y, 2);
	return sqrt(pre); //esto NO devuelve un int....
}

void moverse(nodo& lugar){
	/*	To do: 
		Actualizar x e y
		eliminar del vector correspondiente el lugar al que voy
		actualizar recorrido actual y distancia actual
		vaciar/llenar la mochila
	*/

}