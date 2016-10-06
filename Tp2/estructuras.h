#ifndef __NODO__
#define __NODO__
#include <iostream>
#include <queue>

using namespace std;
class Eje;
class Nodo {
public:
  unsigned int indice;
  priority_queue<Eje *> ejes;
  vector<Eje *> ejejes;
  int nivel;
  bool pared;
  Nodo(unsigned int indice) : indice(indice){
    ejes = priority_queue<Eje *>();
    ejejes = vector<Eje *>(4,NULL);
    nivel=0;
    pared=false;
    contadorDeEjes=0;
  };
  Nodo(unsigned int indice,bool esPared) : indice(indice),pared(esPared){
    ejes = priority_queue<Eje *>();
    ejejes = vector<Eje *>(4,NULL);
    nivel=0;
    contadorDeEjes=0;
  };
  Nodo(unsigned int indice,int cualnivel) : indice(indice),nivel(cualnivel){
    ejes = priority_queue<Eje *>();
    ejejes = vector<Eje *>(4,NULL);
    pared=false;
    contadorDeEjes=0;
  };
  Nodo(unsigned int indice,int cualnivel,bool esPared) : indice(indice),nivel(cualnivel),pared(esPared){
    ejes = priority_queue<Eje *>();
    ejejes = vector<Eje *>(4,NULL);
    contadorDeEjes=0;
  };
  Nodo(unsigned int indice,bool esPared,int cualnivel) : indice(indice),pared(esPared),nivel(cualnivel){
    ejes = priority_queue<Eje *>();
    ejejes = vector<Eje *>(4,NULL);
    contadorDeEjes=0;
  };

  void resizearEjes(){
    ejejes.resize(contadorDeEjes);
  };
  void pushearEje(Eje* e){
    ejejes.push_back(e);
    contadorDeEjes++;
  };
private:
  int contadorDeEjes;
};

void imprimirLinea(int linea){
  std::cout << "Linea: "<<linea << std::endl;
}




#define verNodo(i,j,variable,aux){\
    if (indices[i][j] >= 0) {\
      variable = indices[i][j];\
    } else {\
      if (aux =='o'){\
        nodos[0] = new Nodo(0);\
        indices[i][j] = 0;\
        variable = 0;\
      }else if (aux =='x'){\
        nodos[nodos.size()-1] = new Nodo(nodos.size()-1);\
        indices[i][j] = nodos.size()-1;\
        variable = nodos.size()-1;\
      }else{\
        nodos[count] = new Nodo(count);\
        indices[i][j] = count;\
        variable = count;\
        count++;\
      }\
    }\
}
bool esPiso(char coso){
  return coso=='.' ||coso=='o' || coso=='x'  ;
}
bool esPisoPared(char coso){
  return coso=='#' || esPiso(coso);
}


int  parsearInput(vector<Nodo *> & nodos, vector<Eje *> & ejes,int ejercicio)
{
  int f, c, p;
  cin >> c >> f;
  if (ejercicio==1) {
    cin >> p;
  }else{
    p=0;
  }

  char aux;
  int indices[f - 2][c - 2];
  char matriz[f - 2][c - 2];
  unsigned int count = (ejercicio==1)?1:0;
  unsigned int countEjes = 0;
  unsigned int countParedes = 0;
  unsigned int nodidex =0;
  nodos.resize((f - 2) * (c - 2),NULL);
  ejes.resize((f - 2) * (c - 2)*4,NULL);
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
        cout<<matriz[i][j];
      }
      cout<<endl;
    }
  for (size_t i = 0; i < f -2; i++) {
    for (size_t j = 0; j <c -2; j++) {
      aux = matriz[i][j];
      if (esPiso(aux)) {
        int index;
        int derecha, abajo;
        // Tomo/inicializo el nodo
        verNodo(i,j,index,aux);
        // Abajo
        if (j < c - 3) {
          aux = matriz[i][j+1];
          if (esPiso(aux)) {
            verNodo(i,j+1,derecha,aux);
            Eje *e = new Eje(countEjes, 0, nodos[index], nodos[derecha]);
            nodos[index]->ejes.push(e);
            nodos[index]->pushearEje(e);
            nodos[derecha]->ejes.push(e);
            nodos[derecha]->pushearEje(e);
            ejes[countEjes]=e;
            countEjes++;
          }
        }
        // derecha
        if (i < f - 3) {
          aux = matriz[i + 1][j];
          if (esPiso(aux)) {
            verNodo(i+1,j,abajo,aux);
            Eje *e = new Eje(countEjes, 0, nodos[index], nodos[abajo]);
            nodos[index]->ejes.push(e);
            nodos[index]->pushearEje(e);
            nodos[abajo]->ejes.push(e);
            nodos[abajo]->pushearEje(e);
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
            verNodo(i,j+1,derecha,aux);
          }
        }
        // Abajo
        if (i < f - 3) {
          aux = matriz[i + 1][j];
          if (esPiso(aux)) {
            verNodo(i+1,j,abajo,aux);
          }
        }
        // A la izquierda
        if (0 < j) {
          aux = matriz[i][j - 1];
          if (esPiso(aux)) {
            verNodo(i,j-1,izquierda,aux);
          }
        }
        // arriba
        if (0 < i) {
          aux = matriz[i - 1][j];
          if (esPiso(aux)) {
            verNodo(i-1,j,arriba,aux);
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
        nodos[a]->pushearEje(e);
        nodos[b]->ejes.push(e);
        nodos[b]->pushearEje(e);
        ejes[countEjes]=e;
        countEjes++;

      }else if(ejercicio==1 && aux=='#'){
        imprimirLinea(__LINE__);
        int arriba, abajo, izquierda, derecha,index;
        // Tomo/inicializo el nodo
        verNodo(i,j,index,aux);
        nodos[index]->esPared=true;
        arriba = -1;
        abajo = -1;
        izquierda = -1;
        derecha = -1;
        // A la derecha
        if (j < c - 3) {
          aux = matriz[i][j + 1];
          if (esPiso(aux)) {
            verNodo(i,j+1,derecha,aux);
            Eje *e = new Eje(countEjes, 1, nodos[index], nodos[derecha]);
            nodos[index]->ejes.push(e);
            nodos[index]->pushearEje(e);
            nodos[derecha]->ejes.push(e);
            nodos[derecha]->pushearEje(e);
            ejes[countEjes]=e;
            countEjes++;
          }
        }
        // Abajo
        if (i < f - 3) {
          aux = matriz[i + 1][j];
          if (esPiso(aux)) {
            verNodo(i+1,j,abajo,aux);
            Eje *e = new Eje(countEjes, 1, nodos[index], nodos[abajo]);
            nodos[index]->ejes.push(e);
            nodos[index]->pushearEje(e);
            nodos[abajo]->ejes.push(e);
            nodos[abajo]->pushearEje(e);
            ejes[countEjes]=e;
            countEjes++;
          }
        }
        // A la izquierda
        if (0 < j) {
          aux = matriz[i][j - 1];
          if (esPisoPared(aux)) {
            verNodo(i,j-1,izquierda,aux);
            Eje *e = new Eje(countEjes, 1, nodos[index], nodos[izquierda]);
            nodos[index]->ejes.push(e);
            nodos[index]->pushearEje(e);
            nodos[izquierda]->ejes.push(e);
            nodos[izquierda]->pushearEje(e);
            ejes[countEjes]=e;
            countEjes++;
          }
        }
        // arriba
        if (0 < i) {
          aux = matriz[i - 1][j];
          if (esPisoPared(aux)) {
            verNodo(i-1,j,arriba,aux);
            Eje *e = new Eje(countEjes, 1, nodos[index], nodos[arriba]);
            nodos[index]->ejes.push(e);
            nodos[index]->pushearEje(e);
            nodos[arriba]->ejes.push(e);
            nodos[arriba]->pushearEje(e);
            ejes[countEjes]=e;
            countEjes++;
          }
        }
        countParedes++;
      }
    }
  }
  nodos[count]=nodos.back();
  count++;
  nodos.resize(count);
  ejes.resize(countEjes);
  for (size_t i = 0; i < nodos.size(); i++) {
    nodos[i].resizearEjes();
  }
  return min(p,countParedes)
}

void clonarUltimoNivel(vector<Nodo *> & nodos, vector<Eje *> & ejes){
int tamanioNivel=0;
int nivelAnterior= nodos.back()->nivel;
int nivelNuevo= nivelAnterior+1;
int tam = nodos.size()-1;
int indices=nodos.size()+tamanioNivel;
int tamanioNodos=nodos.size();
int tamanioEjes=ejes.size();
while (tam >-1 && nodos[i]->nivel==nivelAnterior) {
  tam--;
  tamanioNivel++;
}
nodos.resize(tamanioNodos+tamanioNivel,NULL);
vector<Eje *>  nuevosEjes=vector<Eje *> (2*tamanioEjes);

for (int i = 0; i < tamanioNivel; i++) {
  Nodo * n= nodos[nodos.size()-tamanioNivel+i-1];
  nuevosNodos[tamanioNodos+n->indice]= new Nodo(tamanioNodos+n->indice,nivelNuevo,n->esPared);
}

for (int i = 0; i < ejes.size(); i++) {
  Eje* e = ejes[i];
  if(e->n1->nivel==e->n2->nivel && e->n1->nivel==nivelAnterior){
    Eje *e = new Eje(tamanioEjes+i, 0, nodos[tamanioNodos+e->n1->indice ], nodos[tamanioNodos+e->n2->indice]);
    nodos[tamanioNodos+e->n1->indice]->ejes.push(e);
    nodos[tamanioNodos+e->n1->indice]->pushearEje(e);
    nodos[tamanioNodos+e->n2->indice]->ejes.push(e);
    nodos[tamanioNodos+e->n2->indice]->pushearEje(e);
    ejes[tamanioEjes+i]=e;
  }
}
/*
for (int i = 0; i < tamanioNivel; i++) {
  Nodo * n= nodos[nodos.size()-tamanioNivel+i-1];
  if(n->esPared){
  }
}
*/
}
#endif
