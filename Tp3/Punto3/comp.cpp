#include "ej3.h"
using namespace std;
uint64_t rdtsc() {
    unsigned int lo, hi;
    __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
    return ((uint64_t)hi << 32) | lo;
}

int main(){
    double res=0.0;
    vnod gimnasios;
    vnod pokeParadas;
    Mochila mochila(30);
    int i=0;
    gimnasios.push_back(Nodo(-12,i++,0,4));
    gimnasios.push_back(Nodo(-9,i++,0,8));
    gimnasios.push_back(Nodo(-6,i++,0,11));
    gimnasios.push_back(Nodo(-10,i++,0,21));
    gimnasios.push_back(Nodo(-2,i++,0,21));
    pokeParadas.push_back(Nodo(0,i++,0,0));
    pokeParadas.push_back(Nodo(0,i++,0,1));
    pokeParadas.push_back(Nodo(0,i++,0,2));
    pokeParadas.push_back(Nodo(0,i++,0,3));
    pokeParadas.push_back(Nodo(0,i++,0,5));
    pokeParadas.push_back(Nodo(0,i++,0,6));
    pokeParadas.push_back(Nodo(0,i++,0,7));
    pokeParadas.push_back(Nodo(0,i++,0,9));
    pokeParadas.push_back(Nodo(0,i++,0,10));
    pokeParadas.push_back(Nodo(0,i++,0,12));
    pokeParadas.push_back(Nodo(0,i++,0,13));
    pokeParadas.push_back(Nodo(0,i++,0,14));
    pokeParadas.push_back(Nodo(0,i++,0,15));
    pokeParadas.push_back(Nodo(0,i++,0,16));
    pokeParadas.push_back(Nodo(0,i++,0,16));
    pokeParadas.push_back(Nodo(0,i++,0,17));
    //Lectura(gimnasios, pokeParadas, mochila);
    //for (auto proximoUltimo:gimnasios){
    //    cout<<proximoUltimo.CordenadaX()<< " "<< proximoUltimo.CordenadaY()<<endl;
    //}
    int rep =1000;
    vint solucion;
    uint64_t elapsed=0;
    uint64_t start;
    uint64_t took;
    for (size_t j = 0; j < rep; j++) {
        start = rdtsc();
        res = pto3(gimnasios,pokeParadas,mochila,solucion);
        took = rdtsc() - start;
        elapsed+=took;
        solucion.clear();
    }
    cout<<"res a: "<<res<< "\tduracion: "<<elapsed/rep<<endl;
    elapsed=0;
    for (size_t j = 0; j < rep; j++) {
        start = rdtsc();
        res = pto3b(gimnasios,pokeParadas,mochila,solucion);
        took = rdtsc() - start;
        elapsed+=took;
        solucion.clear();
    }
    cout<<"res b: "<<res<< "\tduracion: "<<elapsed/rep<<endl;
    //imprimirSolucion(solucion);
}
