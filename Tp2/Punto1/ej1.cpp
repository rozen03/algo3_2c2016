 #include "eje.h"
#include "estructuras.h"
#include <iostream>
#include <queue>
using namespace std;

void imprimirLinea(int linea){
  std::cout << "Linea: "<<linea << std::endl;
}
//void tomarMatriz(char * matriz[],int f, int c){
#define tomarMatriz(){ \
  for (size_t i = 0; i < f; i++) {\
    for (size_t j = 0; j < c; j++) {\
      cin >> aux;\
      if (j == 0 || j == f - 1)\
        continue; \
      if (i == 0 || i == c - 1)\
        continue; \
      matriz[i - 1][j - 1] =-1;\
    }\
  }\
}

#define verNodo(i,j,variable){\
    if (indices[i][j] >= 0) {\
      variable = indices[i][j];\
    } else {\
      nodos[count] = new Nodo(count);\
      indices[i][j] = count;\
      variable = count;\
      count++;\
    }\
}
//}

void parsearInputYPrintear() {
  int f, c, p;
  cin >> f >> c;
  if (true) {
    cin >> p;
  }

  char aux;
  int matriz[f - 2][c - 2];
  tomarMatriz();
  for (size_t i = 0; i < c-2; i++) {
    for (size_t j = 0; j <f-2; j++) {
      cout <<" "<<matriz[i][j]<<" ";
    }
    cout << endl;
  }
  cout << endl;
  cout << endl;
  cout << endl;
}

bool esPiso(int coso){
  return coso==-1;
}
void parsearInput()
{ // string input) {
  // fstream ip;
  // ip.open(input);
  int f, c, p;
  cin >> f >> c;
  if (true) {
    cin >> p;
  }

  int aux=0;
  int indices[f - 2][c - 2];
  int matriz[f - 2][c - 2];
  unsigned int count = 0;
  unsigned int countEjes = 0;
  Nodo *nodos[(f - 2) * (c - 2)];

  unsigned int nodidex =0;
  for (int i = 0; i < f-2; i++) {
    for (int j = 0; j < c-2; j++) {
      indices[i][j] = -1;
      nodos[nodidex] = NULL;
      nodidex++;
      if(i<c-2 && j<f-2){
        matriz[i][j]= -2;
      }
    }
  }
  tomarMatriz();
  for (size_t i = 0; i < f -2; i++) {
    for (size_t j = 0; j <c -2; j++) {
      // cout << "i:" << i << " j:" << j << endl;
      aux = matriz[i][j];
      if (esPiso(aux)) {
        imprimirLinea(__LINE__);
        int index;
        int derecha, abajo;
        // Tomo/inicializo el nodo
        verNodo(i,j,index)
        // A la derecha
        if (j < c - 3) {
          aux = matriz[i][j];
          if (aux == 'a') {
            verNodo(i,j+1,derecha);
            Eje *e = new Eje(countEjes, 0, nodos[index], nodos[derecha]);
            nodos[index]->ejes.push(e);
            nodos[derecha]->ejes.push(e);
            countEjes++;
          }
        }
        // Abajo
        if (i < c - 3) {
          aux = matriz[i + 1][j];
          if (esPiso(aux)) {
            verNodo(i+1,j,abajo);
            Eje *e = new Eje(countEjes, 0, nodos[index], nodos[abajo]);
            nodos[index]->ejes.push(e);
            nodos[abajo]->ejes.push(e);
            countEjes++;
          }
        }
      } else if ((aux - '0' > -1) && (aux - '0' < 10)) {
        int peso = aux - '0';
        int arriba, abajo, izquierda, derecha;
        arriba = -1;
        abajo = -1;
        izquierda = -1;
        derecha = -1;
        // A la derecha
        if (j < c - 3) {
          aux = matriz[i][j + 1];
          if (esPiso(aux)) {
            verNodo(i,j+1,derecha);
          }
        }
        // Abajo
        if (i < f - 3) {
          aux = matriz[i + 1][j];
          if (esPiso(aux)) {
            verNodo(i+1,j,abajo);
          }
        }
        // A la izquierda
        if (0 < j) {
          aux = matriz[i][j - 1];
          if (esPiso(aux)) {
            verNodo(i,j-1,izquierda)
          }
        }
        // arriba
        if (0 < i) {
          aux = matriz[i - 1][j];
          if (esPiso(aux)) {
            verNodo(i-1,j,arriba);
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
        Eje *e = new Eje(countEjes, peso, nodos[a], nodos[b]);
        nodos[a]->ejes.push(e);
        nodos[b]->ejes.push(e);
        countEjes++;

      }
    }
  }
  //std::vector<std::vector<int> > matrizDeAdyacencia(f-2,std::vector<int>(c-2));
  int matrizDeAdyacencia[f - 2][c - 2];
  for (unsigned int i = 0; i < f - 2; i++) {
    for (unsigned int j = 0; j < c - 2; j++) {
      matrizDeAdyacencia[i][j]=-1;
    }
  }
  for (size_t i = 0; i < (f - 2) * (c - 2); i++) {
    if (nodos[i] != NULL) {
      while (!nodos[i]->ejes.empty()) {
        Eje *e = nodos[i]->ejes.top();
        matrizDeAdyacencia[i][e->dameElOtroNodoPorfa(nodos[i])->indice] = e->peso;
            //std::cout<<"Nodo: "<<i<<" Eje:"<<e->indice <<" Peso: " << e->peso<<" Conecta con: "<<e->dameElOtroNodoPorfa(nodos[i])->indice << std::endl;
        nodos[i]->ejes.pop();
      }
    }
  }
  cout << endl;
  /*for (size_t i = 0; i < c - 2; i++) {
    for (size_t j = 0; j < f - 2; j++) {
      cout << matrizDeAdyacencia[i][j] << " ";
    }
    cout << endl;
  }*/

  cout << endl;
  cout << "imalaiv you bitch!" << endl;
}

int main(int argc, char *argv[]) {
  parsearInput();
 }
