#include "dsu.h"
#include "../estructuras.h"
#include <queue>
#include <fstream>
#include "../eje.h"

using namespace std;

unsigned int kruskal(priority_queue<Eje *> Ejes, unsigned int n){
	while(!(Ejes.empty())){
		Eje * t= Ejes.top();
		cout<<t->peso<< endl;
		Ejes.pop();
		}
	cout<<"kruskal"<<endl;
	unsigned int res=0;
	cout<< "int"<<endl;
	dsu conj;
	cout<< "int"<<endl;
	conj.init(n);
	cout<<"init"<<endl;
	while(!(Ejes.empty())){
		cout<<"entre al while"<<endl;
		Eje e= *Ejes.top();
		Ejes.pop();
		//ver como se llamas los Nodos extremos del Eje podrian ser inicio y fin?!
		Nodo * nUno=e.dameNodo();
		Nodo * nDos=e.dameElOtroNodoPorfa(nUno);
		cout<<"me rompi"<<endl;
		unsigned int nu = nUno->indice;
		unsigned int nd = nDos->indice;
		if(conj.find(nu) != conj.find(nd)){
			cout<<"entre al if del while"<<endl;
			res=+e.damePeso();
			conj.unir(nu, nd);
		}
		cout<<"sali del while"<<endl;
	return res;
	}

}


/**
*
**
*/
void parsearInputAux(vector<Nodo *> & nodos, vector<Eje *> & ejes,int ejercicio, string input)
{
  fstream ip;
  ip.open(input);
  int f, c, p;
  ip >> f >> c;
  if (ejercicio==1) {
    ip >> p;
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
        ip >> aux;
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
      }
    }
  }
  nodos.resize(count);
  ejes.resize(countEjes);
}


/**
*
*/



int solu( unsigned int n, vector<Eje *> ejes){
	cout<<"entre a la conchuda sola"<< endl;
	priority_queue<Eje *> aristas;
	for(unsigned int j=0; j< ejes.size(); j++){
		cout<<ejes[j]->peso<<endl;
		aristas.push(ejes[j]);
	}
	cout<<"sali del maldito for"<< endl;
	int res= kruskal(aristas,n);
	return res;
}

int main(int agrc, char *argv[]){
	string input = argv[1];
	cout<< "entre al puto main" <<endl;
	vector<Nodo *> nodos;
	vector<Eje *> ejes;
	parsearInputAux(nodos, ejes, 2, input);
	cout<< "sali de parsear inputos"<< endl;
	for(int i=0; i<ejes.size(); i++){
		cout<< ejes[i]->peso << endl;
		}
	unsigned int n= nodos.size();
	solu(n, ejes); 
	return 0;	
}
