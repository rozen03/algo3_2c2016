#include <cmath>
#include <vector>
#include <iostream>
//#ifndef __NODO__
//#define __NODO__


using namespace std;

//Tipos


class Nodo{
public:
	Nodo(int p, int i, int x, int y);
	int DameIndice();
	int DamePociones();
	bool Recorrido();
	void Recorrer(bool b);
	float Distancia(Nodo & y);
	bool EsGim();

private:
	int indice;
	int pociones;
	bool Recorri;
	int X;
	int Y;
};


class Mochila{
public:
	Mochila(unsigned int n);
	int DameCapacidad();
	int DamePeso();
	bool estaLLena();
	void Restaurar(int n);
	void usarMochila(int n); 
	void CambiarCapacidad(int n);	
	
private:
	int capacidad;
	int peso;
};


//funciones nodo

int Nodo::DameIndice(){

	return indice;
}

Nodo::Nodo(int p, int i, int x, int y):indice(i), pociones(p), X(x), Y(y), Recorri(false){
};

float Nodo::Distancia(Nodo & f) {
	int x = X - f.X;
	int y = Y - f.Y;
	int pre = pow(x, 2) + pow(y, 2);
	return sqrt(pre);
}

int Nodo::DamePociones(){
	return pociones;	
}

bool Nodo::Recorrido(){
	return Recorri;
}

void Nodo::Recorrer(bool b){
	Recorri= b;
}

bool Nodo::EsGim(){
	return (pociones!=3);
}

//funciones mochila

void Mochila::CambiarCapacidad(int n){
	capacidad=n;
}

Mochila::Mochila(unsigned int n):capacidad(n), peso(0){
};

int Mochila::DameCapacidad(){
	return capacidad;
}
int Mochila::DamePeso(){
	return peso;
}
bool Mochila::estaLLena(){
	return peso==capacidad;
}
void Mochila::usarMochila(int n){
	if(peso+n>capacidad){
		peso=capacidad;	
	}
	else{
		peso+=n;
	}
}

void Mochila::Restaurar(int n){
	peso = n;
}


typedef vector<Nodo > vnod;
//Lectura de Datos

void Lectura(vnod& gimnasios, vnod& pokeParadas, Mochila& moch){
	int n, m, k;
	int maxPos = 0;
	int totPos = 0;
	cin>> n >> m >> k;
	moch.CambiarCapacidad(k);
	for(int i=1; i<=n; i++){
		int x,y,p;
		cin>> x >> y >> p;
		totPos += p;
		if(maxPos < p) maxPos = p;
		Nodo nuevo = Nodo(-p,i,x,y);
		gimnasios.push_back(nuevo);		
	}
	if(maxPos > k || m*3 < totPos) {
	cout<< -1<<endl;
	return;
	}
	for(int i=n+1; i<= n+m; i++){
		int x,y;
		cin>> x >> y;
		Nodo nuevo= Nodo(3,i,x,y);
		pokeParadas.push_back(nuevo); 
	}
}


