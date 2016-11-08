//#include "../clases.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <limits>
#include <tuple>
#include "../Punto1/pto1.cpp"
#include "../Punto1/pto1A.cpp"
#include "../Punto2/Punto2.cpp"
//#include "../Punto3/ej3.cpp"
//#include "../Punto4/pto4.cpp"*/

//Funciones Auxiliares
//basicamente hace correr y correr podas, guarda el caso en casos.
void CorrerGeneral(int rep, vnod gim, vnod pp, Mochila moch,ofstream & res, ofstream & casos, ofstream & podas);

//Este correr se encarga de ejecutar los casos con todos los ejercicios
void Correr(int rep, vnod gim, vnod pokeparadas, Mochila moch, ofstream & res, int nroEj);

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
	 Esto es para sacar bien cuantas se necesita.
	 capMoch = 5
	 ej = [1,2,3,1,0]
	 si lo hago bruto se necesita 8 pokeparadas.
	 pero se que en la posicion 2 tengo las que necesitan 3, entonces ahi no tengo otra opcion que poner 1 pokeparada.
	 despues es la posicion 0 necesito 1 ( los que necesitan 0 no tengo que ni pensarlos) y en la 1 necesto 2 pociones, entonces
	 puedo aparear de a pares, entonces se que tengo que poner 1 por cada par + 1 por el restante (pero tambien esta bueno saber que me quedaron de sobra), es decir solo 2 pokeparadas.
	 en la posicion 3 necesito 4 pociones, pero por como estuve haciendo las cuentas no necesito dos pp necesito una sola, me sobro una pocion del los pares.
	 3+2+1 = 6 en un caso chico se reduce poco, pero en mas grandes se tendria que reducir mas, y esto seguro que caga heuristicas.
	 */
	vector<int> bucket(capMoch, 0);
	//meto en el bucket
	cerr<<"la capacidad es "<<capMoch<<" empece con "<<cantPP<<" PokeParadas"<<endl;
	for(int i = 0; i < pocionesDeGim.size(); i++){
		int pocAux = pocionesDeGim[i];
		if(pocAux > 0) bucket[pocAux-1]++;
	}

	for(int i = 0; i<bucket.size();i++){
		cerr<<bucket[i]<<" ";
	}
	cerr<<endl;
	/*la deconstruccion del bucket la hago de mas grande a mas chico, ya que es mejor achicar esos casos imaginarse un gimnasio 8, otro 7, otro 2 y otro
	  1 y 9 de capacidad, si apareo primero el 2 y el 1 necesito 3 para el 8 y 3 para el 7 y 1 para el 2,1 eso nos deja en 7
	  si apareamos el 1 con el 8 y el 2 con el 7 solo usamos 6 pp y no desperdiciamos ninguna pokebola
	*/
	//ppDemas en realidad es cuantas ppnecesitamos, despues hacemos una resta y listo
	int ppDemas = 0;
	//primero saco todos los pares que existan
	/*
	for(int i = bucket.size()-1; i >= 0; i--){
		//va a ser dificil pensarlo con un desplazamiento asi que prefiero tenerlo en su forma original, si... con un poco de cerebro se hace igual, pero no quiero debuggear al pedo
		int pociones = i+1;
		int ppNec = pociones /3;
		if(bucket[i]==0) continue;
		//se separa en 3 casos, dependiendo del resto
		if(pociones % 3 == 0){
			//voy uno a la vez
			for(int j = 1; j <=bucket[i]; j++) ppDemas += ppNec;
			cerr<<"modulo 3 agrego "<<ppDemas<<endl;
			//estas siempre van a llegar a 0 en este for, por que no se acomplan con nadie.
			bucket[i] = 0;
		}

		if(pociones % 3 == 2){
			//como es division entera, esto me dejaria por debajo de las que necesito, como en este for solo voy a
			//buscar parejas voy a necesitar la division entera mas 1.
			ppNec++;
			//busco los modulo uno que se puedan acoplar, como voy de mas grande a mas chico
			//nunca va a haber un j mayor que un i que se pueda acoplar.
			//si esa cantidad de pociones como suma es mas grande que la mochila tambien corta
			//como voy reduciendo que hay en cada bucket, si termino de achicar i, listo
			for(int j = 0; j<i && j+1+pociones <=capMoch && bucket[i] != 0; i+=3){
				//voy hasta que me quede sin j o me quede sin i (lo que hay en i/j)
				while(bucket[i]>0 && bucket[j]>0){
					cerr<<"2/3"<<2/3<<" ppNec "<<ppNec;
					ppDemas += ppNec;
					cerr<<"voy metiendo por ser modulo 2"<<endl;
					bucket[i]--;
					bucket[j]--;
				}
			}
		}

		if(pociones % 3 == 1){
			//como es division entera, esto me dejaria por debajo de las que necesito, como en este for solo voy a
			//buscar parejas voy a necesitar la division entera mas 1.
			ppNec++;
			//busco los modulo uno que se puedan acoplar, como voy de mas grande a mas chico
			//nunca va a haber un j mayor que un i que se pueda acoplar.
			//si esa cantidad de pociones como suma es mas grande que la mochila tambien corta
			//como voy reduciendo que hay en cada bucket, si termino de achicar i, listo
			for(int j = 1; j<i && j+1+pociones <=capMoch && bucket[i] != 0; i+=3){
				//voy hasta que me quede sin j o me quede sin i (lo que hay en i/j)
				while(bucket[i]>0 && bucket[j]>0){
					cerr<<"voy metiendo por ser modulo 1"<<endl;
					ppDemas += ppNec;
					bucket[i]--;
					bucket[j]--;
				}
			}
		}
	}
	*/
	
	//Ahora solo quedan cosas que no tienen pares que sumen modulo 3, no se si voy a poder hacerlo tal que me queden las pp justas y necesarias pero bue...
	int pocQuedan = 0;
	for(int i = 0; i<bucket.size(); i++){
		int necesito = 0;
		if((i+1) % 3 == 0){
			necesito = ((i+1)/3 * bucket[i]); 
		}
		else{
			for(int j = 1; j <=bucket[i]; j++){
				if(pocQuedan < i+1){
					int pocionesNec = i+1-pocQuedan;
					float div = pocionesNec/3;
					necesito = floor(div);
					if(pocionesNec % 3 != 0) necesito++;
					//aca hago funcion modulo, i+1 es la cantidad
					//de p que necesita para ganar, si hago esa cuenta queda bien piola y no negativos
					pocQuedan = (3-(i+1)) % 3;
					//la funcion MODULO en realidad da el resto puto el bjarne
					if(pocQuedan < 0) pocQuedan +=3;
				}
				else{
					//me sobran pero todavia puedo gastarlas
					pocQuedan -= i+1;
				}
			}
		}
		cerr<<"("<<i+1<<","<< necesito<<")["<<pocQuedan<<"] ";
		ppDemas += necesito;
	}
	cerr<<endl;
	//Ya tengo todas las pp que necesito y todas las que tengo, una resta y estamos
	cerr<<"las pp que voy a asignar son "<<ppDemas-cantPP<<endl;
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

void CorrerGeneral(int rep, vnod gim, vnod pp, Mochila moch, ofstream & res, ofstream & casos, ofstream & podas){
	int gimTotales = gim.size();
	int ppTotales = pp.size();
	if(21 > ppTotales+gimTotales){
			for(int nroEj = 1; nroEj <= 4; nroEj++){
				res<<nroEj<<" & "<<gimTotales << " & "<< ppTotales<<" & ";
				Correr(rep, gim, pp, moch, res, nroEj);
			}
			//me va a dar numeros dependiendo de que poda use
			if(13 > ppTotales+gimTotales){
				podas << gimTotales << " & "<<ppTotales << " & ";
				CorrerPodas(gim, pp, moch, podas);
				podas<<"\n";
			}
			for(int i = 0; i<gimTotales;i++) casos<<"("<<gim[i].CordenadaX()<<","<<gim[i].CordenadaY()<<")["<<gim[i].DamePociones()<<"] ";
			casos<<" & ";
			for(int i = 0; i< ppTotales;i++) casos<<"("<<pp[i].CordenadaX()<<","<<pp[i].CordenadaY()<<") ";
			casos<<"\n";
		}
		else{
			for(int nroEj = 2; nroEj <= 4; nroEj++){
				res<<nroEj<<" & "<<gimTotales << " & "<< ppTotales<<" & ";
				Correr(rep, gim, pp, moch, res, nroEj);
			}
		}
}

void Correr(int rep, vnod gimnasios, vnod pokeparadas, Mochila moch, ofstream & res, int nroEj){
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
		/*case 3:
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

		CorrerGeneral(rep, gimnasios, pp, moch, res, casos, podas);
	}
}

void SoloPokeparadasNecesariasRecta(int rep, int cantgim){
	ofstream res("resultadosRectaPPNec.txt");
	ofstream casos("casosRectaPPNec.txt");
	ofstream podas("podasRectaPPNec.txt");
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
		cerr<<"las pociones que agrego "<<pociones<<" en el gimnasio "<<i<<endl;
		pokeparadas = ElegirSoloNecesarias(pocionesDeGim, pp.size(), capMoch);
		cerr<<"las pokeparadas que le voy a asignar son "<<pokeparadas<<endl;
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
		CorrerGeneral(rep, gim, pp, moch, res, casos, podas);
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

void gruposSeparados (vnod& gym, vnod& pepe, const int &a, const int &b ){

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

	SoloPokeparadasNecesariasRecta(1, 30);

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
