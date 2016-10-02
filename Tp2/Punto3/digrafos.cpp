#include <vector>
#include <tuple>
#include <iostream>
#include <fstream>

using namespace std;
/*
 La representacion de los grafos es una matriz de adyacencia
 mat[origen][destino] el primer int de la tupla seria el tiempo y el segundo el predesesor
 */
 //Genera todos los posbiles destinos y origenes sin contar uno mismo ya que no seria un digrafo;
 vector<tuple<int,int> > todasComb(int nodos){
	 vector<tuple<int, int> > posibles;
	 for(int i = 1; i<=nodos; i++){
		for(int j = 1; j<=nodos;j++){
			if(i == j) continue;
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
 
 //crea una mat ady de un grafo conexo con esa cantidad de nodos y ejes
vector<vector<tuple<int,int> > > CrearConexo(int nodos, int ejes){
	//cout<<"Entre a crear conexo con nodos y ejes respectivamente " << nodos <<" "<<ejes<<endl;
	tuple<int,int> basura(-1,0);
	vector<tuple<int,int > > fila(nodos+1, basura);
	vector<vector<tuple<int,int> > > filaycolum(nodos+1,fila);
	if(nodos - 1 > ejes || ejes > (nodos)*(nodos) - nodos){
		cout<<"no es posible crear conexo con nodos " << nodos << " y "<< ejes<<endl;
	}
	else{
		int i = 0;
		vector<tuple<int,int> > posibles = todasComb(nodos);
		srand(time(NULL));
		while(i<ejes){
			int origen;
			int destino;
			int tiempo;
			if(i <nodos -1){
				origen = i+1;
				destino = i+2;
				tiempo = rand()%1000+1;
				tuple <int, int> elem(tiempo, origen);
				filaycolum[origen][destino] = elem;
				sacarComb(posibles, origen, destino);
				i++;
			}
			else{
				int pos = rand()%posibles.size();
				origen = get<0>(posibles[pos]);
				destino = get<1>(posibles[pos]);
				sacarComb(posibles,origen,destino);
				tiempo = rand()%1000+1;
				tuple<int, int> elem(tiempo, origen);
				tuple<int, int> elem2(0, origen);
				//if(origen == 1&& destino == nodos) elem = elem2;
				int val = get<0>(filaycolum[origen][destino]);
				filaycolum[origen][destino] = elem;
				i++;
			}
		}	
	}
	return filaycolum;
}

/*
 La idea es, tengo n nodos y creo dos componentes conexas donde en
 una estan los primeros part nodos y en la otra los demas, cada comp
 conexa es un k grafo, por que pinto.
 */
vector<vector<tuple<int,int> > > compConexa(int nodos, int part){
	vector<vector<tuple<int,int> > > v1;
	int kpart = (part)*(part) - part;
	v1 = CrearConexo(part, kpart);
	vector<vector<tuple<int, int> > > v2;
	int knpart = (nodos-part)*(nodos-part)-(nodos-part);
	v2 = CrearConexo(nodos-part, knpart);
	tuple<int,int> basura(-1, 0);
	vector<tuple<int, int> > fila(nodos+1, basura);
	vector<vector<tuple<int,int> > > mat(nodos+1, fila);
	
	for(int i = 1; i<= nodos; i++){
		for(int j = 1; j<= nodos; j++){
			if(i <= part && j<=part){
				mat[i][j] = v1[i][j];
			}
			if(i > part && j  > part){
				tuple<int,int> aux = v2[i-part][j-part]; 
				int tiempo = get<0>(aux);
				int pred = 0;
				if(get<1>(aux) !=0) pred = get<1>(aux)+part;
				tuple<int, int> nueva(tiempo, pred);
				mat[i][j] = nueva;
			}
		}
	}
	return mat;
}

void EscrituraDato(const vector<vector<tuple<int,int> > >& mat, string output){
	ofstream op(output);
	int n = mat.size() -1;
	int m = 0;
	for(unsigned int i = 0; i<mat.size(); i++){
		for(unsigned int j = 0; j<mat.size(); j++){
			if(get<0>(mat[i][j]) != -1) m++;
		}
	}
	op << n<< " "<<m<<"\n";
	for(unsigned int i = 0; i<mat.size(); i++){
		for(unsigned int j = 0; j<mat.size(); j++){
			int tiempo = get<0>(mat[i][j]); 
			if(tiempo != -1){
				op<<i<<" "<<j<<" "<<tiempo<<"\n";
			}
		}
	}
	op.close();
}

void Imprimir(const vector<vector<tuple<int,int> > >& mat){
		cout<<"La matriz de " <<mat.size() -1 <<" nodos, tiene la siguiente forma \n";
		for(unsigned int i = 0; i <mat.size();i++){
			for(unsigned int j = 0; j< mat.size(); j++){
				cout<<"("<<get<0>(mat[i][j])<<","<<get<1>(mat[i][j])<<") ";
			}
			cout<<"| \n";
		}
		cout<<endl;
}

void CrearConex(){
	for(int i = 4; i<=9; i++){
		string is = to_string(i);
		string ts = is+"nodos10ejes.txt";
		vector<vector<tuple<int,int> > > prueba;
		prueba = CrearConexo(i,10);
		EscrituraDato(prueba, ts);
	}
}

void testcomConex(){
	for(int i =1; i< 10; i++){
		vector<vector<tuple<int,int> > > prueba;
		prueba = compConexa(10, i);
		cout<<"tiene que estar particionado en el "<<i<<" nodo"<<endl;
		Imprimir(prueba);
	}
}
/*
int main(){
	//CrearConex();
	string ts = "K10.txt";
	vector<vector<tuple<int,int> > > prueba;
	prueba = CrearConexo(10, 90);
	EscrituraDato(prueba,ts);
	//testcomConex();
}
*/
