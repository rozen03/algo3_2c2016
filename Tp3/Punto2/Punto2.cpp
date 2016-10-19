#include "../clases.h"
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
typedef vector<Nodo > vnod;

//Variables
Mochila moch(0);
vint Recorrido;
float distanciaRecorrida;
vnod PokeParadas;
vnod Gimnasios;
int xactual;
int yactual;
//funciones
Nodo	GimMasCercano(); //devuelve el  gimnasio mas cercano. Si devuelve 0 es porque no se le puede ganar
Nodo	PokeParadaMasCercana(); //devuelve el id de la pokeparada mas cercana.
void	moverse(*Nodo);//actualiza la posicion actual, y el recorrido, y elimina el Nodo de vector correspondiente.
float	dist(*Nodo); //calcula la distancia desde la posicion actual hasta el Nodo

int main(){
	//comienza en ALGUN LADO. Por ej; la primera pokeparada tambieeeeen fijarse si "es posible"
	/*
		ARMAR ESTA COSA
	*/
	Nodo* proxLugar=0;

	while(!Gimnasios.empty()){//mientras sigan existiendo gimnasios que no pasaron  
		proxLugar = GimMasCercano();
		if(proxGim==0){ //no le puedo ganar al gimnasio mas cercano
			proxLugar = PokeParadaMasCercana();
		}
		moverse(proxLugar);

	}


	//Devolver distanciaRecorrida y RecorridoActual
}


Nodo GimMasCercano(){//AAAAA NO SE SI USAR PUNTEROS
	Nodo min = 0;
	for (int i = 0; i < Gimnasios.size(); ++i){
		if(moch.DamePeso()>=Gimnasios[i].damePociones()){//verifico que puedo vencer este gimnacio 
			if(min==0){
				min = $Gimnasios[i];
			}
			else{
				if(dist(min)>dist(Gimnasios[i])){
					min = &Gimnasios[i];		
				}
			}
		}
	}

	return min;

}

Nodo* PokeParadaMasCercana(){
	Nodo* min =0;

	for (int i = 0; i < PokeParadas.size(); ++i){
		if(min==0){
				min = &PokeParadas[i];
			}
			else{
				if(dist(min)>dist(PokeParadas[i])){
					min = &PokeParadas[i];		
				}
		}
	}
	return min;
}


float dist(Nodo* f) {
	int x = xactual - f<-CordenadaX();
	int y = xactual - f<-CordenadaY();
	int pre = pow(x, 2) + pow(y, 2);
	return sqrt(pre); //esto NO devuelve un int....
}

void moverse(Nodo & lugar){
	
	/*	Lo que hace esta funcion: 
		Actualizar x e y
		eliminar del vector correspondiente el lugar al que voy
		actualizar recorrido actual y distancia actual
		vaciar/llenar la mochila
	*/

	nuevo = lugar; //copio el Nodo
	
	//elimino el Nodo de la lista correspondiente
	if(lugar.EsGim()){
		Gimnasios.erase(lugar);
	}
	else {
		PokeParadas.erase(lugar);	
	}

	//lleno/vacio la mochila
	moch.usarMochila(nuevo.damePociones());

	//lo agrego al recorrido  y la distancia que estoy haciendo
	Recorrido.push_back(nuevo);
	distanciaRecorrida =+ distancia(nuevo);

	//actualizo x e y
	xactual = nuevo.CordenadaX();
	yactual = nuevo.CordenadaY();


	


}