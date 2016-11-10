//#include "../clases.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <limits>
#include <tuple>
#include <functional>
#include "../Punto1/pto1.cpp"
#include "../Punto1/pto1A.cpp"
//#include "../Punto2/Punto2.cpp"
#include "../Punto3/ej3.cpp"
#include "../Punto4/pto4.cpp"

//Funciones Auxiliares
//basicamente hace correr y correr podas.
void CorrerGeneral(int rep, vnod gim, vnod pp, Mochila moch,ofstream & res, ofstream & meta, ofstream & podas);

//imprime los casos en un archivo separado.
void ImprimirCasos(vnod & gim, vnod & pp, ofstream & casos);

//Este correr se encarga de ejecutar los casos con todos los ejercicios
void Correr(int rep, vnod gim, vnod pokeparadas, Mochila moch, ofstream & res, ofstream & meta, int nroEj);

//Esto nos deja crear los gimnasios y los nodos sin preocpuarnos por los indices, ya que esta funcion se encarga
void AsignarIndices(vnod & gim, vnod & pp);

/*esto te dice cuantas pokeparadas te sobran o necesitas, sabiendo cuantas tenes y la capacidad de la mochila.
pociones de gim tiene cuantas pociones necesita cada gimnasio.
negativo cuantas te sobran positivo cuantas necesitas.
*/
int ElegirSoloNecesarias(vint pocionesDeGim, int cantPP, int capMoch);

//Generadores de casos
//hace una recta no importa la mochila y el camino mas corrto es caminar la recta.
void RectaPPgim(int rep, int cantgim);

//Hace una recta, pero la mochila si importa, ya que la cantidad de pokeparadas esta ajustada al maximo.
void SoloPokeparadasNecesariasRecta(int rep, int cantgim);

using namespace std;

#define ya chrono::high_resolution_clock::now

int ElegirSoloNecesarias(vint pocionesDeGim, int cantPP, int capMoch){
	//la idea de bucket es ordenar la cantidad de pociones de Gim dependiendo cuantas se requiere.
	/*
	La idea es de menor a mayor, fijarse cuantas pociones me sobran en la mochila e ir agregando solo lo necesario.
	 */
	vector<int> bucket(capMoch, 0);
	//meto en el bucket
	for(int i = 0; i < pocionesDeGim.size(); i++){
		int pocAux = pocionesDeGim[i];
		if(pocAux > 0) bucket[pocAux-1]++;
	}
    /*
	 La deconstruccion va de menor a mayor, ya que asi voy metiendo solo lo necesario y supuestamene guardo
	 cuantas pociones uso, para no meter pp de mas.
	*/
	//ppDemas en realidad es cuantas ppnecesitamos, despues hacemos una resta y listo
	int ppDemas = 0;

	int pocQuedan = 0;
	for(int i = 0; i<bucket.size(); i++){
		int necesito = 0;
		if((i+1) % 3 == 0){
			necesito = ((i+1)/3 * bucket[i]);
		}
		else{
			int necesitofor = 0;
			for(int j = 1; j <=bucket[i]; j++){
				if(pocQuedan < i+1){
					int pocionesNec = i+1-pocQuedan;
					float div = pocionesNec/3;
					necesitofor += floor(div);
					if(pocionesNec % 3 != 0) necesitofor++;
					//aca hago funcion modulo, i+1 es la cantidad
					//de p que necesita para ganar, si hago esa cuenta queda bien piola y no negativos
					pocQuedan = (3-pocionesNec) % 3;
					//la funcion MODULO en realidad da el resto puto el bjarne
					if(pocQuedan < 0) pocQuedan +=3;
				}
				else{
					//me sobran pero todavia puedo gastarlas
					pocQuedan -= i+1;
				}
			}
			necesito = necesitofor;
		}
		ppDemas += necesito;
	}
	//Ya tengo todas las pp que necesito y todas las que tengo, una resta y estamos
	return ppDemas-cantPP;
}

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

void ImprimirCasos(vnod & gim, vnod & pp, ofstream & casos){
			for(int i = 0; i<gim.size();i++) casos<<"("<<gim[i].CordenadaX()<<","<<gim[i].CordenadaY()<<")["<<gim[i].DamePociones()<<"] ";
			casos<<" & ";
			for(int i = 0; i< pp.size();i++) casos<<"("<<pp[i].CordenadaX()<<","<<pp[i].CordenadaY()<<") ";
			casos<<"\n";
			casos.close();
}

void CorrerGeneral(int rep, vnod gim, vnod pp, Mochila moch, ofstream & res, ofstream & podas, ofstream & meta){
	int gimTotales = gim.size();
	int ppTotales = pp.size();
	if(21 > ppTotales+gimTotales){
			for(int nroEj = 1; nroEj <= 4; nroEj++){
				res<<nroEj<<" & "<<gimTotales << " & "<< ppTotales<<" & ";
				Correr(rep, gim, pp, moch, res, meta, nroEj);
			}
			//me va a dar numeros dependiendo de que poda use
			if(13 > ppTotales+gimTotales){
				podas << gimTotales << " & "<<ppTotales << " & ";
				CorrerPodas(gim, pp, moch, podas);
				podas<<"\n";
			}
		}
		else{
			for(int nroEj = 2; nroEj <= 4; nroEj++){
				res<<nroEj<<" & "<<gimTotales << " & "<< ppTotales<<" & ";
				Correr(rep, gim, pp, moch, res, meta, nroEj);
			}
		}
}

void Correr(int rep, vnod gimnasios, vnod pokeparadas, Mochila moch, ofstream & res, ofstream & meta, int nroEj){
	int valor;
	vector<int> sol;
	double (* foo)(vnod,vnod, Mochila,vint &);
	switch(nroEj){

		case 1:
		foo = &pto1;
		break;
		/*
		case 2:
		foo = &pto2;
		break;
		case 3:
		foo = &pto3;
		break;
*/
		case 4:
		foo = &pto4;
		break;
		default:
		cout<<"N invalido"<<endl;
		res<<"\n";
		return;
	}
	valor = (double) foo(gimnasios, pokeparadas, moch, sol);

	if(nroEj == 4){
		res <<valor<<" & ";
		meta << valor<<" & ";
		for(int i = 0; i< sol.size(); i++){
			res<<sol[i]<< " ";
			meta<<sol[i]<<" ";
		}
		meta<<"& ";
		res <<"& ";
		for(int i = 0; i < rep; i++){
			sol.clear();
			long tiempo = 0;
			auto start = ya();
			valor = foo(gimnasios, pokeparadas, moch, sol);
			auto end = ya();
			tiempo = chrono::duration_cast<chrono::nanoseconds>(end-start).count();
			meta<<valor<<" & ";
			for(int i = 0; i<sol.size(); i++) meta<<sol[i]<<" ";
			meta<<"& ";
			res<<tiempo<<" & ";
		}
		meta<<"\n";
		res<<"\n";
	}
	else{
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
}


/*
void PPdeMas(){}
*/
void RectaPPgim(int rep, int cantgim){
	ofstream res("resultadosRectaSinMoch.txt");
	ofstream meta("resultadosRSMmeta.txt");
	ofstream casos("casosRSM.txt");
	ofstream podas("podasRectaSinMoch.txt");
	vnod gimnasios;
	vnod pp;
	srand(time(NULL));
	for(int i = 0; i<=rep;i++) meta<<"valor & sol &";
	meta<<"\n";
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
		ImprimirCasos(gimnasios, pp, casos);
		CorrerGeneral(rep, gimnasios, pp, moch, res, podas, meta);
	}
}

void SoloPokeparadasNecesariasRecta(int rep, int cantgim){
	ofstream res("resultadosRectaPPNec.txt");
	ofstream casos("casosRectaPPNec.txt");
	ofstream podas("podasRectaPPNec.txt");
	ofstream meta("resultadosPPNecmeta.txt");
	for(int i = 0; i<=rep;i++) meta<<"valor & sol &";
	meta<<"\n";
	res<<"pto & cantidad de gimnasios & cantidad de pokeparadas & distancia & resultado & ... tiempos ...& \n";
	podas<<"cant Gim & cant pp & cantidad de llamadas al BT sin podas & distancia & recorrido";
	podas<<" & #BT con Poda A & distancia & recorrido & #BT con Poda B & distancia & recorrido";
	podas<<" & #BT con Poda c & distancia & recorrido & #BT con Poda AB & distancia & recorrido";
	podas<<" & #BT con Poda AC & distancia & recorrido & #BT con Poda BC & distancia & recorrido";
	podas<<" & #BT con Poda ABC & distancia & recorrido\n";
	casos<<"La idea es saber como estan conformados los casos gimansios & pp \n";
	vnod gim;
	vnod pp;
	vint pocionesDeGim;
	srand(time(NULL));
	int ppTotales = 0;
	int capMoch = 15;
	for(int i = 1; i<=cantgim;i++){
		int pociones = rand()%capMoch +1;
		pocionesDeGim.push_back(pociones);
		int pokeparadas;
		int gimAgregados = gim.size();
		int ppAgregadas = pp.size();
		pokeparadas = ElegirSoloNecesarias(pocionesDeGim, pp.size(), capMoch);
		int cantidadEnRecta= 0;
		for(int j = 1; j<= pokeparadas; j++){
			cantidadEnRecta = gimAgregados + ppAgregadas + j - 1 ;
			//el Indice no me importa, se reasigna despues.
			Nodo aux(3, 42, cantidadEnRecta, 0);
			pp.push_back(aux);
		}
		cantidadEnRecta++;
		Nodo gimAux(-pociones, 42, cantidadEnRecta, 0);
		gim.push_back(gimAux);
		AsignarIndices(gim, pp);
		ImprimirCasos(gim, pp, casos);
		CorrerGeneral(rep, gim, pp, moch, res, podas, meta);
	}
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
//void gruposSeparados (vnod& gym, vnod& pepe, const int &a, const int &b ){

std::function<tuple<int,int>()> generadorDeEspirales(int a, int b){
	int x=0;
	int y=0;
	int dx = 0;
	int dy = -1;
	return [=]() mutable{ //espiral.. girasol... lo q sea..
		if ((x == y) or (x < 0 and x == -y) or (x > 0 and x == 1-y)){
			int swapy=dx;
			dx=-dy;
			dy=swapy;
		}
		x = x+dx;
		y=y+dy;
		return make_tuple(x,y);
	};

}




int main(){
	RectaPPgim(1, 10);

	//SoloPokeparadasNecesariasRecta(1, 30);

	/*
	std::vector<tuple<int,int> > v;
	auto espiral = generadorDeEspirales(20,20);
	for (size_t i = 0; i < 100000000; i++) {
	//	espiral();
	v.push_back(espiral());
	}
	cout<<v.size()<<endl;
	}*/

}
