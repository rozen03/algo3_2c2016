#include "../clases.h"
typedef vector<int> vint;
typedef std::vector<vnod> vvnod;
float tirarPokeParadas(vnod pokeParadas, vnod &gimnasios, Mochila mochila,
    vnod &solucion) {

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
        float tirarPokeParadas(vnod pokeParadas, vnod &gimnasios, Mochila mochila) {
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
        tuple<vnod, float> solucionesVecindad(vvnod &vecindad, vnod pokeParadas,
            Mochila &mochila, float valor) {
                tuple<vnod, float> res;
                vnod vacio;
                res = make_tuple(vacio, valor + 1);
                for (auto gimnasios : vecindad) {
                    auto sol = tirarPokeParadas(pokeParadas, gimnasios, mochila);
                    if (sol == -1)
                    continue;vint &solucion
                    if (sol < valor) {
                        res = make_tuple(gimnasios, sol);
                    }
                }
                return res;
            }

            vnod dameGimnasios(vnod gimnasios, vint &solucion){
                vnod res(gimnasios.size());
                int indiceAPoner=0;
                for (auto indice : solucion){
                    for (auto gym: gimnasios){
                        if(gym.DameIndice() == indice)
                        res[indiceAPoner]=gym;
                        indiceAPoner++;
                    }
                    break;
                }
                return res;
            }
            double BusquedaLocal(vnod &gimnasios, vnod &pokeParadas, Mochila &mochila, vint &solucion, int valor){
                vnod nuevosGimnasios = dameGimnasios;
                vint solucion_posible;
                int res_posible;
                res_posible= pto3( nuevosGimnasios, pokeParadas,mochila,  solucion_posible);
                if(res_posible<valor){
                    solucion=solucion_posible;
                    return res_posible
                }else{
                    return valor;
                }
            }
            int pto3(vnod gimnasios, vnod pokeParadas, Mochila &mochila, vint &solucion) {
                bool mejora = true;
                tuple<vnod, float> actual =
                make_tuple(gimnasios, tirarPokeParadas(pokeParadas, gimnasios, mochila));
                while (mejora) {
                    vvnod vecinitud = vecindad(gimnasios);
                    auto minim =
                    solucionesVecindad(vecinitud, pokeParadas, mochila, get<1>(actual));
                    mejora = get<1>(minim) < get<1>(actual);
                    if (mejora)
                    actual = minim;
                }
                ImprimirNod(get<0>(actual));
                vnod solucioNodos(1, Nodo(27, 27, 27, 27));
                auto res = tirarPokeParadas(pokeParadas, gimnasios, mochila, solucioNodos);
                ImprimirNod(solucioNodos);
                for (auto nodo : solucioNodos) {
                    solucion.push_back(nodo.DameIndice());
                }
                return res;
            }

            int main() {
                vnod pokeParadas;
                vnod gimnasios;
                Mochila mochila = Mochila(100);
                vint solucion;
                pto3(gimnasios, pokeParadas, mochila, solucion);
                for (auto val : solucion) {
                    cout << val << ",";
                }
                cout << endl;
            }
