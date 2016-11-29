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
    Mochila();
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
extern vnod PokeParadas;
extern vnod Gimnasios;
extern Mochila moch;
extern unsigned int GimRecorridos;
extern int PPRecorridas;
extern int PocionesNecesarias;
extern double MinGlobal;
extern double MinActual;
extern vint RecorridoGlobal;
extern vint RecorridoActual;
extern int xactual;
extern int yactual;
extern vint Recorrido;
extern double distanciaRecorrida;
// da informacion sobre un vector de nodos
void ImprimirNod(vnod &gim) ;

// Lectura de Datos

void Lectura(vnod &gimnasios, vnod &pokeParadas, Mochila &moch);
#endif
