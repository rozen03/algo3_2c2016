#include "../clases.h"
//#include "../Punto2/Punto2.cpp"
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
double dist(Nodo* f);
void moverse(Nodo * lugar);
void sacar(vnod &vector,int elem);
Nodo* PokeParadaMasCercana();
Nodo* GimMasCercano();
void grasp();
void GolozoRand(Nodo & comienzo);
int PuntajeAnodo(Nodo & n);
void Filtro(vpnod & vect);
void SacarPunteros(vpnod & vector, int elem);
Nodo * ElegirElNodo(vpnod & vect);
Nodo * DameNodo(int indice);
void ResetGlobalesPto4();




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
cerr<< "res= "<<MinGlobal<<endl;
for (int i = 0; i < RecorridoGlobal.size(); ++i)
{
	cerr<< RecorridoGlobal[i]<<endl;
}
}



double pto4(vnod gim,vnod pp, Mochila mochil,vint & sol){
	PokeParadas = pp;
	Gimnasios =gim;
	RecorridoGlobal.clear();
	RecorridoActual.clear();
	moch.CambiarCapacidad(mochil.DameCapacidad());
	moch.Restaurar(0);
	xactual = 0;
	yactual = 0;
	MinGlobal = MAX;
	MinActual = 0;

	cerr<<"gim "<<Gimnasios.size()<<"pp "<< PokeParadas.size()<< endl;


	grasp();
	sol=RecorridoGlobal;
	double res = MinGlobal;
	
	return res;
}


void grasp(){

	vnod entradasValidas;

	cerr<<"pokeparadas y gim :";
	for(int i = 0; i< PokeParadas.size(); i++) cerr<<PokeParadas[i].DameIndice()<<" ";
	cerr<<endl;
	for(int i = 0; i< Gimnasios.size(); i++) cerr<<Gimnasios[i].DameIndice()<<" ";
	cerr<<endl;	
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
	  // BusquedaLocal(Gimnasios, PokeParadas, moch, RecorridoActual,MinActual);
	    if (MinActual < MinGlobal) {
	      MinGlobal = MinActual;
	      RecorridoGlobal = RecorridoActual;
	    }
	    RecorridoActual.clear();
	    MinActual = 0;
	}

}

void GolozoRand(Nodo & comienzo){
  int gimRecorridos = Gimnasios.size();
  int k=0;
  int indice = comienzo.DameIndice();
  Nodo* proxLugar= DameNodo(indice);
  moverse(proxLugar);
  cerr<<"el prox nodo "<<proxLugar->Recorrido()<<"("<<proxLugar->DameIndice()<<")"<<endl;
 cerr<<"en PP"<<PokeParadas[0].Recorrido()<<"("<<PokeParadas[0].DameIndice()<<")"<<endl;
  while(k!=gimRecorridos){
  //mientras sigan existiendo gimnasios que no pasaron
  //cout <<"Gimnasios"<< Gimnasios.size()<< endl;
  //cout <<"PokeParadaMasCercana"<< PokeParadaMasCercana.size()<< endl;
    vpnod losMasCercanos;

    //guardamos los 4 gim y las 4 pp mas cercanas a la posicion actual
    
    double porcAux = (double)(Gimnasios.size()+ PokeParadas.size()) * 20/100;

    int  porcentaje = ceil(porcAux);
    cerr<< "porcentaje "<<porcentaje<<endl;

    for (int i = 0; i < porcentaje; i++) {

      Nodo* aux=PokeParadaMasCercana();    

      if (aux != NULL) {      	
      	losMasCercanos.push_back(aux);	
      	aux->Recorrer(true);
      	
  		}
      Nodo* auxg=GimMasCercano();
      if(auxg!=NULL) {      	
       losMasCercanos.push_back(auxg);
      	aux->Recorrer(true);
  	  }
     	
    }


    for (int i = 0; i < losMasCercanos.size(); i++) {

      Nodo aux= *losMasCercanos[i];
      cerr<< "cercano "<< aux.DameIndice()<<endl;
      aux.Recorrer(false);
    }

    // me quedo solo con los 4 mas cercanos
    Filtro(losMasCercanos);
	cerr<<"size los mas cercanos "<<losMasCercanos.size()<<endl;
    proxLugar = ElegirElNodo(losMasCercanos);
	cerr <<"sali elegir nodo"<<endl;
 
    cerr<< "el prox lugar es "<<proxLugar->DameIndice() <<" y "<<proxLugar->EsGim() <<endl;

    if(proxLugar==NULL && gimRecorridos!=Gimnasios.size()){
      MinActual=-1;
      RecorridoActual.clear();
      break;
      }
      else{
      	 proxLugar->Recorrer(true);	
      	 moverse(proxLugar);
  		cerr<< "peso mochila " <<moch.DamePeso()<<endl;
   		 if(proxLugar->EsGim()){
      	 	k++;
    	}
      }

      cerr<<proxLugar->DameIndice()<<endl;     

      
    }
   cerr<< "min global " <<MinGlobal<< " min actual "<< MinActual<<endl;
   //Restauro los valores de las pokeparadas y gimnasios
   for(int i = 0;i <PokeParadas.size(); i++) PokeParadas[i].Recorrer(false);
   for(int i = 0;i <Gimnasios.size(); i++) Gimnasios[i].Recorrer(false);
   	
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

	for (int i = 0; i < vect.size(); ++i)
		{
			cerr<< vect[i]->DameIndice()<<endl;
		}	
  vpnod aux;
  Nodo * GimMin=NULL;
  bool hayGim = false;
  double capacidadvect = (double) vect.size()/2;
  int a= ceil(capacidadvect );
  
  for (int i = 0; i < a; i++) {
  	
    Nodo* min=vect[0];

    if(vect[i]->EsGim() && GimMin == NULL) GimMin=vect[i];


    if((GimMin != NULL && vect[i]->EsGim())  && dist(vect[i]) < dist(GimMin) )  GimMin=vect[i];
        	
    for(int j = 1; j < vect.size(); j++) {

      if(dist(min)>dist(vect[j])) min=vect[j];
    }
    cerr<< "min "<<min->DameIndice()<<endl;
    if(min -> EsGim()) hayGim = true;
    aux.push_back(min);
    SacarPunteros(vect, min->DameIndice());

  }
 cerr<< "aux size"<< aux.size()<< aux[0]->DameIndice()<<endl;	
  if(!hayGim && GimMin!=NULL){
  	aux.push_back(GimMin);
  }

  vect=aux;
  cerr<< "en filtrar el size es "<< vect.size()<< vect[1]->DameIndice()<<endl;
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


	cerr<< "size " << vect.size()<<endl;
	cerr<< vect[0]->DameIndice()<<endl;
  Nodo* res;
  vint valorNodos;
  int suma=0;
  
  for(int i=0; i<vect.size(); i++){

    int aux= vect.size()*10-i*10;
  
    aux += PuntajeAnodo(*vect[i]);
 
    suma+=aux;
    valorNodos.push_back(suma);
  }
  cerr<<" nodos : ";
  for (int i = 0; i < vect.size(); ++i)
  {
  	cerr<<vect[i]<<" ";
  }
  cerr<<endl;
    int random = rand() % suma +1;
   cerr<<"valor random "<<random<<endl;
    for (int i = 0; i < valorNodos.size(); i++) {
    	cerr<<"valor nodo" <<valorNodos[i]<<endl;
      if (random <= valorNodos[i]){
      	cerr<<"entre en el if"<<endl;
        res= vect[i];
        cerr<< "elegido "<<res->DameIndice()<<endl;
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

double dist(Nodo* f) {
	int x = xactual - f->CordenadaX();
	int y = xactual - f->CordenadaY();
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
	if(!RecorridoActual.empty()){
		MinActual =+ dist(lugar);
	}
	RecorridoActual.push_back(lugar->DameIndice());
	

	//actualizo x e y
	xactual = lugar->CordenadaX();
	yactual = lugar->CordenadaY();
	
	//elimino el Nodo de la lista correspondiente
	lugar->Recorrer(true);
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

Nodo* GimMasCercano(){//AAAAA NO SE SI USAR PUNTEROS
	Nodo * min = NULL;
	for (int i = 0; i < Gimnasios.size(); ++i){
		if( !Gimnasios[i].Recorrido() && moch.DamePeso()>= - Gimnasios[i].DamePociones()){//verifico que puedo vencer este gimnacio 
			if(min==NULL){
				min = &Gimnasios[i];
			}
			else{
				if(!Gimnasios[i].Recorrido() && dist(min)>dist(&Gimnasios[i])){
					min = &Gimnasios[i];		
				}
			}
		}
	}

	return min;

}

Nodo* PokeParadaMasCercana(){
	Nodo* min =NULL;
	for (int i = 0; i < PokeParadas.size(); ++i){
		bool b=true;

		cerr<<PokeParadas[i].Recorrido()<<"("<<PokeParadas[i].DameIndice()<< ") "<<endl;
		if(min==NULL && !PokeParadas[i].Recorrido()){

				min = &PokeParadas[i];

			}
			else{

				if((min != NULL &&dist(min)>dist(&PokeParadas[i])) && !PokeParadas[i].Recorrido()){
					
					min = &PokeParadas[i];	
					
				}
		}
	}
	cerr<<endl;
	return min;
	cerr<<min->DameIndice()<<endl;
}

Nodo * DameNodo(int indice){
	Nodo * res;
	if(indice<=Gimnasios.size()){
		res = &Gimnasios[indice-1];
	}
	else{
		res = &PokeParadas[indice - Gimnasios.size()- 1];
	}
	return res;
}