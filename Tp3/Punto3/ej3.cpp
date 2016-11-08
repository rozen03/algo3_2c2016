#include "../clases.h"
typedef vector<int> vint;
typedef std::vector<vnod> vvnod;
double tirarPokeParadas(vnod pokeParadas, vnod &gimnasios, Mochila mochila, vnod &solucion) {
    int suma = 0;
    int distancia = 0;
    bool esSolucionFinal = false;
    if (!solucion.empty()) {
        esSolucionFinal = true;
        solucion.clear();
    }
    for (vnod::iterator it = gimnasios.begin(); it != gimnasios.end(); ++it) {
        uint peso = -it->DamePociones();
        while (suma < peso) {
            if (pokeParadas.empty())
            return -1;
            suma += 3;
            if (suma > mochila.DameCapacidad())
            suma = mochila.DameCapacidad();
            auto compararDistancia = [it](Nodo a, Nodo b) {
                return it->Distancia(a) < it->Distancia(b);
            };
            vnod::iterator pokeParadaCerca = min_element(
                pokeParadas.begin(), pokeParadas.end(), compararDistancia);
                distancia += it->Distancia(*pokeParadaCerca);
                if (esSolucionFinal) {
                    solucion.push_back(*pokeParadaCerca);
                }
                pokeParadas.erase(pokeParadaCerca);
            }
            if (esSolucionFinal) {
                solucion.push_back(*it);
            }
        }
        return distancia;
    }
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
    double pto3(vnod gimnasios, vnod pokeParadas, Mochila &mochila, vint &solucion) {
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

    double BusquedaLocal(vnod &gimnasios, vnod &pokeParadas, Mochila &mochila, vint &solucion, int valor){
        vnod nuevosGimnasios = dameGimnasios(gimnasios,solucion);
        vint solucion_posible;
        int res_posible;
        res_posible= pto3( nuevosGimnasios, pokeParadas,mochila,  solucion_posible);
        if(res_posible<valor){
            solucion=solucion_posible;
            return res_posible;
        }else{
            return valor;
        }
    }

    int main() {
        //inicializo
        vnod pokeParadas;
        vnod gimnasios;
        Mochila mochila = Mochila(100);
        vint solucion;
        sort(gimnasios.begin(), gimnasios.end(),[](Nodo a, Nodo b){a.DamePociones()<b.DamePociones()});
        pto3(gimnasios, pokeParadas, mochila, solucion);
        for (auto val : solucion) {
            cout << val << ",";
        }
        cout << endl;
    }
