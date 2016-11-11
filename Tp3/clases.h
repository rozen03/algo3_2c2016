#include <algorithm>
#include <cmath>
#include <iostream>
#include <tuple>
#include <vector>
#ifndef __NODO__
#define __NODO__

using namespace std;

//Statics
static double MAX = numeric_limits<double>::max();

//hay variables declarada post la declaracion delas clases.

class Nodo {
public:
  Nodo(int p, int i, int x, int y);
  Nodo(Nodo n, int i);
  int DameIndice();
  void asignarCantidadPociones(int p);
  //los gims tienen este valor en negativo
  int DamePociones();
  bool Recorrido();
  //para marcar que la recorriste poner true
  void Recorrer(bool b);
  double Distancia(Nodo &y);
  bool EsGim();
  int CordenadaX();
  int CordenadaY();

private:
  int indice;
  int pociones;
  bool Recorri;
  int X;
  int Y;
};



class Mochila {
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

//Tipos
typedef vector<int> vint;
typedef vector<Nodo> vnod;

//variables interpuntos
vnod PokeParadas;
vnod Gimnasios;
Mochila moch(0);
unsigned int GimRecorridos;
int PPRecorridas;
int PocionesNecesarias;
double MinGlobal;
double MinActual;
vint RecorridoGlobal;
vint RecorridoActual;
int xactual;
int yactual;
vint Recorrido;
double distanciaRecorrida;

// funciones nodo

int Nodo::DameIndice() { return indice; }

Nodo::Nodo(int p, int i, int x, int y)
    : indice(i), pociones(p), X(x), Y(y), Recorri(false){};

Nodo::Nodo( Nodo n, int i){
	indice = i;
	pociones = n.DamePociones();
	X = n.CordenadaX();
	Y = n.CordenadaY();
	Recorri = n.Recorrido();
}

double Nodo::Distancia(Nodo &f) {
  int x = X - f.X;
  int y = Y - f.Y;
  int pre = pow(x, 2) + pow(y, 2);
  return sqrt(pre);
}
void Nodo::asignarCantidadPociones(int p){
    pociones = p;
}
int Nodo::DamePociones() { return pociones; }

bool Nodo::Recorrido() { return Recorri; }

void Nodo::Recorrer(bool b) { Recorri = b; }

bool Nodo::EsGim() { return (pociones != 3); }

int Nodo::CordenadaX() { return X; }

int Nodo::CordenadaY() { return Y; }
// funciones mochila

void Mochila::CambiarCapacidad(int n) { capacidad = n; }

Mochila::Mochila(unsigned int n) : capacidad(n), peso(0){};

int Mochila::DameCapacidad() { return capacidad; }

int Mochila::DamePeso() { return peso; }

bool Mochila::estaLLena() { return peso == capacidad; }

void Mochila::usarMochila(int n) {
  if (peso + n > capacidad) {
    peso = capacidad;
  } else {
    peso += n;
  }
}

void Mochila::Restaurar(int n){ peso = n; }

// da informacion sobre un vector de nodos
void ImprimirNod(vnod &gim) {
  for (unsigned int i = 0; i < gim.size(); i++) {
    cout << "(" << gim[i].CordenadaX() << "," << gim[i].CordenadaY() << ") {"<<gim[i].DameIndice()<<"} ";
	if(gim[i].Recorrido()){
		cout<<"Recorrido ";
	}
	else{
		cout<<"No Recorrido ";
	}
    if (gim[i].EsGim())
      cout << "[" << -gim[i].DamePociones() << "] ";
  }
  cout << endl;
}

// Lectura de Datos

void Lectura(vnod &gimnasios, vnod &pokeParadas, Mochila &moch) {
  int n, m, k;
  int maxPos = 0;
  int totPos = 0;
  cin >> n >> m >> k;
  moch.CambiarCapacidad(k);
  for (int i = 1; i <= n; i++) {
    int x, y, p;
    cin >> x >> y >> p;
    totPos += p;
    if (maxPos < p)
      maxPos = p;
    Nodo nuevo = Nodo(-p, i, x, y);
    gimnasios.push_back(nuevo);
  }
  if (maxPos > k || m * 3 < totPos) {
    cout << -1 << endl;
    return;
  }
  for (int i = n + 1; i <= n + m; i++) {
    int x, y;
    cin >> x >> y;
    Nodo nuevo = Nodo(3, i, x, y);
    pokeParadas.push_back(nuevo);
  }
}
#endif
