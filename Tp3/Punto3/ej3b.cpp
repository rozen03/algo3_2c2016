//#include "../clases.h"
#include "ej3.h"
using namespace std;
typedef vector<vnod> vvnod;
typedef vector<vint> vvint;


vvint dameBloques(vnod & gimnasios,vint solucion){
    int cantidad_de_gimnasios = gimnasios.size();
    vvint bloques(cantidad_de_gimnasios);
    int indiceDeBloque=0; //indice del bloque q voy a estar pusheadndo cosas
    for(int indice: solucion){
        bloques[indiceDeBloque].push_back(indice);
        if(indice < cantidad_de_gimnasios){
            indiceDeBloque++;
        }
    }
    return bloques;
}


double distancia ( vnod gimnasios,   vnod &pokeParadas,  vvint & bloques){
    auto ultimo = dameNodo(gimnasios,pokeParadas,bloques[0][0]);
    auto proximoUltimo=ultimo;
    double suma=0;
    for(auto bloque:bloques){
        for(auto indice:bloque){
            proximoUltimo=dameNodo(gimnasios,pokeParadas,indice);
            suma+=proximoUltimo.Distancia(ultimo);
            ultimo=proximoUltimo;
        }
    }
    return suma;
}
bool validarConMochila(vnod &gimnasios, vnod &pokeParadas,Mochila &mochila,vvint &bloques){
    int suma=0;
    //int peso = -it->DamePociones();
    for(auto bloque:bloques){
        for(auto indice:bloque){
            if (indice <gimnasios.size() ){
                Nodo & proximoUltimo=dameNodo(gimnasios,pokeParadas,indice);
                suma+= proximoUltimo.DamePociones();
                if (suma<0){
                    return false;
                }
            }else{
                suma+=3;
                if (suma > mochila.DameCapacidad()){
                    suma = mochila.DameCapacidad();
                }
            }

        }
    }
    return true;
}
bool validarConMochila(vnod &gimnasios, vnod &pokeParadas,Mochila &mochila,vint &solucion){
    int suma=0;
    //int peso = -it->DamePociones();
    for(auto indice:solucion){
        if (indice <gimnasios.size() ){
            Nodo & proximoUltimo=dameNodo(gimnasios,pokeParadas,indice);
            suma+= proximoUltimo.DamePociones();
            if (suma<0){
                return false;
            }
        }else{
            suma+=3;
            if (suma > mochila.DameCapacidad()){
                suma = mochila.DameCapacidad();
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
    double mejorValor=distancia(gimnasios,pokeParadas,solucion);
    int mejorSwap_i=0;
    int mejorSwap_j=0;
    while(hayMejora){
        hayMejora=false;
        for (size_t i = 0; i < solucion.size(); i++) {
            for (size_t j = 0; j < solucion.size(); j++) {
                if (i==j|| solucion[i] < gimnasios.size() || solucion[j] < gimnasios.size()){
                    continue;
                }
                iter_swap(solucion.begin() + i, solucion.begin() + j);
                double valor=distancia(gimnasios,pokeParadas,solucion);
                if (valor<mejorValor){
                    mejorValor=valor;
                    hayMejora=true;
                    mejorSwap_i=i;
                    mejorSwap_j=j;
                }
                iter_swap(solucion.begin() + i, solucion.begin() + j);
            }
        }
        if(hayMejora){
            iter_swap(solucion.begin() + mejorSwap_i, solucion.begin() + mejorSwap_j);
        }
    }
    return mejorValor;
}
double mejorarPokeparadas(vnod &gimnasios, vnod &pokeParadas, Mochila &mochila, vint &solucion){
    bool hayMejora=true;
    double mejorValor=distancia(gimnasios,pokeParadas,solucion);
    int posicionAInsertar;
    int indiceAInsertar;
    int indiceAEliminar;
    vint ppEnLaNube;
    for (auto pokeParada: pokeParadas){
        if (find(solucion.begin(), solucion.end(), pokeParada.DameIndice()) == solucion.end()){//si no esta en la solucion
            ppEnLaNube.push_back(pokeParada.DameIndice());
        }
    }
    while(hayMejora){
        hayMejora=false;
        for (size_t i = 1; i < solucion.size(); i++) {
            if (solucion[i] < gimnasios.size()){
                continue;
            }
            ppEnLaNube.push_back(solucion[i]);
            for (int pokeParada : ppEnLaNube) {
                for (size_t j = 1; j < i; j++) {

                        vint::const_iterator first = solucion.begin();
                        vint::const_iterator last = solucion.end() ;
                        vint newVec(first, last);
                        newVec.erase(newVec.begin()+ i);
                        newVec.insert(newVec.begin()+j,pokeParada);
                    if(distancia(gimnasios,pokeParadas,newVec)<distancia(gimnasios,pokeParadas,solucion)){
                        if(validarConMochila(gimnasios,pokeParadas,mochila,newVec)){
                            posicionAInsertar=j;
                            indiceAInsertar=pokeParada;
                            indiceAEliminar=i;
                            hayMejora=true;
                        }
                    }
                }

            }
            ppEnLaNube.pop_back();
        }
        if(hayMejora){
            solucion.erase(solucion.begin()+ indiceAEliminar);
            solucion.insert(solucion.begin()+posicionAInsertar,indiceAInsertar);
        }
    }
    return distancia(gimnasios,pokeParadas,solucion);
}
double BusquedaLocalb(vnod &gimnasios, vnod &pokeParadas, Mochila &mochila, vint &solucion, double valor){

    vvint bloques = dameBloques(gimnasios,solucion);
    double res_posible=mejorOrdenDeBloques( gimnasios, pokeParadas,mochila, bloques);
    vint solucion_posible;
    for (auto bloque: bloques){
        solucion_posible.insert(solucion_posible.end(),bloque.begin(),bloque.end());
    }

    res_posible=mejorOrdenDePokeParadas(gimnasios,pokeParadas,solucion_posible);

    res_posible= mejorarPokeparadas(gimnasios,pokeParadas,mochila,solucion_posible);

    bloques = dameBloques(gimnasios,solucion_posible);
    res_posible=mejorOrdenDeBloques(gimnasios, pokeParadas,mochila, bloques);
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
double tirarPokeParadass(vnod pokeParadas, vnod& gimnasios, Mochila& mochila, vnod &solucion) {
    int suma = 0;
    int distancia = 0;
    bool esSolucionFinal = false;
    bool hayUltimo=false;
    Nodo ultimo= pokeParadas[0];//le meto uno cualquiera por q no hay constructor vacio lpm
    Nodo ultimoIter=pokeParadas[0];
    auto iterUltimo=pokeParadas[0];
    bool hayIterUltimo=false;
    vnod parteDeSolucion;
    if (!solucion.empty()) {
        esSolucionFinal = true;
        solucion.clear();
    }
    for (vnod::iterator it = gimnasios.begin(); it != gimnasios.end(); ++it) {

        parteDeSolucion.clear();
        int peso = -it->DamePociones();
        while (suma < peso) {
            if (pokeParadas.empty()){
                return -1;
            }

            suma += 3;
            if (suma > mochila.DameCapacidad()){
                suma = mochila.DameCapacidad();
            }
            auto compararDistancia = [=](Nodo a, Nodo b) {
                if(hayIterUltimo){
                    return iterUltimo.Distancia(a) < iterUltimo.Distancia(b);
                }
                if(it->Distancia(a) == it->Distancia(b)){
                    Nodo centro = Nodo(0,0,0,0);
                    return centro.Distancia(a)<centro.Distancia(b);
                }
                return it->Distancia(a) < it->Distancia(b);
            };
            vnod::iterator pokeParadaCerca = min_element(
                pokeParadas.begin(), pokeParadas.end(), compararDistancia);
                parteDeSolucion.push_back(*pokeParadaCerca);
                pokeParadas.erase(pokeParadaCerca);
                iterUltimo = *pokeParadaCerca;
                hayIterUltimo=true;
            }
            for (int i =parteDeSolucion.size() -1; i >-1; i--) {

                if (hayUltimo){
                    distancia += ultimo.Distancia(parteDeSolucion[i]);
                }else{
                    hayUltimo=true;
                }
                ultimo= parteDeSolucion[i];
                if (esSolucionFinal) {
                    solucion.push_back(parteDeSolucion[i]);
                }
            }
            if (hayUltimo){
                distancia += ultimo.Distancia(*it);
            }else{
                hayUltimo=true;
            }

            ultimo=*it;
            iterUltimo=*it;
            suma-=peso;
            if (esSolucionFinal) {
                solucion.push_back(*it);
            }
        }
        return distancia;
    }
    double pto3b(vnod gimnasios, vnod& pokeParadas, Mochila& mochila, vint &solucion) {
        sort(gimnasios.begin(), gimnasios.end(),[](Nodo a, Nodo b){return a.DamePociones()<b.DamePociones();});
        vnod solucioNodos(1,Nodo(27,27,27,27));
        auto dist =  tirarPokeParadas(pokeParadas, gimnasios,  mochila, solucioNodos);
        if (dist ==-1){
            cout<<"aah dio mal"<<endl;
            return -1;
        }
        for(auto nodo : solucioNodos){
            solucion.push_back(nodo.DameIndice());
        }
        return BusquedaLocalb(gimnasios,pokeParadas, mochila, solucion,distancia(gimnasios,pokeParadas,solucion));
    }

/*
    int main(){
        double res=0.0;
        vnod gimnasios;
        vnod pokeParadas;
        Mochila mochila(30);
        gimnasios.push_back(Nodo(-12,0,0,4));
        gimnasios.push_back(Nodo(-9,1,0,8));
        gimnasios.push_back(Nodo(-6,2,0,11));
        pokeParadas.push_back(Nodo(0,3,0,0));
        pokeParadas.push_back(Nodo(0,4,0,1));
        pokeParadas.push_back(Nodo(0,5,0,2));
        pokeParadas.push_back(Nodo(0,6,0,3));
        pokeParadas.push_back(Nodo(0,7,0,5));
        pokeParadas.push_back(Nodo(0,8,0,6));
        pokeParadas.push_back(Nodo(0,9,0,7));
        pokeParadas.push_back(Nodo(0,10,0,9));
        pokeParadas.push_back(Nodo(0,11,0,10));
        //pokeParadas.push_back(Nodo(0,12,0,12));
        //pokeParadas.push_back(Nodo(0,13,0,12));
        //pokeParadas.push_back(Nodo(0,14,0,14));
        //pokeParadas.push_back(Nodo(0,15,0,15));
        //pokeParadas.push_back(Nodo(0,16,0,16));
        //pokeParadas.push_back(Nodo(0,16,0,16));
        //pokeParadas.push_back(Nodo(0,17,0,17));
        //Lectura(gimnasios, pokeParadas, mochila);
        //for (auto proximoUltimo:gimnasios){
        //    cout<<proximoUltimo.CordenadaX()<< " "<< proximoUltimo.CordenadaY()<<endl;
        //}
        vint solucion;
        res = pto3b(gimnasios,pokeParadas,mochila,solucion);

        imprimirSolucion(solucion);
        cout<<"res: "<<res<<endl;
    }
*/
