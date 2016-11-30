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

//Variables Estan todas en Clase.h

//vnod PokeParadas;
//vnod Gimnasios;
//Mochila moch;
int xactual;
int yactual;
vint Recorrido;
double distanciaRecorrida;


//funciones
Nodo *	GimMasCercano(); //devuelve el  gimnasio mas cercano. Si devuelve 0 es porque no se le puede ganar
Nodo *	PokeParadaMasCercana(); //devuelve el id de la pokeparada mas cercana.
void	moverse(Nodo * p);//actualiza la posicion actual, y el recorrido, y elimina el Nodo de vector correspondiente.
double	dist(Nodo * p); //calcula la distancia desde la posicion actual hasta el Nodo
void sacar(vnod &vect, int ind);
void goloso();
void elegirPrimero();
void solucion();
double pto2(vnod gim, vnod pp, Mochila moch, vint & sol);

/*
int main(){
	Lectura(Gimnasios, PokeParadas, moch);
	solucion();
	return 0;
}
*/
double pto2(vnod gim, vnod pp, Mochila mochil, vint & sol){
	//Primero reseteo las variables globales
	moch.CambiarCapacidad(mochil.DameCapacidad());
	moch.Restaurar(0);
	Recorrido.clear();
	distanciaRecorrida = 0;
	PokeParadas = pp;
	Gimnasios = gim;
	xactual = 0;
	yactual = 0;

	//despues llamo a lo que seria solucion, pero sin los couts molestos
	elegirPrimero();
	goloso();
	sol = Recorrido;
	return distanciaRecorrida;
}

void solucion(){
	elegirPrimero();
	goloso();

	cout <<distanciaRecorrida <<" ";
	cout <<Recorrido.size() <<" ";
	for(int i=0; i<Recorrido.size(); i++){
		cout <<  Recorrido[i] << " ";
	}
	cout <<endl;
}

void elegirPrimero(){
	//Eleccion de comienzo
	//Idea: recorro los gimnasios.
	//Si encuentro un gimnasio con fuerza =0 lo elijo
	//para todos los gimnasios con fuerza menor a 3, calculo
	// la pokeparada más cercana y empiezo por esa
	int minPoke =0; //lugar del vector
	double mindist = -1; //la distancia minima de la pokeparada
	for (int i = 0; i < Gimnasios.size(); ++i){
		if(Gimnasios[i].DamePociones()==0){
			xactual = Gimnasios[i].CordenadaX();
			yactual = Gimnasios[i].CordenadaY();
			Recorrido.push_back(Gimnasios[i].DameIndice());
			sacar(Gimnasios,Gimnasios[i].DameIndice());
			break;
		}
		else if(Gimnasios[i].DamePociones()<4){
			for(int j=0; j < PokeParadas.size(); j++){
				if(mindist==-1 || PokeParadas[j].Distancia(Gimnasios[i])< mindist ){
					minPoke=j;
					mindist= PokeParadas[j].Distancia(Gimnasios[i]);
				}

			}

		}
 	}
 	//MI CODIGO ES UN MOUNSTRO DE FRANKESTEIN D:
 	if(Recorrido.empty()){//si no encontre un gimnasio trivial
 		 //Si encontre al menos un gimansio facil, voy a la pokeparada mas cercana
 		 // Si no, voy a la primer pokeparada del vecor (es mejorable, pero no mucho)
 			xactual = PokeParadas[minPoke].CordenadaX();
			yactual = PokeParadas[minPoke].CordenadaY();
			Recorrido.push_back(PokeParadas[minPoke].DameIndice());
			moch.usarMochila(PokeParadas[minPoke].DamePociones());
			sacar(PokeParadas,PokeParadas[minPoke].DameIndice());




 	}

	//Fin de eleccion de comienzo
}


void goloso(){


	Nodo* proxLugar=0;

	while(!Gimnasios.empty()){//mientras sigan existiendo gimnasios que no pasaron
		//cout <<"Gimnasios"<< Gimnasios.size()<< endl;
		//cout <<"PokeParadaMasCercana"<< PokeParadaMasCercana.size()<< endl;
		proxLugar = GimMasCercano();
		if(proxLugar==0){ //no le puedo ganar al gimnasio mas cercano
			proxLugar = PokeParadaMasCercana();
		}
		if(proxLugar==0){
		distanciaRecorrida=-1;
		Recorrido.clear();
		break;
		}
		moverse(proxLugar);

	}

}


Nodo* GimMasCercano(){//AAAAA NO SE SI USAR PUNTEROS
	Nodo * min = 0;
	for (int i = 0; i < Gimnasios.size(); ++i){
		if(moch.DamePeso()>=-Gimnasios[i].DamePociones()){//verifico que puedo vencer este gimnacio
			if(min==0){
				min = &Gimnasios[i];
			}
			else{
				if(dist(min)>dist(&Gimnasios[i])){
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
				if(dist(min)>dist(&PokeParadas[i])){
					min = &PokeParadas[i];
				}
		}
	}
	return min;
}


double dist(Nodo* f) {
	int x = xactual - f->CordenadaX();
	int y = yactual - f->CordenadaY();
	int pre = pow(x, 2) + pow(y, 2);
	return sqrt(pre); //esto NO devuelve un int....
}

void moverse(Nodo * lugar){

	/*	Lo que hace esta funcion:
		Actualizar x e y
		eliminar del vector correspondiente el lugar al que voy
		actualizar recorrido actual y distancia actual
		vaciar/llenar la mochila
	*/
	//lleno/vacio la mochila
	moch.usarMochila(lugar->DamePociones());

	//lo agrego al recorrido  y la distancia que estoy haciendo
	if(!Recorrido.empty()){
		distanciaRecorrida += dist(lugar);
	}
	Recorrido.push_back(lugar->DameIndice());


	//actualizo x e y
	xactual = lugar->CordenadaX();
	yactual = lugar->CordenadaY();

	//elimino el Nodo de la lista correspondiente
	if(lugar->EsGim()){
		sacar(Gimnasios, lugar->DameIndice());
	}
	else {
		sacar(PokeParadas, lugar->DameIndice());
	}
}

void sacar(vnod &vector,int elem){

	for(int i = 0; i<vector.size();i++){
		int indiceAux = vector[i].DameIndice();
		if(indiceAux == elem){
			vector[i] = vector.back();
			vector.pop_back();

			return;
		}
	}
}
