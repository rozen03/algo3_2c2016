#include "ej3.h"
#include <functional>

using namespace std;
uint64_t rdtsc() {
	unsigned int lo, hi;
	__asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
	return ((uint64_t)hi << 32) | lo;
}
function<tuple<int,int>()> generadorDeEspirales(int a, int b){
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
int main(){
	double res=0.0;
	double res2=0.0;
	vnod gimnasioss;//,gimnasioss;
	vnod pokeParadass;
	Mochila mochila(30);
	int i=0;
	int pesos[] = {-12,-9,-6,-10,-2,-3,-20,-30,-1};//,-2,-27};
	int cantidadDePP= 80;
	auto espiral = generadorDeEspirales(0,0);
	auto espiralPP = generadorDeEspirales(2*cantidadDePP,2*cantidadDePP);
	/*
	gimnasios.push_back(Nodo(-12,i++,0,4));
	gimnasios.push_back(Nodo(-9,i++,0,8));
	gimnasios.push_back(Nodo(-6,i++,0,11));
	gimnasios.push_back(Nodo(-10,i++,0,21));
	gimnasios.push_back(Nodo(-2,i++,0,21));
	pokeParadas.push_back(Nodo(0,i++,0,0));
	pokeParadas.push_back(Nodo(0,i++,0,1));
	pokeParadas.push_back(Nodo(0,i++,0,2));
	pokeParadas.push_back(Nodo(0,i++,0,3));
	pokeParadas.push_back(Nodo(0,i++,0,5));
	pokeParadas.push_back(Nodo(0,i++,0,6));
	pokeParadas.push_back(Nodo(0,i++,0,7));
	pokeParadas.push_back(Nodo(0,i++,0,9));
	pokeParadas.push_back(Nodo(0,i++,0,10));
	pokeParadas.push_back(Nodo(0,i++,0,12));
	pokeParadas.push_back(Nodo(0,i++,0,13));
	pokeParadas.push_back(Nodo(0,i++,0,14));
	pokeParadas.push_back(Nodo(0,i++,0,15));
	pokeParadas.push_back(Nodo(0,i++,0,16));
	pokeParadas.push_back(Nodo(0,i++,0,16));
	pokeParadas.push_back(Nodo(0,i++,0,17));
	*/

	for (size_t j = 0; j < sizeof(pesos)/sizeof(pesos[0]); j++) {
		auto punto = espiral();
		gimnasioss.push_back(Nodo(pesos[j],i++,get<0>(punto),get<1>(punto)));
	}
	for (size_t j = 0; j < cantidadDePP; j++) {
		auto punto = espiralPP();
		pokeParadass.push_back(Nodo(0,i++,get<0>(punto),get<1>(punto)));
	}
	//Lectura(gimnasios, pokeParadas, mochila);
	//for (auto proximoUltimo:gimnasios){
	//    cout<<proximoUltimo.CordenadaX()<< " "<< proximoUltimo.CordenadaY()<<endl;
	//}
	for (int k = gimnasioss.size()-1; k <gimnasioss.size() ; k++) {
		vnod::const_iterator first = gimnasioss.begin();
		vnod::const_iterator last = gimnasioss.begin() + k ;
		vnod gimnasios(first, last);
		for (size_t po =pokeParadass.size()-1; po < pokeParadass.size(); po++) {
			/* code */
			//gimnasios.clear();
			//gimnasios.insert(gimnasioss.begin(),gimnasioss.begin()+k);
			vnod::const_iterator first = pokeParadass.begin();
			vnod::const_iterator last = pokeParadass.begin() + po ;
			vnod pokeParadas(first, last);

			//cout<<k<<" gimnasios: y\t "<<po<<" pokeparadas" <<endl;
			int rep =1;
			vint solucion;
			uint64_t elapsed1=0;
			uint64_t elapsed2=0;
			uint64_t start;
			uint64_t took;
			for (size_t j = 0; j < rep; j++) {
				start = rdtsc();
				res = pto3(gimnasios,pokeParadas,mochila,solucion);
				took = rdtsc() - start;
				elapsed1+=took;
				solucion.clear();
			}

			cout<<"res a: "<<res<< "\tduracion: "<<elapsed1/rep<<endl;
			for (size_t j = 0; j < rep; j++) {
				start = rdtsc();
				res2 = pto3b(gimnasios,pokeParadas,mochila,solucion);
				took = rdtsc() - start;
				elapsed2+=took;
				solucion.clear();
			}
			cout<<"res b: "<<res2<< "\tduracion: "<<elapsed2/rep<<endl;
			if(!isnormal(res2)){
				cout<<"EXOOOOOOODIAAAAAAAA"<<endl;
			}
			//cout<<"Porcentaje de diferencia de tiempo: "<< (elapsed2*100)/elapsed1<<'%'<<endl;
			//cout<<"Porcentaje de diferencia de solucion: "<< (res2*100)/res<<'%'<<endl;
			cout<<k<<"\t|\t "<<po<<"\t|\t "<<(elapsed2*100)/elapsed1<<"\t|\t "<<(res2*100)/res<<endl;
		}
	}
	//imprimirSolucion(solucion);
}
