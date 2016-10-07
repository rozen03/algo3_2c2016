#include "../eje.h"
#include "../estructuras.h"
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;
//Busqueda lineal return

void Imprimir(vector<Nodo *>& nodos){
	
	for(int i=0; i<nodos.size(); i++){
			cout<< nodos[i]->indice;
			vector<Eje *> vectEjes = nodos[i]->ejejes;
			for(int j=0; j<vectEjes.size(); j++){
				Nodo * nodin = vectEjes[j]->dameNodo();
				cout <<"("<< nodin->indice<<", "<<vectEjes[j]->dameElOtroNodoPorfa(nodin)->indice<<")";
			}
			cout<< " "<<endl;
		}
}

int Bfs(vector<Nodo *>& nodos){
	vector<int> pred(nodos.size(), -1);
	vector<int> orden(nodos.size(), -1);
	vector<Eje *> ejesAux(nodos.size(), NULL);
	//como consumo la cola de prioridad guardo el eje, representa el eje
	//que une a la iesima posicion del arreglo pred con el valor del nodo.
	queue<tuple<int, int> > list;
	tuple<int, int> prim(0, -3); 
	list.push(prim);
	int next = 0;
	while(!list.empty()){
		tuple<int, int> aux = list.front();
		list.pop();
		int nod = get<0>(aux);
		int padre = get<1>(aux);
		if(orden[nod] == -1){
			pred[nod] = padre;
			orden[nod] = next;
			next++;
			Nodo* nodin = nodos[nod];
			vector<Eje *> ejesNodin = nodin -> ejejes;
			//agregamos los ejes que estan conectados
			for(unsigned int i=0 ; i<ejesNodin.size(); i++){
				cout<<"Entro a aristas que pueden o no estar en la lista \n";
				Eje * ejeaux = ejesNodin[i];				
				Nodo * nodoaux = ejeaux ->dameElOtroNodoPorfa(nodin);
				int acomp = nodoaux -> indice;
				cout<<"la arista puede ser "<<"("<<acomp<<", "<<nod<<")";
				//si ya lo tagee o estoy bajando a una instancia invalida, reconstruir una pared
				if(orden[acomp] != -1 || nodoaux->nivel < nodin->nivel) continue;
				// estamos en el mismo nivel pero estoy rompiendo una pared, tendria que subir de nivel
				if(nodoaux -> nivel == nodin -> nivel &&  nodoaux -> esPared) continue; 
				tuple<int, int> arist(acomp, nod);
				cout<<" meti la arista"<<endl;
				list.push(arist);				
			}
		}
	}
	cout<<"Termine el while bfs"<<endl;
	/*
	//pred tiene la informacion de los ejes, la posicion i te dice quien es el padre
	//para crear los nodos tenes que tener una copia limpia de los nodos y buscar el eje que
	//corresponda, fijarse que como es priority queue por ahi tenes que guardas los ejes que no eran
	//en una auxiliar y despues asignarlo devvuelta a los ejes del nodo.
	vector<Nodo *> nodosNuevos;
	for(int i = 0; i<nodos.size(); i++){
		Nodo * aux = new Nodo(i);
		nodosNuevos.push_back(aux);
	}
	
	//creo un arreglo para ver si ya meti el eje que conecta dos vertices, por ejemplo el 12 lo meteria dos veces sin darme cuenta si no hago esto
	vector<int> metido(nodos.size(), -1);
	//son dos fors por que necesitaba inicializar el arreglo primero.
	for(int i = 1; i < nodos.size(); i++){
		if(metido[i] == -1){
			Eje * ejeaux = ejesAux[i];
			int pad = pred[i];
			metido[i] = 0;
			metido[pad] = 0;
			Nodo * hijo = nodosNuevos[i];
			
			Nodo * padre = nodosNuevos[pad];
			hijo -> ejes.push_back(ejeaux);
			padre -> ejes.push_back(ejeaux);
		}
	}
	nodos = nodosNuevos;
	for(int i=0; i<nodosNuevos.size(); i++){
			cout<< nodosNuevos[i]->indice;
			vector<Eje *> vectEjes = nodosNuevos[i]->ejes;
			for(int j=0; j<vectEjes.size(); j++){
				Nodo * nodin = vectEjes[j]->dameNodo();
				cout <<"("<< nodin->indice<<", "<<vectEjes[j]->dameElOtroNodoPorfa(nodin)->indice<<")";
			}
			cout<< " "<<endl;
	}*/
	
	int x= nodos.size()-1;
	int res=2;
	int aux = 0;
	for(int i = nodos.size()-1; 0<= i;i--){
		cout<<"el predecesor de "<<i<<" es "<< pred[i]<<endl; 
	}
	
	while(aux < nodos.size()){
		cout<<"el pred de "<<x<<" es "<<pred[x]<<" res es "<<res<<endl;
			x= pred[x];
			if(x == 0 || x == -1) break;
			res++;
			aux++;
	}
	if(x==-1){
			return -1;
	}
	else{
			return res;
	}
}

int Solucion(vector<Nodo *>& nodos, vector<Eje *>& ejes, int p){
	int res=2*nodos*p.size();
	for(int i=0; i<=p; i++){
		cout<<"entre a solucion con "<<i<<" paredes rotas y puedo romper "<<p<<endl;
			int respar=Bfs(nodos);
			cout<<"sali Bfs y la respar es "<<respar<<endl;
			clonarUltimoNivel(nodos,ejes);
			cout<<"deje de clonar"<<endl;
			Imprimir(nodos);
			if(respar< res && respar!=-1){
					res=respar;
			}
		}
	if(res==2*nodos.size()){
			res=-1;
	}
	cout<<"termine todo y res es " <<res<<endl;
	return res;
}

int main(int argc, char *argv[]) {
  std::vector<Nodo *> nodos;
  std::vector<Eje *> ejes;
<<<<<<< HEAD
  parsearInput(nodos,ejes,1);

  cout<<"fin parsear"<<endl;

	clonarUltimoNivel(nodos,ejes);
  clonarUltimoNivel(nodos,ejes);
  clonarUltimoNivel(nodos,ejes);
  clonarUltimoNivel(nodos,ejes);
  clonarUltimoNivel(nodos,ejes);
	cout<<"fin clon"<<endl;
=======
  int p = 0;
  p = parsearInput(nodos,ejes,1);
  int res = Solucion(nodos, ejes, p);/*
>>>>>>> 4729852da08cef018106430829c4418596f65149
  for (size_t i = 0; i < nodos.size(); i++) {
    std::cout << nodos[i]->indice << std::endl;
  }
  for (size_t i = 0; i < ejes.size(); i++) {
    std::cout <<ejes[i]->n1->indice<<" "<<ejes[i]->n2->indice<<" "<<ejes[i]->peso  << std::endl;
  }
  //Bfs(nodos);*/

  return 0;
 }
