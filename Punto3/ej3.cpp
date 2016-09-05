#include "ej3.h"
//#include<iostream>
#include<fstream>

using namespace std;

Tesoro::Tesoro(int p, int t, int v):peso(p), tipo(t), valor(v){
}

int Tesoro::Peso(){
	return peso;
}

int Tesoro::Tipo(){
	return tipo;
}

int Tesoro::Valor(){
	return valor;
}

string Tesoro::Imprimir(){
	string s = to_string(tipo);
	return s;
}

Mochila::Mochila(int p):cap(p){
}

Mochila::Mochila():cap(0){
}

void Mochila::Agregar(Tesoro o){
	cap = cap - o.Peso();
	tes.push_back(o);
}

int Mochila::Capacidad(){
	return cap;
}

void Mochila::Imprimir(){
	cout << tes.size() << " ";
	for(unsigned int i = 0; i< tes.size(); i++){
		cout <<tes[i].Imprimir()<<" ";
	}
	cout << "\n";

}

int Maximo(vector<int> obj){
	int elem = 0;
	for(unsigned int i = 0; i<obj.size(); i++){
		if(elem < obj[i]){
			elem = obj[i];
		}
	}
	return elem;
}
//la funcón toma un hipercubo (una matriz en 4 dimensiones), un vector de tesoros, el indice del objeto, y los pesos de las mochilas.
int CalcularOptimo(vector<vector<vector<vector<int> > > >& objetoxPesos,vector<Tesoro>& cofre, int objeto, int peso1, int peso2, int peso3){
	int pesoObj = cofre[objeto].Peso();
	int valorObj = cofre[objeto].Valor();
	//esto nunca se llama en la construccion del hipercubo, pero si en la deconstrucion, para hacer mas legible el codigo.
	if(peso1 < 0 || peso2 < 0 || peso3 < 0){
		return -1;
	}
	//-1 implica no calculado.
	if(objetoxPesos[objeto][peso1][peso2][peso3] != -1){
		return objetoxPesos[objeto][peso1][peso2][peso3];
	}
	//caso base.
	if(objeto == 0){
		int val = 0;
		if(peso1 >= pesoObj || peso2 >= pesoObj || peso3 >= pesoObj) val = valorObj;
		objetoxPesos[objeto][peso1][peso2][peso3] = val;
		return val;
	}
	else{
		//recursiones dependiendo de donde se pone el objeto
		int sinObj = CalcularOptimo(objetoxPesos, cofre, objeto -1, peso1, peso2, peso3);
		//vector con posibles soluciones
		vector<int> objetos;
		objetos.push_back(sinObj);
		if(peso1-pesoObj >= 0){
			int objen1 = valorObj + CalcularOptimo(objetoxPesos, cofre, objeto - 1, peso1 - pesoObj, peso2, peso3);
			objetos.push_back(objen1);
		}
		if(peso2 - pesoObj >= 0){
		int objen2 = valorObj + CalcularOptimo(objetoxPesos, cofre, objeto - 1, peso1, peso2  - pesoObj, peso3);
		objetos.push_back(objen2);
		}
		if(peso3-pesoObj >= 0){
		int objen3 = valorObj + CalcularOptimo(objetoxPesos, cofre, objeto - 1, peso1, peso2, peso3  - pesoObj);
		objetos.push_back(objen3);
		}
		int valor = Maximo(objetos);
		objetoxPesos[objeto][peso1][peso2][peso3] = valor;
		return valor;
	}
}

void MeterEnCorrecta(int valM1, int valM2, int valM3, Mochila& m1, Mochila& m2, Mochila& m3, Tesoro obj){
	if(valM1 == 0){
			m1.Agregar(obj);
	}else
	 if(valM2 == 0){
				m2.Agregar(obj);
		}else if(valM3== 0){
					m3.Agregar(obj);
		}
}

void LlenarMochilas(vector<vector<vector<vector<int> > > >& objetoxPesos,vector<Tesoro>& cofre, Mochila& m1, Mochila& m2, Mochila& m3){
	int i=cofre.size()-1;
	while(i>=0){
		//la capacidad de cada mochila se va updeteando cada vez que guardas algo
		int cap1 = m1.Capacidad();
		int cap2 = m2.Capacidad();
		int cap3 = m3.Capacidad();
		Tesoro obj(cofre[i]);
		int pesoObj = obj.Peso();
		int valorObj = obj.Valor();
		int valActual = objetoxPesos[i][cap1][cap2][cap3];
		if(i == 0){
			if(cap1 >= pesoObj){
				m1.Agregar(obj);
			}else if(cap2>=pesoObj){
					m2.Agregar(obj);
				}else if(cap3 >= pesoObj){
						m3.Agregar(obj);
					}
		}else{
			/*se llama a calcularOptimo, lo que podria suponer un problema en la complejidad, pero en realidad es O(1) ya que estamos acediendo a valores
			  pre calculados, no accedo a la matriz directamente por que cap1-pesoObjj puede ser negativo.
			  le pongo un 0 al maxValor ya que como dije antes no estoy construyendo nada*/
			int valM1 = valorObj + CalcularOptimo(objetoxPesos, cofre, i - 1, cap1 - pesoObj, cap2, cap3) - valActual;
			int valM2 = valorObj + CalcularOptimo(objetoxPesos, cofre, i - 1, cap1, cap2 - pesoObj, cap3) - valActual;
			int valM3 = valorObj + CalcularOptimo(objetoxPesos, cofre, i - 1, cap1, cap2, cap3 - pesoObj) - valActual;
			//decide cual mochila es la que efectivamente se lleno, si no se lleno ninguna no mete el objeto.
			MeterEnCorrecta(valM1, valM2,valM3, m1,m2,m3,obj);
		}
		i--;
	}


}

int solucion(string test){
	int m;
	int n;
	int pesomax = 0;
	int sol = 0;
	fstream input;
	input.open(test);
	input>> m>> n;
	vector<Mochila> mochilas(3);
	//Creo las mochilas y las pongo en un vector
	for(int i = 0; i<3; i++){
		int k = 0;
		if(i<m)	input >> k;
		if(k>pesomax) pesomax = k;
		Mochila m(k);
		mochilas[i] = m;
	}
	//Meto los tesoros en el cofre, tener en cuenta que tesoros
	// con peso mayor que la capacidad se descartan aca.
	vector<Tesoro> cofre;
	for(int i = 0; i <n; i++){
		int cant;
		int p;
		int v;
		input>> cant>> p>> v;
	//(usar este cout para saber que tipos responden a que valores/peso
	//.cout<<"Hay "<<cant << " tesoros de tipo " <<i <<" de peso " << p <<" de valor " << v<<endl;
		if(p <= pesomax){
			for(int j = 0;j < cant; j++){
				cofre.push_back(Tesoro(p,i,v));
			}
		}
	}
	input.close();
	if (cofre.size()==0) {
		cout<< sol<<"\n";
		for(int i = 0; i<m;i++){
			mochilas[i].Imprimir();
		}
		return 1;
	}
	//incializo en -1 la matriz ya que en la función recursiva, si es -1 implica que no lo calculo y tiene que hacerlo.
	vector<int> m3(mochilas[2].Capacidad()+1, -1);
	vector<vector<int> > m2ym3(mochilas[1].Capacidad()+ 1, m3);
	vector<vector<vector<int> > >m1ym2ym3(mochilas[0].Capacidad()+1, m2ym3);
	vector<vector<vector<vector<int> > > >  objXpesos(cofre.size(),m1ym2ym3);

	//para no complicar el algoritmo calcularOptimo, pongo todas las posiciones donde no puede haber objetos en 0, entonces piensa que ya lo calculamos.
	for(unsigned int i = 0; i< cofre.size(); i++) objXpesos[i][0][0][0] = 0;//O(cofre.size())
	sol = CalcularOptimo(objXpesos, cofre, cofre.size()-1, mochilas[0].Capacidad(), mochilas[1].Capacidad(), mochilas[2].Capacidad());
	/*
	 en el peor dde los casos tengo que calcular todos las posiciones del hipercubo, una sola vez, eso es
	 */

	LlenarMochilas(objXpesos, cofre, mochilas[0], mochilas[1], mochilas[2]);//O(cofre.size())

	cout<< sol<<"\n";
	for(int i = 0; i<m;i++){
		mochilas[i].Imprimir();
	}

	return 0;
}
/*
int main(int argc, char *argv[]){
	string test = argv[1];
	solucion(test);
	return 0;
}*/

