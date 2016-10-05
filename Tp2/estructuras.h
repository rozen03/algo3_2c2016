#ifndef __NODO__
#define __NODO__
#include <iostream>
#include <queue>
#include"eje.h"

using namespace std;
//class Eje;
class Nodo {
public:
  unsigned int indice;
  priority_queue<Eje *> ejes;
  Nodo(unsigned int indice) : indice(indice){
    ejes = priority_queue<Eje *>();
  };

private:
};


void imprimirLinea(int linea){
  std::cout << "Linea: "<<linea << std::endl;
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
bool esPiso(char coso){
  return coso=='.';
}
bool esPisoPared(char coso){
  return coso=='#' || esPiso(coso);
}

void parsearInput(vector<Nodo *> & nodos, vector<Eje *> & ejes,int ejercicio)
{
  int f, c, p;
  cin >> c >> f;
  if (ejercicio==1) {
    cin >> p;
  }

  char aux;
  int indices[f - 2][c - 2];
  char matriz[f - 2][c - 2];
  unsigned int count = 0;
  unsigned int countEjes = 0;
  nodos.resize((f - 2) * (c - 2),NULL);
  ejes.resize((f - 2) * (c - 2)*4,NULL);
  unsigned int nodidex =0;
  for (int i = 0; i < f-2; i++) {
    for (int j = 0; j < c-2; j++) {
      indices[i][j] = -1;
      nodos[nodidex] = NULL;
      nodidex++;
        matriz[i][j]= 'a';
    }
  }
  for (int register j = 0; j < c; j++) {
    for (int register i = 0; i < f; i++) {
        cin >> aux;
        if (i == 0 || i == f - 1)
          continue;
        if (j == 0 || j == c - 1)
          continue;
        matriz[i - 1][j - 1] =aux;
      }
    }

  for (size_t i = 0; i < f -2; i++) {
    for (size_t j = 0; j <c -2; j++) {
      aux = matriz[i][j];
      if (esPiso(aux)) {
        int index;
        int derecha, abajo;
        // Tomo/inicializo el nodo
        verNodo(i,j,index);
        // Abajo
        if (j < c - 3) {
          aux = matriz[i][j+1];
          if (esPiso(aux)) {
            verNodo(i,j+1,derecha);
            Eje *e = new Eje(countEjes, 0, nodos[index], nodos[derecha]);
            nodos[index]->ejes.push(e);
            nodos[derecha]->ejes.push(e);
            ejes[countEjes]=e;
            countEjes++;
          }
        }
        // derecha
        if (i < f - 3) {
          aux = matriz[i + 1][j];
          if (esPiso(aux)) {
            verNodo(i+1,j,abajo);
            Eje *e = new Eje(countEjes, 0, nodos[index], nodos[abajo]);
            nodos[index]->ejes.push(e);
            nodos[abajo]->ejes.push(e);
            ejes[countEjes]=e;
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
        ejes[countEjes]=e;
        countEjes++;

      }else if(ejercicio==1 && aux=='#'){
        int arriba, abajo, izquierda, derecha,index;
        // Tomo/inicializo el nodo
        verNodo(i,j,index);
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
      }
    }
  }
  nodos.resize(count);
  ejes.resize(countEjes);
}



#endif
