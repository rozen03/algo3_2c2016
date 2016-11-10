#ifndef __Ej3__
#include "../clases.h"

using namespace std;
typedef vector<vnod> vvnod;

double tirarPokeParadas(vnod pokeParadas, vnod &gimnasios, Mochila mochila, vnod &solucion);

double tirarPokeParadas(vnod pokeParadas, vnod &gimnasios, Mochila mochila);
    
vnod copiaSwapeada(vnod gimnasios, int pos_uno, int pos_dos);

vvnod vecindad(vnod gimnasios);

tuple<vnod, double> solucionesVecindad(vvnod &vecindad, vnod pokeParadas, Mochila &mochila, double valor);

vnod dameGimnasios(vnod gimnasios, vint &solucion);
 
tuple<vnod, double> actualInicial(vnod gimnasios, vnod pokeParadas, Mochila &mochila);

double mejorarSolucion (vnod gimnasios, vnod pokeParadas, Mochila &mochila, vint &solucion);
 
double pto3(vnod gimnasios, vnod &pokeParadas, Mochila &mochila, vint &solucion);

double BusquedaLocal(vnod &gimnasios, vnod &pokeParadas, Mochila &mochila, vint &solucion, double valor);
 
 
#endif
