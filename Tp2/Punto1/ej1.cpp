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
  for (size_t i = 0; i < c - 2; i++) {
    for (size_t j = 0; j < f - 2; j++) {
      // cout << "i:" << i << " j:" << j << endl;
      cout << matriz[i][j] << endl;
      aux = matriz[i][j];
      cout << matriz[i][j] << endl;
      if (aux == '.') {

        cout << "entre al punto" << endl;
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
        cout << "alawan" << endl;
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
            countEjes++;
          }
        }
      }
    }
  }

  for (size_t i = 0; i < (f - 2) * (c - 2); i++) {
    // cout << nodos[3] << " ";
    // cout << nodos[i]->indice << " ";
  }
  cout << endl;
  cout << "imalaiv you bitch!" << endl;
}

int main(int argc, char *argv[]) { parsearInput(); }
