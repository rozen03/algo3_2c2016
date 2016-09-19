#include "eje.h"
#include "estructuras.h"
#include <iostream>
#include <queue>
#define ARRAY_SIZE(array) (sizeof((array)) / sizeof((array[0])))
using namespace std;
void parsearInputYPrintear() { // string input) {
  // fstream ip;
  // ip.open(input);
  int f, c, p;
  cin >> f >> c;
  if (true) {
    cin >> p;
  }

  char aux;
  char matriz[f - 2][c - 2];
  //  cout << input << endl;
  for (size_t i = 0; i < c; i++) {
    for (size_t j = 0; j < f; j++) {
      cin >> aux;
      if (i == 0 || i == f - 1)
        continue; // ignoro la primera y la ultima fila
      if (j == 0 || j == c - 1)
        continue; // ignoro la primera y la ultima columna

      matriz[i][j] = aux;
    }
  }
  cout << f << " " << c << " " << p << endl;
  for (size_t i = 0; i < c; i++) {
    for (size_t j = 0; j < f; j++) {
      if (i == 0 || i == f - 1) {
        cout << "#"; // ignoro la primera y la ultima fila
        continue;    // ignoro la primera y la ultima columna
      }
      if (j == 0 || j == c - 1) {
        cout << "#"; // ignoro la primera y la ultima columna
        continue;    // ignoro la primera y la ultima columna
      }
      cout << matriz[i][j];
    }
    cout << endl;
  }
  cout << endl;
  cout << endl;
  cout << endl;
}

void parsearInput() { // string input) {
  // fstream ip;
  // ip.open(input);
  int f, c, p;
  cin >> f >> c;
  if (true) {
    cin >> p;
  }

  char aux;
  int indices[f - 2][c - 2];
  char matriz[f - 2][c - 2];
  for (size_t i = 0; i < c; i++) {
    for (size_t j = 0; j < f; j++) {
      cin >> aux;
      if (i == 0 || i == f - 1)
        continue; // ignoro la primera y la ultima fila
      if (j == 0 || j == c - 1)
        continue; // ignoro la primera y la ultima columna
      indices[i - 1][j - 1] = -1;
      matriz[i - 1][j - 1] = aux;
    }
  }
  unsigned int count = 0;
  unsigned int countEjes = 0;
  Nodo *nodos[(f - 2) * (c - 2)];
  for (size_t i = 0; i < (f - 2) * (c - 2); i++) {
    nodos[i] = NULL;
  }
  for (size_t i = 0; i < c - 2; i++) {
    for (size_t j = 0; j < f - 2; j++) {
      // cout << "i:" << i << " j:" << j << endl;
      aux = matriz[i][j];
      if (aux == '.') {
        int index;
        int derecha, abajo;
        // Tomo/inicializo el nodo
        if (indices[i][j] >= 0) {
          index = indices[i][j];
        } else {
          nodos[count] = new Nodo(count);
          indices[i][j] = count;
          index = count;
          count++;
        }
        // A la derecha
        if (j < f - 3) {
          aux = matriz[i][j + 1];
          if (aux == '.') {
            if (indices[i][j + 1] >= 0) {
              derecha = indices[i][j + 1];
            } else {
              nodos[count] = new Nodo(count);
              indices[i][j + 1] = count;
              derecha = count;
              count++;
            }
            Eje *e = new Eje(countEjes, 0, nodos[index], nodos[derecha]);
            nodos[index]->ejes.push(e);
            nodos[derecha]->ejes.push(e);
            countEjes++;
          }
        }
        // Abajo
        if (i < c - 3) {
          aux = matriz[i + 1][j];
          if (aux == '.') {
            if (indices[i + 1][j] >= 0) {
              abajo = indices[i + 1][j];
            } else {
              nodos[count] = new Nodo(count);
              indices[i + 1][j] = count;
              abajo = count;
              count++;
            }
            Eje *e = new Eje(countEjes, 0, nodos[index], nodos[abajo]);
            nodos[index]->ejes.push(e);
            nodos[abajo]->ejes.push(e);
            countEjes++;
          }
        }
      } else if ((aux - '0' > -1) && (aux - '0' < 10)) {
        int arriba, abajo, izquierda, derecha;
        arriba = -1;
        abajo = -1;
        izquierda = -1;
        derecha = -1;
        // A la derecha
        if (j < f - 3) {
          aux = matriz[i][j + 1];
          if (aux == '.') {
            if (indices[i][j + 1] >= 0) {
              derecha = indices[i][j + 1];
            } else {
              nodos[count] = new Nodo(count);
              indices[i][j + 1] = count;
              derecha = count;
              count++;
            }
          }
        }
        // Abajo
        if (i < c - 3) {
          aux = matriz[i + 1][j];
          if (aux == '.') {
            if (indices[i + 1][j] >= 0) {
              abajo = indices[i + 1][j];
            } else {
              nodos[count] = new Nodo(count);
              indices[i + 1][j] = count;
              abajo = count;
              count++;
            }
          }
        }
        // A la izquierda
        if (0 < j) {
          aux = matriz[i][j - 1];
          if (aux == '.') {
            if (indices[i][j - 1] >= 0) {
              izquierda = indices[i][j + 1];
            } else {
              nodos[count] = new Nodo(count);
              indices[i][j - 1] = count;
              izquierda = count;
              count++;
            }
          }
        }
        // arriba
        if (0 < i) {
          aux = matriz[i - 1][j];
          if (aux == '.') {
            if (indices[i - 1][j] >= 0) {
              arriba = indices[i - 1][j];
            } else {
              nodos[count] = new Nodo(count);
              indices[i - 1][j] = count;
              arriba = count;
              count++;
            }
          }
        }
        // conecto los dos nodos
        int a, b;
        a = max(arriba, max(abajo, max(izquierda, derecha)));
        if (a == arriba) {
          b = max(abajo, max(izquierda, derecha));
        } else if (a == abajo) {
          b = max(arriba, max(izquierda, derecha));
        } else if (a == izquierda) {
          b = max(abajo, max(arriba, derecha));
        } else {
          b = max(abajo, max(izquierda, arriba));
        }
        Eje *e = new Eje(countEjes, aux - '0', nodos[a], nodos[b]);
        nodos[a]->ejes.push(e);
        nodos[b]->ejes.push(e);
        countEjes++;
        cout << "eje numericowowow" << endl;
      }
    }
  }

  int matrizDeAdyacencia[f - 2][c - 2];
  for (size_t i = 0; i < c - 2; i++) {
    for (size_t j = 0; j < f - 2; j++) {
      matrizDeAdyacencia[i][j] = -1;
    }
  }
  cout << "exodia" << endl;
  for (size_t i = 0; i < (f - 2) * (c - 2); i++) {
    if (nodos[i] != NULL) {
      // cout << nodos[i]->indice << " ";
      while (!nodos[i]->ejes.empty()) {
        Eje *e = nodos[i]->ejes.top();
        matrizDeAdyacencia[i][e->dameElOtroNodoPorfa(nodos[i])->indice] =
            e->peso;
        nodos[i]->ejes.pop();
      }
    }
  }
  cout << endl;
  for (size_t i = 0; i < c - 2; i++) {
    for (size_t j = 0; j < f - 2; j++) {
      cout << matrizDeAdyacencia[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
  cout << "imalaiv you bitch!" << endl;
}

int main(int argc, char *argv[]) { parsearInput(); }
