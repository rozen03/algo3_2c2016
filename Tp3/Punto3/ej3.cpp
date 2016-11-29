#include "ej3.h"

double tirarPokeParadas(vnod pokeParadas, vnod &gimnasios, Mochila mochila) {
    vnod solucion;
    return tirarPokeParadas(pokeParadas, gimnasios, mochila, solucion);
}
vnod copiaSwapeada(vnod gimnasios, int pos_uno, int pos_dos) {
    vnod copia = gimnasios;
    iter_swap(copia.begin() + pos_uno, copia.begin() + pos_dos);
    return copia;
}
vvnod vecindad(vnod gimnasios) {
    vvnod res;
    for (size_t i = 0; i < gimnasios.size(); i++) {
        for (size_t j = 0; j < gimnasios.size(); j++) {
            if (i == j)
            continue;
            res.push_back(copiaSwapeada(gimnasios, i, j));
        }
    }
    return res;
}
tuple<vnod, double> solucionesVecindad(vvnod &vecindad, vnod pokeParadas, Mochila &mochila, double valor) {
    tuple<vnod, double> res;
    vnod vacio;
    res = make_tuple(vacio, valor + 1);
    for (auto gimnasios : vecindad) {
        auto sol = tirarPokeParadas(pokeParadas, gimnasios, mochila);
        if (sol == -1)
        continue;
        //vint &solucion
        if (sol < valor) {
            res = make_tuple(gimnasios, sol);
        }
    }
    return res;
}

vnod dameGimnasios(vnod gimnasios, vint &solucion){
    vnod res;//(gimnasios.size());
    int indiceAPoner=0;
    for (auto indice : solucion){
        for (auto gym: gimnasios){
            if(gym.DameIndice() == indice){
                //res[indiceAPoner]=gym;
                res.push_back(gym);
                indiceAPoner++;
                break;
            }
        }
    }
    return res;
}
tuple<vnod, double> actualInicial(vnod gimnasios, vnod pokeParadas, Mochila &mochila){
    return make_tuple(gimnasios, tirarPokeParadas(pokeParadas, gimnasios, mochila));
}
double mejorarSolucion (vnod gimnasios, vnod pokeParadas, Mochila &mochila, vint &solucion) {
    bool mejora = true;
    auto actual =actualInicial(gimnasios, pokeParadas, mochila);
    while (mejora) {
        vvnod vecinitud = vecindad(gimnasios);
        auto minim =
        solucionesVecindad(vecinitud, pokeParadas, mochila, get<1>(actual));
        mejora = get<1>(minim) < get<1>(actual);
        if (mejora)
        actual = minim;
    }
    vnod solucioNodos;
    solucioNodos.push_back(Nodo(27, 27, 27, 27));
    auto res = tirarPokeParadas(pokeParadas, gimnasios, mochila, solucioNodos);
    for (auto nodo : solucioNodos) {
        solucion.push_back(nodo.DameIndice());
    }
    return res;
}
double pto3(vnod gimnasios, vnod& pokeParadas, Mochila& mochila, vint &solucion) {
    sort(gimnasios.begin(), gimnasios.end(),[](Nodo a, Nodo b){return a.DamePociones()<b.DamePociones();});
    return mejorarSolucion(gimnasios,pokeParadas, mochila, solucion);
}

double BusquedaLocal(vnod &gimnasios, vnod &pokeParadas, Mochila &mochila, vint &solucion, double valor){
    vnod nuevosGimnasios = dameGimnasios(gimnasios,solucion);
    vint solucion_posible;
    double res_posible;
    res_posible= mejorarSolucion( nuevosGimnasios, pokeParadas,mochila,  solucion_posible);
    if(res_posible<valor){
        solucion=solucion_posible;
        return res_posible;
    }else{
        return valor;
    }
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
    res = pto3(gimnasios,pokeParadas,mochila,solucion);

    imprimirSolucion(solucion);
    cout<<"res: "<<res<<endl;
}
*/
