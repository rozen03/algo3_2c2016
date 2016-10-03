#include <vector>
#include <iostream>
#include <tuple>

using namespace std;

 //Genera todos los posbiles destinos y origenes sin contar uno mismo ya que no seria un digrafo;
 vector<tuple<int,int> > todasComb(int nodos){
	 vector<tuple<int, int> > posibles;
	 for(int i = 1; i<=nodos; i++){
		for(int j = i+1; j<=nodos;j++){
			tuple<int,int> aux(i,j);
			posibles.push_back(aux);
		}
	}
	return posibles;
 }
 
 
//va a ser lineal en tamaño de nodos n^2 podria ser mas inteligente ya que se puede calcular en que posicion, pero da paja
void sacarComb(vector<tuple<int, int> >& posibles, int origen, int destino){
	unsigned int i = 0;
	while(i< posibles.size()){
		int ori = get<0>(posibles[i]);
		int dest = get<1>(posibles[i]);
		if(ori == origen && dest == destino){
			unsigned int n = posibles.size()-1;
			posibles[i] = posibles[n];
			posibles.pop_back();
			break;
		}
		i++;
	}
}

//crea un grafo conexo nodos y ejes
vector<vector<int> > CrearConexo(int nodos, int ejes){
	vector<int> fila(nodos+1, -1);
	vector<vector<int> > mat(nodos+1, fila);
	if(ejes < nodos || ejes > (nodos-1)*(nodos-2)/2){
		cerr<< "Te fuiste de rango, no podes crear un grafo conexo con "<<nodos <<" nodos y "<<ejes<<" ejes..."<<endl;
		break;
	}
	int i = 1;
	vector<tuple<int,int> > posibles = todasComb(nodos);
	srand(time(NULL));
	while(i<=ejes){
		int origen;
		int destino;
		int tiempo = rand()%9 +1;
		if(i <nodos ){
			origen = i;
			destino = i+1;
		}
		else{
			int pos = rand()%posibles.size();
			origen = get<0>(posibles[pos]);
			destino = get<1>(posibles[pos]);
		}	
		filaycolum[origen][destino] = tiempo;
		filaycolum[destino][origen] = tiempo;
		sacarComb(posibles,origen,destino);
		i++;
	}	
}
