#include "../clases.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <limits>
using namespace std;

void Corrrer(int rep, vnod gimnasios, vnod pokeparadas, Mochila moch, ofstream res){
	
}
/*
void PPdeMas(){}
*/
void RectaPPgim(int rep, int cantgim){
	ofstream res("resultadossRectaSinMoch.txt");
	vnod gimnasios;
	vnod pp;
	srand(time(NULL));
	res<<"la idea es tener una recta tal que todas las pp que necesitas para ganar un gimnasio las tenes antes de llegar\n";
	res<<"cantidad de gimnasios & cantidad de pokeparadas & distancia & resultado & ... tiempos ...& \n";
	//indice emula como funciona el indice de los nodos en la lectura
	int indicePP = cantgim+1;
	int ppTotales = 0;
	//no me importa la mochila aca
	Mochila moch(30);
	for(int i = 1; i<=cantgim; i++){
		int cantpp = rand()%10 + 1;
		ppTotales += cantpp;
		
		Nodo gim(-3*cantpp,i , ppTotales + i-1, 0);
		gimnasios.push_back(gim);
		for(int j = 1; j<=cantpp; j++){
			//son las pokeparadass que ya agregue, mas los gimsios que ya agregue mas las pokeparadas que estoy agregando en este for, el menos dos es por que quiero empezar en el 0,0
			Nodo pokeparada(3, indicePP, ppTotales- cantpp +i + j - 2 , 0);
			indicePP++;
			pp.push_back(pokeparada);
		}
		res<<i << " & "<< ppTotales<<" & ";
		Correr(rep, gimansios, pp, moch, res);
	}
	cout<<"Los gimnasios son: ";
	for(int i = 0; i<gimnasios.size(); i++){
		Nodo aux = gimnasios[i];
		cout<<"("<<aux.CordenadaX()<<","<<aux.CordenadaY()<<")["<<aux.DameIndice()<<"] "<<aux.DamePociones()<<" , ";
	}
	cout<<"\nLas Pokeparadas son: ";
	for(int i = 0; i<pp.size(); i++){
		Nodo aux = pp[i];
		cout<<"("<<aux.CordenadaX()<<","<<aux.CordenadaY()<<")["<<aux.DameIndice()<<"], ";
	}
	cout<<endl;
	res.close();
}
/*
void PrimeroSeVaAlasPPyDespuesGim(){}

void Fibonacci(){}

void Girasol(){}

void LLenar(vnod & gim, vnod & pp, vector<Cuadrado> & zonaRest, int x, int y){
	
}


void Buscar(int & x, int & y, const vector<Cuadrado> & zonaRest, int ppNecesaria){
	
}

void PokeParadasAlLadoGimMochNoImporta(int rep, int cantgim){
	ofstream res("ResultadosPPAlLadoSinLimiteMoch.txt");
	vnod gimnasios;
	vnod pp;
	vector<Cuadrado> zonaRestringida;
	res<<"cantidad de gimnasios & cantidad de pokeparadas & distancia & resultado & ... tiempos ...& \n";
	res.close();
	for(int i = 1; i<=cantgim; i++){
		int poc =rand()% 30 + 1;
		int ppNecesarias = poc / 3;
		if(poc % 3 != 0) ppNecesarias++;
		int x, y;
		if(!zonaRestringida.empty()){
			x = abs(rand());
			y = abs(rand());
			Llenar(gimnasios, pp, zonaRestringida, x, y);
		}
		Buscar(x, y, zonaRestringida, ppNecesarias);
		Llenar(gimnasios, pp, zonaRestringida, x, y);
		Correr(rep, gimansios, pp, res);
	}
}
*/
int main(){
	RectaPPgim(1, 10);
}
