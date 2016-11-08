#include "../clases.h"
#include "../Punto2/Punto2.cpp"
//#include "../Punto3/ej3.cpp"
#include <iostream>
#include <limits>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


//Tipos
typedef vector<int> vint;
typedef vector<Nodo > vnod;
typedef vector<Nodo * > vpnod;

//variables globales
vnod GimDeCero;
/*

vnod PokeParadas;
vnod Gimnasios;
Mochila moch(0);
int xactual;
int yactual;

double MinGlobal;
double MinActual;
vint RecorridoGlobal;
vint RecorridoActual;
*/ 

//funciones
void grasp();
void GolozoRand(Nodo comienzo);
int PuntajeAnodo(Nodo & n);
void Filtro(vpnod & vect);
void SacarPunteros(vpnod & vector, int elem);
Nodo * ElegirElNodo(vpnod & vect);
void ResetGlobalesPto4();

/*
int main(){
  srand (time(NULL));
    ResetGlobalesPto4();
  Lectura(Gimnasios, PokeParadas, moch);
  for (int i=0; i < Gimnasios.size();i++) {
    Nodo aux= Gimnasios[i];
    if (aux.DamePociones()==0) {
      GimDeCero.push_back(aux);
    }
  }

  grasp();

}

*/

double pto4(vnod gim,vnod pp, Mochila mochil,vint & sol){
	PokeParadas = pp;
	Gimnasios =gim;
	RecorridoGlobal.clear();
	RecorridoActual.clear();
	moch.CambiarCapacidad(mochil.DameCapacidad());
	moch.Restaurar(0);
	xactual = 42;
	yactual = 42;
	MinGlobal = MAX;
	MinActual = 42;




	grasp();
	sol=RecorridoGlobal;
	double res = MinGlobal;
	
	return res;
}

void grasp(){

vnod entradasValidas;

for (int i=0; i < GimDeCero.size();i++) {
  Nodo aux= GimDeCero[i];
  if (aux.DamePociones()==0) {
    entradasValidas.push_back(aux);
  }
}

for (int i = 0; i < PokeParadas.size(); i++) {
  entradasValidas.push_back(PokeParadas[i]);
}
int j= entradasValidas.size();

for (int i = 0; i < j; i++) {

    GolozoRand(entradasValidas[i]);
cerr<<"sali del golozo"<<endl;
  //  BusquedaLocal(Gimnasios, PokeParadas, moch, RecorridoActual,MinActual);
    if (MinActual < MinGlobal) {
      MinGlobal = MinActual;
      RecorridoGlobal = RecorridoActual;
    }
    RecorridoActual.clear();
    MinActual = 0;
}

}

void GolozoRand(Nodo comienzo){

  Nodo* proxLugar=&comienzo;
cerr<<"el prox nodo "<<proxLugar->DameIndice()<<endl;
  while(!Gimnasios.empty()){//mientras sigan existiendo gimnasios que no pasaron
  //cout <<"Gimnasios"<< Gimnasios.size()<< endl;
  //cout <<"PokeParadaMasCercana"<< PokeParadaMasCercana.size()<< endl;
    vpnod losMasCercanos;

    //guardamos los 4 gim y las 4 pp mas cercanas a la posicion actual
    
    double porcAux = (double)(Gimnasios.size()+ PokeParadas.size()) * 20/100;

    int  porcentaje = ceil(porcAux);

    for (int i = 0; i < porcentaje; i++) {

      Nodo* aux=PokeParadaMasCercana();

      if (aux != NULL) {losMasCercanos.push_back(aux);
      sacar(PokeParadas, aux->DameIndice());
  		}
      Nodo* auxg=GimMasCercano();

      if(auxg!=NULL) { losMasCercanos.push_back(auxg);
      sacar(Gimnasios, auxg->DameIndice());
  	  }
      
    }

    for (int i = 0; i < losMasCercanos.size(); i++) {

      Nodo aux= *losMasCercanos[i];
      if(aux.EsGim()){
        Gimnasios.push_back(aux);


      }
      else{

        PokeParadas.push_back(aux);
      }
    }

    // me quedo solo con los 4 mas cercanos
    Filtro(losMasCercanos);

    proxLugar = ElegirElNodo(losMasCercanos);
cerr <<"sali elegir nodo"<<endl;
 
    	cerr<< "el prox lugar es "<<proxLugar->DameIndice() <<" y "<<proxLugar->EsGim() <<endl;


    if(proxLugar==0){ //no le puedo ganar al gimnasio mas cercano
      proxLugar = PokeParadaMasCercana();
    }

    if(proxLugar==0){
      distanciaRecorrida=-1;
      Recorrido.clear();
      }
      cerr<<proxLugar->DameIndice()<<endl;
      moverse(proxLugar);


    }

}

int PuntajeAnodo(Nodo & n){
	cerr<< "emtre a puntaje nodo"<<endl;
	cerr<< n.DameIndice()<<endl;
  int res=0;
  if(n.EsGim() && moch.DamePeso()>=n.DamePociones()) res+=30;
  if(!n.EsGim() && !moch.estaLLena()){
    if (moch.DameCapacidad()-moch.DamePeso()==2) res+=15;
    if(moch.DameCapacidad()-moch.DamePeso()==1) res+=10;
    res+=25;

  }
  cerr<< moch.DameCapacidad() <<" " << moch.DamePeso() <<endl;
  return res;
}

void Filtro(vpnod & vect ){

  vpnod aux;
  Nodo * GimMin;
  bool hayGim = false;

  for (int i = 0; i < ceil(vect.size()/2); i++) {

    Nodo* min=vect[0];

    if(vect[i]->EsGim() && GimMin == NULL) GimMin=vect[i];

    //no tendria q preguntar tmbn si vecti es gim? se lo voy a agregar
    if((GimMin != NULL && vect[i]->EsGim())  && dist(vect[i]) < dist(GimMin) )  GimMin=vect[i];
        	
    for(int j = 1; j < vect.size(); j++) {

      if(dist(min)>dist(vect[j])) min=vect[j];
    }

    if(min -> EsGim()) hayGim = true;
    aux.push_back(min);
    SacarPunteros(vect, min->DameIndice());
  }
 
  if(!hayGim)   aux.push_back(GimMin);
  vect=aux;

}

void SacarPunteros(vpnod &vector,int elem){

	for(int i = 0; i<vector.size();i++){
		int indiceAux = vector[i]->DameIndice();
		if(indiceAux == elem){
			vector[i] = vector.back();
			vector.pop_back();

			return;
		}
	}
}

Nodo* ElegirElNodo(vpnod & vect){
	cerr<< "size" << vect.size()<<endl;
	cerr<< vect[0]->DameIndice()<<endl;
  Nodo* res;
  vint valorNodos;
  int suma=0;
  cerr<< "valo basura nodo es "<< res->DameIndice()<<endl;
  for(int i=0; i<vect.size(); i++){

    int aux= vect.size()*10-i*10;
    cerr << "bla"<<endl;
    aux += PuntajeAnodo(*vect[i]);
    cerr<<"puntaje nodo"  << aux<<endl;
    suma+=aux;
    valorNodos.push_back(suma);
  }

    int random = rand() % suma +1;
   cerr<<random<<endl;
    for (int i = 0; i < valorNodos.size(); i++) {

      if (random <= valorNodos[i]){
      	cerr<<"entre en el if"<<endl;
        res= vect[i];
        break;
      }
    }


    return res;
  }

//si hay un shift de 42 en algun lado es por que tengo que resetear mejor
void ResetGlobalesPto4(){
PokeParadas.clear();
Gimnasios.clear();
RecorridoGlobal.clear();
RecorridoActual.clear();
moch.CambiarCapacidad(0);
moch.Restaurar(0);
xactual = 42;
yactual = 42;
MinGlobal = MAX;
MinActual = 42;
}
