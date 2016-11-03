//#include "../estructuras.h"
#include "estructuras_test.h"
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
#include "ej1.cpp"

using namespace std;

uint64_t rdtsc() {
  unsigned int lo, hi;
  __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
  return ((uint64_t)hi << 32) | lo;
}

int parsearInputAux(vector<Nodo *> &nodos, vector<Eje *> &ejes, int ejercicio, string test) {
  int f, c, p;
  fstream ip;
  ip.open(test);
  ip >> c >> f;
  if (ejercicio == 1) {
    ip >> p;
  } else {
    p = 0;
  }

  char aux;
  int indices[f - 2][c - 2];
  char matriz[f - 2][c - 2];
  unsigned int count = (ejercicio == 1) ? 1 : 0;
  unsigned int countEjes = 0;
  int countParedes = 0;
  unsigned int nodidex = 0;
  nodos.resize((f - 2) * (c - 2), NULL);
  ejes.resize((f - 2) * (c - 2) * 4, NULL);
  for (int i = 0; i < f - 2; i++) {
    for (int j = 0; j < c - 2; j++) {
      indices[i][j] = -1;
      nodos[nodidex] = NULL;
      nodidex++;
    }
  }
  for (int register j = 0; j < c; j++) {
    for (int register i = 0; i < f; i++) {
      ip >> aux;
      if (i == 0 || i == f - 1)
        continue;
      if (j == 0 || j == c - 1)
        continue;
      matriz[i - 1][j - 1] = aux;
    }
  }
  for (size_t i = 0; i < f - 2; i++) {
    for (size_t j = 0; j < c - 2; j++) {
      cout << matriz[i][j];
    }
    cout << endl;
  }
  for (size_t i = 0; i < f - 2; i++) {
    for (size_t j = 0; j < c - 2; j++) {
      aux = matriz[i][j];
      if (esPiso(aux)) {
        int index;
        int derecha, abajo;
        // Tomo/inicializo el nodo
        verNodo(i, j, index, aux);
        // Abajo
        if (j < c - 3) {
          aux = matriz[i][j + 1];
          if (esPiso(aux)) {
            verNodo(i, j + 1, derecha, aux);
            Eje *e = new Eje(countEjes, 0, nodos[index], nodos[derecha]);
            nodos[index]->ejes.push(e);
            nodos[index]->pushearEje(e);
            nodos[derecha]->ejes.push(e);
            nodos[derecha]->pushearEje(e);
            ejes[countEjes] = e;
            countEjes++;
          }
        }
        // derecha
        if (i < f - 3) {
          aux = matriz[i + 1][j];
          if (esPiso(aux)) {
            verNodo(i + 1, j, abajo, aux);
            Eje *e = new Eje(countEjes, 0, nodos[index], nodos[abajo]);

            nodos[index]->ejes.push(e);
            nodos[index]->pushearEje(e);
            nodos[abajo]->ejes.push(e);
            nodos[abajo]->pushearEje(e);
            ejes[countEjes] = e;
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
            verNodo(i, j + 1, derecha, aux);
          }
        }
        // Abajo
        if (i < f - 3) {
          aux = matriz[i + 1][j];
          if (esPiso(aux)) {
            verNodo(i + 1, j, abajo, aux);
          }
        }
        // A la izquierda
        if (0 < j) {
          aux = matriz[i][j - 1];
          if (esPiso(aux)) {
            verNodo(i, j - 1, izquierda, aux);
          }
        }
        // arriba
        if (0 < i) {
          aux = matriz[i - 1][j];
          if (esPiso(aux)) {
            verNodo(i - 1, j, arriba, aux);
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
        ejes[countEjes] = e;
        countEjes++;

      } else if (ejercicio == 1 && aux == '#') {
        int arriba, abajo, izquierda, derecha, index;
        // Tomo/inicializo el nodo
        verNodo(i, j, index, aux);
        nodos[index]->esPared = true;
        arriba = -1;
        abajo = -1;
        izquierda = -1;
        derecha = -1;
        // A la derecha
        if (j < c - 3) {
          aux = matriz[i][j + 1];
          if (esPiso(aux)) {
            verNodo(i, j + 1, derecha, aux);
            Eje *e = new Eje(countEjes, 1, nodos[index], nodos[derecha]);
            nodos[index]->ejes.push(e);
            nodos[index]->pushearEje(e);
            nodos[derecha]->ejes.push(e);
            nodos[derecha]->pushearEje(e);
            ejes[countEjes] = e;
            countEjes++;
          }
        }
        // Abajo
        if (i < f - 3) {
          aux = matriz[i + 1][j];
          if (esPiso(aux)) {
            verNodo(i + 1, j, abajo, aux);
            Eje *e = new Eje(countEjes, 1, nodos[index], nodos[abajo]);
            nodos[index]->ejes.push(e);
            nodos[index]->pushearEje(e);
            nodos[abajo]->ejes.push(e);
            nodos[abajo]->pushearEje(e);
            ejes[countEjes] = e;
            countEjes++;
          }
        }
        // A la izquierda
        if (0 < j) {
          aux = matriz[i][j - 1];
          if (esPisoPared(aux)) {
            verNodo(i, j - 1, izquierda, aux);
            Eje *e = new Eje(countEjes, 1, nodos[index], nodos[izquierda]);
            nodos[index]->ejes.push(e);
            nodos[index]->pushearEje(e);
            nodos[izquierda]->ejes.push(e);
            nodos[izquierda]->pushearEje(e);
            ejes[countEjes] = e;
            countEjes++;
          }
        }
        // arriba
        if (0 < i) {
          aux = matriz[i - 1][j];
          if (esPisoPared(aux)) {
            verNodo(i - 1, j, arriba, aux);
            Eje *e = new Eje(countEjes, 1, nodos[index], nodos[arriba]);
            nodos[index]->ejes.push(e);
            nodos[index]->pushearEje(e);
            nodos[arriba]->ejes.push(e);
            nodos[arriba]->pushearEje(e);
            ejes[countEjes] = e;
            countEjes++;
          }
        }
        countParedes++;
      }
    }
  }
  // count--;
  nodos[count] = nodos.back();
  count++;
  nodos.resize(count);
  ejes.resize(countEjes);
  for (size_t i = 0; i < nodos.size(); i++) {
    nodos[i]->resizearEjes();
  }
  return min(p, countParedes);
}

void correr(int rep, ofstream & res, string test, int c, int f, int p){
	uint64_t begin, end, elapsed_secs, elapsed_final;
	elapsed_secs = 0;
	res<<c << " & "<< f<<" & "<<p;
	vector<Nodo *> nodos;
	vector<Eje *> ejes;
	for(int i = 0; i< rep; i++){
		int paredes = parsearInputAux(nodos, ejes, 1, test);
		begin = rdtsc();
		Solucion(nodos, ejes, paredes);
		end = rdtsc();
		elapsed_secs += end - begin;
		ejes.clear();
		nodos.clear();
		res<<" & "<<elapsed_secs;
	}
	res<<"\n";
}

//elige un x e y tal que este a i distancia del (1,1) como bfs, f y c son las filas  las columnas de la matriz
void ElegirDiagonal(int i, int & x, int & y, int f, int c){
	x = i /2;
	y = i - x;
	if(x >f){
		x = f;
		y = i - x;
	}
}

void MantengoValoresCambioDestino(int rep){
	/* ##### La idea es poner el destino en las diagonales, las diagonales representan la distancia que estan del origen
	 * #012# Me gustaria ver como es solo con puntos y despues me gustaria ver como es con algunas paredes en el medio y a que la pared hace cosas?
	 * #123# Creo que no, solo aumentaria la complejidad de clonar.
	 * #234#
	 * #####
	 */
	 
	 int f, c, p;
	 f = c = 50;
	 p = 0;
	 ofstream res("resultadosMVCD.txt");
	 string ts = "inputMVCD.txt";
	 ofstream caso(ts);
	 for(int i = 1; i<= c+f; i++){
		 int x, y;
		 ElegirDiagonal(i,x,y,f,c);
		 for(int j = -1; j<=c; j++){
			 for(int l = -1; l<= f; l++){
				 if(l== -1 || l == f || j == -1 || j == c){
					 caso <<"#";
					 continue;
				 }
				 if(l == 0 && j == 0){
					 caso<< "o";
					 continue;
				 }
				 if(l == x && j == y){
					 caso<<"x";
					 continue;
				 }
				 caso<<".";
			 }
			 caso<<"\n";
		 }
		 Correr(rep, res, ts,c ,f, p);
	 }
	 
}

void MantengoValoresAumentoCantParedes(int rep){
	int f, c, p;
	ofstream res("SolucionesAumentoParedesConstante.txt");
	f = c = 20;
	p = 50;
	vector<Nodo *> nodos;
	vector<Eje *> ejes;
	for(int i = p; i< (f-2)*(c-2)-3; i++){
		uint64_t begin, end, elapsed_secs, elapsed_final;
		elapsed_secs = 0;
		for(int i = 0; i< rep; i++){
			int paredes = parsearInput(nodos, ejes, f, c, p, p + i);
			begin = rdtsc();
			Solucion(nodos, ejes, paredes);
			end = rdtsc();
			elapsed_secs += end - begin;
			ejes.clear();
			nodos.clear();
			}
		elapsed_final = elapsed_secs / repeticiones;
		res << f << '|' << c << '|' << p + i << '|' << elapsed_final << endl;
	}
}



int main(int argc, char *argv[]) {
  
  return 0;
}
