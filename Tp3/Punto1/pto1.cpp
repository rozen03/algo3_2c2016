#include "../clases.h"
#include <iostream>
#include <chrono>
#include <limits>


using namespace std;

//Statics
static int MAX = numeric_limits<int>::max();

//Tipos
typedef vector<int> vint;


//variables globales
float MinGlobal;
float MinActual;
vint RecorridoGlobal;
vint RecorridoActual;
vnod PokeParadas;
vnod Gimnasios;
int GimRecorridos;
Mochila moch(0);


//declaracion de funciones
void BT();
void voy(Nodo & p);
bool puedoIrG(Nodo & p);
bool puedoIrPP(Nodo & p);
Nodo & BuscarNodo(int n);
int Maximo(int a, int b);


//funciones

int main(){
	MinGlobal = MAX;
	MinActual=0;
	Lectura(Gimnasios,PokeParadas,moch);
	BT();
	cout<< MinGlobal << " "<< RecorridoGlobal.size() <<" ";
	for(int i=0; i<RecorridoGlobal.size(); i++){
		cout<< RecorridoGlobal[i] << " ";	
	} 
	cout<< endl;
	return 0;

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
				Nodo pp = PokeParadas[i];
				//si es posible ir con el gimnasio, marco y voy y desmarco
					if(puedoIrPP(pp)){
						pp.Recorrer(true);
						RecorridoActual.push_back(pp.DameIndice());
						BT();
						pp.Recorrer(false);
						RecorridoActual.pop_back();
					}
			 	}	
			}	


			if(i<Gimnasios.size()){
				Nodo gim = Gimnasios[i];
				//si es posible ir con el gimnasio, marco y voy y desmarco
				if (puedoIrG(gim)){
					GimRecorridos++;					
					voy(gim);	
					GimRecorridos--;				
				}
			}
			//Voy a pokeparadas
			if(i<PokeParadas.size()){
				Nodo pp = PokeParadas[i];
				//si es posible ir a pokeparada, marco y voy y desmarco
				if(puedoIrPP(pp)){
					voy(pp);
				}
			}
			
				
	}
	if(MinActual<=MinGlobal){
		MinGlobal=MinActual;
		RecorridoGlobal=RecorridoActual;
	}	
	return;
}

bool puedoIrPP( Nodo & p){
	return !moch.estaLLena() && (p.Recorrido() == false);
}

bool puedoIrG(Nodo & p){
	return moch.DamePeso() >= -(p.DamePociones()) && (p.Recorrido() == false);
}



void voy(Nodo & p) {
	p.Recorrer(true);
	Nodo origen = BuscarNodo(RecorridoActual.back());
	float dist = Distancia(origen, p)
	MinActual += dist;
	RecorridoActual.push_back(p.DameIndice());
	int pociones = p.DamePociones();
	moch.usarMochila(pociones);
	BT();
	MinActual -= dist;
	RecorridoActual.pop_back();
	pp.Recorrer(false);
	RecorridoActual.push_back(p.DameIndice());
	moch.usarMochila(-pociones);
}



Nodo & BuscarNodo(int n){
	if(n<= Gimnasios.size()){
		return Gimnasios[n-1];
	}
	else{
		return PokeParadas[n-Gimnasios.size()-1];
	}
}



//Max entre 2 valores
int Maximo(int a, int b){
	if (a <= b)
	{
		return b;
	}
	return a;
}

