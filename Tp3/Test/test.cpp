#include "../clases.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <limits>
#include <tuple>
#include <functional>
#include "../Punto1/pto1.cpp"
#include "../Punto1/pto1A.cpp"
//estan incluidos en el pto4
//#include "../Punto2/Punto2.cpp"
//#include "../Punto2/Punto2b.cpp"
//#include "../Punto3/ej3.cpp"
#include "../Punto4/pto4.cpp"


//Funciones Auxiliares
//basicamente hace correr y correr podas.
void CorrerGeneral(int rep, vnod gim, vnod pp, Mochila moch,ofstream & res, ofstream & meta, ofstream & podas);

//imprime los casos en un archivo separado.
void ImprimirCasos(vnod & gim, vnod & pp, ofstream & casos);

//Este correr se encarga de ejecutar los casos con todos los ejercicios
void Correr(int rep, vnod gim, vnod pokeparadas, Mochila moch, ofstream & res, ofstream & meta, int nroEj);

//Header de CorrerPodas
void Header(ofstream & res, ofstream & podas, ofstream & casos, ofstream & meta, int cantRep);

//Esto nos deja crear los gimnasios y los nodos sin preocpuarnos por los indices, ya que esta funcion se encarga
//LO PUSE EN PTO1A por que lo necesitaba ahi.
//void AsignarIndices(vnod & gim, vnod & pp);

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


//Hace dos puntos, uno de pokeparadas y otro de gimnasios
void DosPuntos(int rep, int cantgim);



using namespace std;

#define ya chrono::high_resolution_clock::now


void Header(ofstream & res, ofstream & podas, ofstream & casos, ofstream & meta, int cantRep){
	for(int i = 0; i<=cantRep;i++) meta<<"valor & sol &";
	meta<<"\n";
	res<<"pto &i &j & d & r &";
	for(int i = 1; i<=cantRep; i++)res<<"t"<<i<<" &";
	res<<"\n";
	podas<<"i &j &SP &dp &rp";
	podas<<" &A & da & ra &B &db &rb";
	podas<<" &C &dc &rc &AB &dab &rab";
	podas<<" &AC & dac &rac &BC &dbc &rbc";
	podas<<" &ABC &dabc &rabc";

	podas<<" &SPi &dpi &rpi";
	podas<<" &Ai & dai & rai &Bi &dbi &rbi";
	podas<<" &Ci &dci &rci &ABi &dabi &rabi";
	podas<<" &ACi & daci &raci &BCi &dbci &rbci";
	podas<<" &ABCi &dabci &rabci";
	podas<<" &SPr &dpr &rpr";
	podas<<" &Ar & dar & rar &Br &dbr &rbr";
	podas<<" &Cr &dc &rcr &ABr &dabr &rabr";
	podas<<" &ACr & dacr &racr &BCr &dbcr &rbcr";
	podas<<" &ABCr &dabcr &rabcr \n";
	casos<<"i &j \n";
}

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

void ImprimirCasos(vnod & gim, vnod & pp, ofstream & casos){
	for(int i = 0; i<gim.size();i++) casos<<"("<<gim[i].CordenadaX()<<","<<gim[i].CordenadaY()<<")["<<gim[i].DamePociones()<<"] ";
	casos<<" & ";
	for(int i = 0; i< pp.size();i++) casos<<"("<<pp[i].CordenadaX()<<","<<pp[i].CordenadaY()<<") ";
	casos<<"\n";
}

void CorrerGeneral(int rep, vnod gim, vnod pp, Mochila moch, ofstream & res, ofstream & podas, ofstream & meta, int nodoValidosPto1, int nodoValidosPodas){

	int gimTotales = gim.size();
	int ppTotales = pp.size();
	if(nodoValidosPto1 > ppTotales+gimTotales){
		//ahora no responde a cada punto 1 es pto1 2 es pto2 3 es pto3 4 es pto3b 5 pto4 6 pto4b
		for(int nroEj = 1; nroEj <= 5; nroEj++){
			res<<nroEj<<" & "<<gimTotales << " & "<< ppTotales<<" & ";
			Correr(rep, gim, pp, moch, res, meta, nroEj);

			cerr<<"termine el pto "<<nroEj<<" con "<<gimTotales<<" gimnasios y "<<ppTotales<<" pokeparadas"<<endl;
		}
		//me va a dar numeros dependiendo de que poda use
		if(nodoValidosPodas > ppTotales+gimTotales){
			CorrerPodas(gim, pp, moch, podas);
		}

	}else{
		if(gimTotales+ppTotales <= 200){
			for(int nroEj = 2; nroEj <= 5; nroEj++){
				res<<nroEj<<" & "<<gimTotales << " & "<< ppTotales<<" & ";
				Correr(rep, gim, pp, moch, res, meta, nroEj);
				cerr<<"termine el pto "<<nroEj<<" con "<<gimTotales<<" gimnasios y "<<ppTotales<<" pokeparadas"<<endl;
			}
		}
		else{
			break;
			}
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
		case 2:
		foo = &pto2;
		break;
		case 3:
		foo = &pto3;
		break;
		case 4:
		foo = &pto3b;
		break;
		case 5:
		foo = &pto4;
		break;
		default:
		cout<<"N invalido"<<endl;
		res<<"\n";
		return;
	}
	//return;
	valor = (double) foo(gimnasios, pokeparadas, moch, sol);

	if(nroEj > 4){
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

void TodoEnElMismoLugar(int rep, int cantgim){
	ofstream res("resultadosPPdeMas.txt");
	ofstream meta("resultadosPPdeMasmeta.txt");
	ofstream casos("casosPPdeMas.txt");
	ofstream podas("podasPPdeMas.txt");
	vnod gimnasios;
	vnod pp;
	srand(time(NULL));

	Header(res, podas, casos, meta, rep);
	Mochila moch(30);
	int x= rand()%50 +0;
	int y= rand()%50+ 0;
	for (int i = 1; i <= cantgim; ++i){
		Nodo gim(-1, i, x, y);
		gimnasios.push_back(gim);
		for (int j = 1; j <= cantgim*3; ++j){
			Nodo pokeparada(3,cantgim+i, x, y);
			pp.push_back(pokeparada);
		}
		AsignarIndices(gimnasios, pp);
		ImprimirCasos(gimnasios, pp, casos);
		CorrerGeneral(rep, gimnasios, pp, moch, res, podas, meta, 20, 13);
	}
}

void PPdeMas(int rep, int cantgim){
	ofstream res("resultadosPPdeMas.txt");
	ofstream meta("resultadosPPdeMasmeta.txt");
	ofstream casos("casosPPdeMas.txt");
	ofstream podas("podasPPdeMas.txt");
	vnod gimnasios;
	vnod pp;
	srand(time(NULL));

	Header(res, podas, casos, meta, rep);

	Mochila moch(30);
	for (int i = 1; i <= cantgim; ++i){
		int x= rand()%50+0;
		int y= rand()%50+0;
		Nodo gim(-1, i, x, y);
		gimnasios.push_back(gim);
		for (int j = 1; j <= cantgim*3; ++j){
			int x= rand()%50+0;
			int y= rand()%50+0;
			Nodo pokeparada(3,cantgim+i, x, y);
			pp.push_back(pokeparada);

		}
		AsignarIndices(gimnasios, pp);
		ImprimirCasos(gimnasios, pp, casos);
		CorrerGeneral(rep, gimnasios, pp, moch, res, podas, meta, 20, 13);
	}
}


void RectaPPgim(int rep, int cantgim){
	ofstream res("resultadosRectaSinMoch.txt");
	ofstream meta("resultadosRSMmeta.txt");
	ofstream casos("casosRSM.txt");
	ofstream podas("podasRectaSinMoch.txt");
	vnod gimnasios;
	vnod pp;
	srand(time(NULL));

	Header(res, podas, casos, meta, rep);
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
		CorrerGeneral(rep, gimnasios, pp, moch, res, podas, meta,20,13);
	}
}

void SoloPokeparadasNecesariasRecta(int rep, int cantgim){
	ofstream res("resultadosRectaPPNec.txt");
	ofstream casos("casosRectaPPNec.txt");
	ofstream podas("podasRectaPPNec.txt");
	ofstream meta("resultadosPPNecmeta.txt");

	Header(res, podas, casos, meta, rep);
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
		CorrerGeneral(rep, gim, pp, moch, res, podas, meta,20,13);
	}
}

void DosPuntos(int rep, int cantgim){
	ofstream res("resultadosDosPuntos.txt");
	ofstream meta("resultadosDPmeta.txt");
	ofstream casos("casosDP.txt");
	ofstream podas("podasDosPuntos.txt");
	vnod gimnasios;
	vnod pp;
	srand(time(NULL));

	Header(res, podas, casos, meta, rep);
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
		CorrerGeneral(rep, gimnasios, pp, moch, res, podas, meta,20,13);
	}
}


void SoloPokeparadasNecesariasDosPuntos(int rep, int cantgim){
	ofstream res("resultadosRectaPPNec.txt");
	ofstream casos("casosRectaPPNec.txt");
	ofstream podas("podasRectaPPNec.txt");
	ofstream meta("resultadosPPNecmeta.txt");

	Header(res, podas, casos, meta, rep);
	vnod gim;
	vnod pp;
	vint pocionesDeGim;
	int ladoPokeparadas = 0;
	int ladoGimnasios = 0;

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
			Nodo aux(3, 42, ladoPokeparadas, 0);
			pp.push_back(aux);
		}
		Nodo gimAux(-pociones, 42, ladoGimnasios, 0);
		gim.push_back(gimAux);
		AsignarIndices(gim, pp);
		ImprimirCasos(gim, pp, casos);
		CorrerGeneral(rep, gim, pp, moch, res, podas, meta,20,13);
	}
}


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
		return make_tuple(x+a,y+b);
	};
}


int dameX(tuple<int,int> tupla){
	return get<0>(tupla);
}
int dameY(tuple<int,int> tupla){
	return get<1>(tupla);
}
void gruposSeparados (vnod& gyms, vnod& pepes, const int &cant_gym, const int &cant_pp ){
	auto espiral_gyms =generadorDeEspirales(0, 0);
	auto espiral_pp   =generadorDeEspirales(2*(cant_gym+cant_pp),2*(cant_gym+cant_pp));//pongo el otro BIEN LEJOS
	for (size_t i = 0; i < cant_gym; i++) {
		auto coordenadas = espiral_gyms();
		gyms.push_back(Nodo(0,0,dameX(coordenadas),dameY(coordenadas)));
	}
}

void asignarPocionesDeFormaCreciente(vnod & gyms){
	for (size_t i = 0; i < gyms.size(); i++) {
		gyms[i].asignarCantidadPociones(i);
	}
}
void casoGruposSeparadosPocionesCreciente(vnod& gyms, vnod& pepes, const int &cant_gym, const int &cant_pp ){
	gruposSeparados (gyms, pepes,cant_gym, cant_pp);
	asignarPocionesDeFormaCreciente(gyms);
	AsignarIndices(gyms,pepes);
}
void casoEspiralPrimeroPepesPocionesCreciente(vnod& gyms, vnod& pepes, const int &cant_gym, const int &cant_pp ){
	auto espiral =generadorDeEspirales(0, 0);
	for (size_t i = 0; i < cant_gym; i++) {
		auto coordenadas = espiral();
		gyms.push_back(Nodo(0,0,dameX(coordenadas),dameY(coordenadas)));
	}

	for (size_t i = 0; i < cant_pp; i++) {
		auto coordenadas = espiral();
		pepes.push_back(Nodo(0,0,dameX(coordenadas),dameY(coordenadas)));
	}
	asignarPocionesDeFormaCreciente(gyms);
	AsignarIndices(gyms,pepes);
}
void gruposSeparadosPorEspirales(int rep, int cantgim){
	ofstream res("gruposEspiralesRes.txt");
	ofstream meta("gruposEspiralesMeta.txt");
	ofstream casos("gruposEspiralesCasos.txt");
	ofstream podas("gruposEspiralesPodas.txt");
	vnod gyms;
	vnod pepes;
	srand(time(NULL));
	Header(res, podas, casos, meta, rep);
	Mochila moch(30);
	casoEspiralPrimeroPepesPocionesCreciente(gyms,pepes,6,8);
	int sumita =0;
	for (size_t i = 1; i < 7; i++) {
		sumita+=i;
		vnod gimnasios;
		for (size_t j = 0; j < i; j++){
			gimnasios.push_back(gyms[j]);
		}
		vnod pp;
		for (size_t j = 0; j <(int)(sumita/3) ; j++) {
			pp.push_back(pepes[j]);
		}

		AsignarIndices(gimnasios, pp);
		ImprimirCasos(gimnasios, pp, casos);
		CorrerGeneral(rep, gimnasios, pp, moch, res, podas, meta, 20, 14);
		gimnasios.clear();
		pp.clear();
	}
}
int main(){
	cerr<<"empece"<<endl;
	RectaPPgim(1, 50);
	cerr<<"termino rectasPP"<<endl;

	SoloPokeparadasNecesariasRecta(1, 50);
	cerr<<"terminoSoloPPNec\n";

	PPdeMas(1,50);

	cerr<<"termino PPdeMas\n";
	TodoEnElMismoLugar(1,20);
	cerr<<"termino MismoLugar\n";

	DosPuntos(1,50);
	cerr<<"termino DosPuntos\n";
	gruposSeparadosPorEspirales(2,14);
	cerr<<"termino grupos separados por espirales yey"<<endl;
}
