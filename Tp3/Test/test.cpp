//#include "../clases.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <limits>
#include <tuple>
#include "../Punto1/pto1.cpp"
#include "../Punto1/pto1A.cpp"
//#include "../Punto2/Punto2.cpp"
//#include "../Punto3/ej3.cpp"
//#include "../Punto4/pto4.cpp"*/

using namespace std;

#define ya chrono::high_resolution_clock::now

void  AsignarIndices(vnod & gim, vnod & pp){
	vnod gimAux;
	vnod ppAux;
	for(int i = 0; i< gim.size(); i++){
		Nodo aux(gim[i], i+1);
		gimAux.push_back(aux);
	}
	int n = gim.size();
	for(int i = 0; i<pp.size(); i++){
		Nodo aux(pp[i], n+i+1);
		ppAux.push_back(aux);
	}
	gim = gimAux;
	pp = ppAux;
}

void Correr(int rep, vnod gimnasios, vnod pokeparadas, Mochila moch, ofstream & res, int nroEj){
	int valor;
	vector<int> sol;
	double (* foo)(vnod,vnod, Mochila,vint &);
	switch(nroEj){
		case 1:
		foo = &pto1;
		break;
		/*case 2:
		foo = &pto2;
		break;
		case 3:
		foo = &pto3;
		break;
		case 4:
		foo = &pto4;
		break;*/
		default:
		cout<<"N invalido"<<endl;
		res<<"\n";
		return;
	}
	valor = (double) foo(gimnasios, pokeparadas, moch, sol);

	res <<valor<<" & ";
	for(int i = 0; i< sol.size(); i++) res<<sol[i]<< " ";
	res <<"& ";
	for(int i = 0; i < rep; i++){
		sol.clear();
		long tiempo = 0;
		auto start = ya();
		foo(gimnasios, pokeparadas, moch, sol);
		auto end = ya();
		tiempo = chrono::duration_cast<chrono::nanoseconds>(end-start).count();
		res<<tiempo<<" & ";
	}
	res<<"\n";
}


/*
void PPdeMas(){}
*/
void RectaPPgim(int rep, int cantgim){
	ofstream res("resultadossRectaSinMoch.txt");
	ofstream casos("casos.txt");
	ofstream podas("podasRectaSinMoch.txt");
	vnod gimnasios;
	vnod pp;
	srand(time(NULL));
	res<<"pto & cantidad de gimnasios & cantidad de pokeparadas & distancia & resultado & ... tiempos ...& \n";
	podas<<"cant Gim & cant pp & cantidad de llamadas al BT sin podas & distancia & recorrido";
	podas<<" & #BT con Poda A & distancia & recorrido & #BT con Poda B & distancia & recorrido";
	podas<<" & #BT con Poda c & distancia & recorrido & #BT con Poda AB & distancia & recorrido";
	podas<<" & #BT con Poda AC & distancia & recorrido & #BT con Poda BC & distancia & recorrido";
	podas<<" & #BT con Poda ABC & distancia & recorrido\n";
	casos<<"La idea es saber como estan conformados los casos gimansios & pp \n";
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
		AsignarIndices(gimnasios, pp);
		if(21 > pp.size()+gimnasios.size()){
			for(int nroEj = 1; nroEj <= 4; nroEj++){
				res<<nroEj<<" & "<<i << " & "<< ppTotales<<" & ";
				Correr(rep, gimnasios, pp, moch, res, nroEj);
			}
			//me va a dar numeros dependiendo de que poda use
			if(13 > pp.size()+gimnasios.size()){
				podas << gimnasios.size() << " & "<<pp.size() << " & ";
				CorrerPodas(gimnasios, pp, moch, podas);
				podas<<"\n";
			}
			for(int i = 0; i<gimnasios.size();i++) casos<<"("<<gimnasios[i].CordenadaX()<<","<<gimnasios[i].CordenadaY()<<")["<<gimnasios[i].DamePociones()<<"] ";
			casos<<" & ";
			for(int i = 0; i< pp.size();i++) casos<<"("<<pp[i].CordenadaX()<<","<<pp[i].CordenadaY()<<") ";
			casos<<"\n";
		}
		else{
			for(int nroEj = 2; nroEj <= 4; nroEj++){
				res<<nroEj<<" & "<<i << " & "<< ppTotales<<" & ";
				Correr(rep, gimnasios, pp, moch, res, nroEj);
			}
		}
	}
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
void gruposSeparados (vnod& gym, vnod& pepe, const int &a, const int &b ){

}
auto generadorDeEspirales(int a, int b){
	auto espiral = [x=0,y=0,dx = 0,dy = -1,a=a,b=b]() mutable{ //espiral.. girasol... lo q sea..
		//cout<<x+a<<" "<<y+b<<endl;
		if ((x == y) or (x < 0 and x == -y) or (x > 0 and x == 1-y)){
			int swapy=dx;
			dx=-dy;
			dy=swapy;
		}
		x = x+dx;
		y=y+dy;
		return make_tuple(x,y);
	};
	return espiral;
}

int main(){
	//RectaPPgim(1, 10);
	std::vector<tuple<int,int> > v;
	auto espiral = generadorDeEspirales(20,20);
	for (size_t i = 0; i < 100000000; i++) {
	//	espiral();
	v.push_back(espiral());
	}
	cout<<v.size()<<endl;

}
