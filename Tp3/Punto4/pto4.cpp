#include "../clases.h"
#include"../Punto2/Punto2.cpp"
#include"../Punto3/pto3.cpp"
#include <iostream>
#include <limits>
#include<stdio.h>
#include<stdlib.h>

using namespace std;


//Tipos
typedef vector<int> vint;
typedef vector<Nodo > vnod;
typedef vector<Nodo * > vpnod;

//variables globales
int solu;
vint RecorridoSolu;
vnod GimDeCero;
Mochila moch(0);
vint Recorrido;
double distanciaRecorrida;
vnod PokeParadas;
vnod Gimnasios;
int xactual;
int yactual;

//funciones
void grasp();
void GolozoRand();

void main(){
  srand (time(NULL));
  Lectura();
  for (int i=0; i < Gimnasios.size();i++) {
    Nodo aux= Gimnasios[i];
    if (aux.DamePociones==0) {
      GimDeCero.push_back(aux);
    }
  }
  grasp();

}

void grasp(){
solu=  MAX;
vnod entradasValidas;
for (int i=0; i < GimDeCero.size();i++) {
  Nodo aux= GimDeCero[i];
  if (aux.DamePociones==0) {
    entradasValidas.push_back(aux);
  }
}
for (int i = 0; i < PokeParadas.size(); i++) {
  entradasValidas.push_back(PokeParadas[i]);
}
int j= entradasValidas.size();
for (int i = 0; i < j; i++) {
    GolozoRand(entradasValidas[i]);
    BLocal(RecorridoGlobal,MinGlobal);
    if (MinGlobal<solu) {
      solu=MinGlobal;
      RecorridoSolu=RecorridoGlobal;
    }
}

}

void GolozoRand(){
  Nodo* proxLugar=0;
  while(!Gimnasios.empty()){//mientras sigan existiendo gimnasios que no pasaron
  //cout <<"Gimnasios"<< Gimnasios.size()<< endl;
  //cout <<"PokeParadaMasCercana"<< PokeParadaMasCercana.size()<< endl;
    vpnod losMasCercanos;
    //guardamos los 4 gim y las 4 pp mas cercanas a la posicion actual
    for (int i = 0; i < 4; i++) {
      Nodo* aux=PokeParadaMasCercana();
      if (aux != NULL) losMasCercanos.push_back(aux);
      sacar(PokeParadas, aux->DameIndice());
      Nodo* auxg=GimMasCercano();
      if(auxg!=NULL) losMasCercanos.push_back(auxg);
      sacar(Gimnasios, auxg->DameIndice());
    }
    for (int i = 0; i < losMasCercanos.size(); i++) {
      Nodo aux= &losMasCercanos[i];
      if(aux.EsGim()){
        Gimnasios.push_back(aux);
      }
      else{
        PokeParadas.push_back(aux);
      }
    }
    // me quedo solo con los 4 mas cercanos
    filro(losMasCercanos);

    proxLugar = ElegirElNodo(losMasCercanos);
    if(proxLugar==0){ //no le puedo ganar al gimnasio mas cercano
      proxLugar = PokeParadaMasCercana();
    }
    if(proxLugar==0){
      distanciaRecorrida=-1;
      Recorrido.clear();
      }
      moverse(proxLugar);

    }
}


int puntajeAnodo(Nodo n){
  int res=0;
  if(n.EsGim() && moch.DamePeso()>=n.DamePociones()) res+=30;
  if(!n.EsGim() && !moch.estaLLena()){
    if (moch.DameCapacidad()-moch.DamePeso()==2) res+=15;
    if(moch.DameCapacidad()-moch.DamePeso()==1) res+=10;
    res+=25;

  }
}

void filtro(vpnod & vect ){
  vpnod aux;
  for (int i = 0; i < 4; i++) {
    Nodo* min=vect[0];
    for ( j = 1; j < vect.size(); j++) {
      if dist(min)>dist(vect[j]) min=vect[j];
    }
    aux.push_back(min);
    SacarPunteros(vect, min->DameIndice());
  }
  vect=aux;
}


void sacarPunteros(vpnod &vector,int elem){

	for(int i = 0; i<vector.size();i++){
		int indiceAux = vector[i]->DameIndice();
		if(indiceAux == elem){
			vector[i] = vector.back();
			vector.pop_back();

			return;
		}
	}
}

Nodo* ElegirElNodo(vpnod vect){
  Nodo* res;
  vint valorNodos;
  int suma=0;
  for(int i=0; i<vect.size(); i++){
    int aux= 40-i*10;
    aux += puntajeAnodo(&vect[i]);
    suma+=aux;
    valorNodos.push_back(suma);
  }
    int random = rand() % suma +1;
    for (int i = 0; i < valorNodos.size(); i++) {
      if (random <= valorNodos[i]){
        res= vect[i];
      }
    }
  }
