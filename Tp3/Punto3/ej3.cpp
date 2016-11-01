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
      auto compararDistancia = [it](auto a, auto &&b) {
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
vector<tuple<vnod, int>> solucionesVecindad(vvnod &vecindad, vnod pokeParadas,
                                            Mochila &mochila) {
  vector<tuple<vnod, int>> res;
  for (auto gimnasios : vecindad) {
    auto sol = tirarPokeParadas(pokeParadas, gimnasios, mochila);
    if (sol == -1)
      continue;
    auto tuplis = make_tuple(gimnasios, sol);

    res.push_back(tuplis);
  }
  return res;
}
int pto3(vnod gimnasios, vnod pokeParadas, Mochila &mochila, vint &solucion) {
  Nodo pp1 = Nodo(0, 1, 1, 1);
  Nodo pp2 = Nodo(0, 2, 2, 2);
  Nodo gym1 = Nodo(-1, 3, 3, 3);
  Nodo gym2 = Nodo(-4, 4, 4, 4);

  pokeParadas.push_back(pp1);
  pokeParadas.push_back(pp2);
  gimnasios.push_back(gym1);
  gimnasios.push_back(gym2);

  bool mejora = true;
  tuple<vnod, int> actual =
      make_tuple(gimnasios, tirarPokeParadas(pokeParadas, gimnasios, mochila));
  auto compararDistancia = [](auto a, auto &&b) {
    return get<1>(a) < get<1>(b);
  };
  while (mejora) {
    vvnod vecinitud = vecindad(gimnasios);
    vector<tuple<vnod, int>> soluciones =
        solucionesVecindad(vecinitud, pokeParadas, mochila);

    vector<tuple<vnod, int>>::iterator minim =
        min_element(soluciones.begin(), soluciones.end(), compararDistancia);
    mejora = get<1>(*minim) < get<1>(actual);
    if (mejora)
      actual = *minim;
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
