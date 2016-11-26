#include "../clases.h"

using namespace std;
typedef vector<vnod> vvnod;
typedef vector<vint> vvint;
vvint dameBloques(vnod & gimnasios,vint solucion){
    int cantidad_de_gimnasios = gimnasios.size();
    vvint bloques(cantidad_de_gimnasios);
    int indiceDeBloque=0; //indice del bloque q voy a estar pusheadndo cosas
    for(int indice: solucion){
        bloques[indiceDeBloque].push_back(i);
        if(i >= cantidad_de_gimnasios){
            indiceDeBloque++;
        }
    }
    return bloques;
}

Nodo &dameNodo(vnod &gimnasios, vnod &pokeParadas,  int &indice){
    if(indice == -1){
        return NULL;
    }
    if(indice < gimnasios.size()){
        return gimnasios[indice];
    }else{
        return pokeParadas[indice-gimnasios.size()-1];
    }
}
double distancia (vnod &gimnasios, vnod &pokeParadas,  vvint & bloques){
    auto ultimo = dameNodo(gimnasios,pokeParadas,bloques[0][0]);
    auto proximoUltimo=ultimo;
    double suma=0;
    for(auto bloque:bloques){
        for(auto indice:bloque){
            proximoUltimo=dameNodo(gimnasios,pokeParadas,indice);
            suma+=proximoUltimo->Distancia(ultimo);
        }
    }
    return suma;
}
double distancia (vnod &gimnasios, vnod &pokeParadas,  vint & solucion){
    auto ultimo = dameNodo(gimnasios,pokeParadas,solucion[0]);
    auto proximoUltimo=ultimo;
    double suma=0;
    for(auto indice:solucion){
            proximoUltimo=dameNodo(gimnasios,pokeParadas,indice);
            suma+=proximoUltimo->Distancia(ultimo);
    }
    return suma;
}
bool validarConMochila(vnod &gimnasios, vnod &pokeParadas,Mochila &mochila,vvint &bloques){
    int suma=0;
    int peso = -it->DamePociones();
    for(auto bloque:bloques){
        for(auto indice:bloque){
            if (indice <gimnasios.size() ){
                proximoUltimo=dameNodo(gimnasios,pokeParadas,indice);
                suma+= proximoUltimo->DamePociones();
                if (suma<0){
                    return false;
                }
            }else{
                sume+=3;
                if (suma > mochila.DameCapacidad()){
                    suma = mochila.DameCapacidad();
                }
            }

        }
    }
    return true;
}
double mejorOrdenDeBloques(vnod &gimnasios, vnod &pokeParadas,Mochila &mochila,vvint &bloques){
    bool hayMejora=true;
    double mejorValor=distancia(gimnasios,pokeParadas,bloques);
    int mejorSwap_i=0;
    int mejorSwap_j=0;
    while(hayMejora){
        hayMejora=false;
        for (size_t i = 0; i < bloques.size(); i++) {
            for (size_t j = 0; j < bloques.size(); j++) {
                if (i==j){
                    continue;
                }
                iter_swap(bloques.begin() + i, bloques.begin() + j);
                double valor=distancia(gimnasios,pokeParadas,bloques);
                if (valor<mejorValor && validarConMochila(gimnasios, pokeParadas,mochila,bloques)){
                    mejorValor=valor;
                    hayMejora=true;
                    mejorSwap_i=i;
                    mejorSwap_j=j;
                }
                iter_swap(bloques.begin() + i, bloques.begin() + j);
            }
        }
        if(hayMejora){
            iter_swap(bloques.begin() + mejorSwap_i, bloques.begin() + mejorSwap_j);
        }
    }
    return mejorValor;
}
double mejorOrdenDePokeParadas(vnod &gimnasios, vnod &pokeParadas,vint &solucion){
    bool hayMejora=true;
    double mejorValor=distancia(gimnasios,pokeParadas,bloques);
    int mejorSwap_i=0;
    int mejorSwap_j=0;
    while(hayMejora){
        hayMejora=false;
        for (size_t i = 0; i < solucion.size(); i++) {
            for (size_t j = 0; j < solucion.size(); j++) {
                if (i==j|| solucion[i] < gimnasios.size() || solucion[j] < gimnasios.size()){
                    continue;
                }
                iter_swap(bloques.begin() + i, bloques.begin() + j);
                double valor=distancia(gimnasios,pokeParadas,bloques);
                if (valor<mejorValor)){
                    mejorValor=valor;
                    hayMejora=true;
                    mejorSwap_i=i;
                    mejorSwap_j=j;
                }
                iter_swap(bloques.begin() + i, bloques.begin() + j);
            }
        }
        if(hayMejora){
            iter_swap(bloques.begin() + mejorSwap_i, bloques.begin() + mejorSwap_j);
        }
    }
    return mejorValor;
}
double BusquedaLocal(vnod &gimnasios, vnod &pokeParadas, Mochila &mochila, vint &solucion, double valor){
    vvint bloques = dameBloques(gimnasios,solucion);
    double res_posible=mejorOrdenDeBloques( nuevosGimnasios, pokeParadas,mochila, bloques);
    vint solucion_posible;
    for (auto bloque: bloques){
        solucion_posible.insert(solucion_posible.end(),bloque.begin(),bloque.end());
    }
    mejorOrdenDePokeParadas(gimnasios,pokeParadas,solucion_posible);
    bloques = dameBloques(gimnasios,solucion_posible);
    res_posible=mejorOrdenDeBloques(nuevosGimnasios, pokeParadas,mochila, bloques);
    solucion_posible.clear();
    for (auto bloque: bloques){
        solucion_posible.insert(solucion_posible.end(),bloque.begin(),bloque.end());
    }
    if(res_posible<valor){
        solucion=solucion_posible;
        return res_posible;
    }else{
        return valor;
    }
}
