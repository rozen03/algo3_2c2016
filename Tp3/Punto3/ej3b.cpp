//#include "../clases.h"
#include "ej3.h"
using namespace std;
typedef vector<vnod> vvnod;
typedef vector<vint> vvint;


vvint dameBloques(vnod & gimnasios,vint& solucion){
	int cantidad_de_gimnasios  = gimnasios.size();
	vvint bloques(cantidad_de_gimnasios);
	int indiceDeBloque=0; //indice del bloque q voy a estar pusheadndo cosas
	for(int indice: solucion){
		//cerr<<"VOY A EXPLOTAR \t indice= "<<indice<<"\t indiceDeBloque= "<<indiceDeBloque<<" "<<gimnasios.size()<<endl;
		bloques[indiceDeBloque].push_back(indice);
		//cerr<<"FALSA ALARMA"<<endl;
		if(indice <= cantidad_de_gimnasios){
			indiceDeBloque++;
			if(indiceDeBloque==cantidad_de_gimnasios){
				break;
			}
		}
	}
	imprimirSolucion(bloques);
	return bloques;
}


double long distancia ( vnod gimnasios,   vnod &pokeParadas,  vvint & bloques){
	if(bloques.empty()){
		cerr<<"Hasta aca llegue, claramente estoy  vacio como tu vieja"<<endl;
		imprimirSolucion(bloques);
		exit(27);
	}
	if(bloques[0].empty()){
		cerr<<"Hasta aca llegue, claramente estoy  vacio como tu vieja"<<endl;
		imprimirSolucion(bloques);
		exit(27);
	}
	auto ultimo = dameNodo(gimnasios,pokeParadas,bloques[0][0]);
	auto proximoUltimo=ultimo;
	double long suma=0;
	for(auto bloque:bloques){
		for(auto indice:bloque){
			if (indice==bloques[0][0] ||  indice ==ultimo.DameIndice()){
				continue;
			}

			proximoUltimo=dameNodo(gimnasios,pokeParadas,indice);
			suma+=proximoUltimo.Distancia(ultimo);
			ultimo=proximoUltimo;
		}
	}
	return suma;
}
bool validarConMochila(vnod &gimnasios, vnod &pokeParadas,Mochila &mochila,vvint &bloques){
	int suma=0;
	int pre=-1;
	//int peso = -it->DamePociones();
	for(auto bloque:bloques){
		for(auto indice:bloque){
			if(pre==indice){
				return false;
			}
			if (indice <gimnasios.size() ){
				Nodo & proximoUltimo=dameNodo(gimnasios,pokeParadas,indice);
				suma+= proximoUltimo.DamePociones();
				if (suma<0){
					return false;
				}
			}else{
				suma+=3;
				if (suma > mochila.DameCapacidad()){
					suma = mochila.DameCapacidad();
				}
			}

		}
	}
	return true;
}
bool validarConMochila(vnod &gimnasios, vnod &pokeParadas,Mochila &mochila,vint &solucion){
	int suma=0;
	//int peso = -it->DamePociones();
	for(auto indice:solucion){
		if (indice <gimnasios.size() ){
			Nodo & proximoUltimo=dameNodo(gimnasios,pokeParadas,indice);
			suma+= proximoUltimo.DamePociones();
			if (suma<0){
				return false;
			}
		}else{
			suma+=3;
			if (suma > mochila.DameCapacidad()){
				suma = mochila.DameCapacidad();
			}
		}

	}
	return validarSol(solucion);
	//return true;
}
double long mejorOrdenDeBloques(vnod &gimnasios, vnod &pokeParadas,Mochila &mochila,vvint &bloques){
	bool hayMejora=true;
	double long mejorValor=distancia(gimnasios,pokeParadas,bloques);
	int mejorSwap_i=0;
	int mejorSwap_j=0;
	while(hayMejora){

		hayMejora=false;
		for (size_t i = 0; i < bloques.size(); i++) {
			for (size_t j = 0; j < bloques.size(); j++) {
				if (i==j){
					continue;
				}
				if(bloques.empty()){

					cerr<<"Hasta aca llegue, claramente estoy  vacio como tu vieja"<<endl;
					imprimirSolucion(bloques);
					exit(27);
				}
				if(bloques[0].empty()){
					cerr<<"Hasta aca llegue, claramente estoy  vacio como tu vieja"<<endl;
					imprimirSolucion(bloques);
					exit(27);
				}
				cerr<<"pre-wipi"<<endl;
				iter_swap(bloques.begin() + i, bloques.begin() + j);
				imprimirSolucion(bloques);
				double long valor=distancia(gimnasios,pokeParadas,bloques);
				cerr<<"wipi"<<endl;
				if (valor<mejorValor && validarConMochila(gimnasios, pokeParadas,mochila,bloques)){
					mejorValor=valor;
					hayMejora=true;
					mejorSwap_i=i;
					mejorSwap_j=j;
				}
				iter_swap(bloques.begin() + i, bloques.begin() + j);
			}
		}
		if(hayMejora){
			iter_swap(bloques.begin() + mejorSwap_i, bloques.begin() + mejorSwap_j);
		}
	}
	return mejorValor;
}

double long mejorOrdenDePokeParadas(vnod &gimnasios, vnod &pokeParadas,vint &solucion){
	bool hayMejora=true;
	double long mejorValor=distancia(gimnasios,pokeParadas,solucion);
	int mejorSwap_i=0;
	int mejorSwap_j=0;
	while(hayMejora){

		hayMejora=false;
		for (size_t i = 0; i < solucion.size(); i++) {
			for (size_t j = 0; j < solucion.size(); j++) {
				if (i==j|| solucion[i] < gimnasios.size() || solucion[j] < gimnasios.size()){
					continue;
				}
				iter_swap(solucion.begin() + i, solucion.begin() + j);
				double valor=distancia(gimnasios,pokeParadas,solucion);
				if (valor<mejorValor && validarSol(solucion)){
					mejorValor=valor;
					hayMejora=true;
					mejorSwap_i=i;
					mejorSwap_j=j;
				}
				iter_swap(solucion.begin() + i, solucion.begin() + j);
			}
		}
		if(hayMejora){
			iter_swap(solucion.begin() + mejorSwap_i, solucion.begin() + mejorSwap_j);
		}
	}
	return mejorValor;
}
double long mejorarPokeparadas(vnod &gimnasios, vnod &pokeParadas, Mochila &mochila, vint &solucion){
	bool hayMejora=true;
	double long mejorValor=distancia(gimnasios,pokeParadas,solucion);
	int posicionAInsertar;
	int indiceAInsertar;
	int indiceAEliminar;
	vint ppEnLaNube;
	for (auto pokeParada: pokeParadas){
		if (find(solucion.begin(), solucion.end(), pokeParada.DameIndice()) == solucion.end()){//si no esta en la solucion
			ppEnLaNube.push_back(pokeParada.DameIndice());
		}
	}
	while(hayMejora){
		cerr<<"Es mi culpa, seguimos aca"<<endl;
		hayMejora=false;
		for (size_t i = 1; i < solucion.size(); i++) {
			if (solucion[i] < gimnasios.size()){
				continue;
			}
			ppEnLaNube.push_back(solucion[i]);
			for (int pokeParada : ppEnLaNube) {
				for (size_t j = 1; j < i; j++) {
					if (i==pokeParada){
						//cerr<<"son iguales pelotudo"<<endl;
					}
					vint::const_iterator first = solucion.begin();
					vint::const_iterator last = solucion.end() ;
					vint newVec(first, last);
					newVec.erase(newVec.begin()+ i);
					newVec.insert(newVec.begin()+j,pokeParada);
					if(distancia(gimnasios,pokeParadas,newVec)<distancia(gimnasios,pokeParadas,solucion)){
						if(validarConMochila(gimnasios,pokeParadas,mochila,newVec)){
							if(!validarSol(newVec)){
								cerr<<"este pibe es boludo"<<endl;
							}
							posicionAInsertar=j;
							indiceAInsertar=pokeParada;
							indiceAEliminar=i;
							hayMejora=true;
						}
					}
				}

			}
			ppEnLaNube.pop_back();
		}
		if(hayMejora){
			//cerr<<"a ver, señor mejora"<<endl;
			//imprimirSolucion(solucion);
			solucion.erase(solucion.begin()+ indiceAEliminar);
			solucion.insert(solucion.begin()+posicionAInsertar,indiceAInsertar);
			//imprimirSolucion(solucion);
			//distancia(gimnasios,pokeParadas,solucion);
			//cerr<<"Parece q no dio NAN"<<endl;
		}
	}
	if(!validarSol(solucion)){
		cerr<<"Claramente es mi culpa pelotudo"<<endl;
		exit(99);
	}
	return distancia(gimnasios,pokeParadas,solucion);
}
double long BusquedaLocalb(vnod gimnasios, vnod pokeParadas, Mochila mochila, vint &solucion, double long valor){
	vint solucion_posible;
	cerr<<"bloques 1"<<endl;
	if(solucion.empty()){
		cerr<<"Loco, que paso aca?"<<endl;
		return -1;
	}
	imprimirSolucion(gimnasios,pokeParadas,solucion);
	vvint bloques = dameBloques(gimnasios,solucion);
	cerr<<"llamo a mejorbloques"<<endl;
	double long res_posible=mejorOrdenDeBloques( gimnasios, pokeParadas,mochila, bloques);
	cerr<<"voy a juntar todo baby"<<endl;
	for (auto bloque: bloques){
		solucion_posible.insert(solucion_posible.end(),bloque.begin(),bloque.end());
	}
	validarSol(solucion_posible);
	cerr<<"mejorden"<<endl;
	res_posible=mejorOrdenDePokeParadas(gimnasios,pokeParadas,solucion_posible);
	validarSol(solucion_posible);
	cerr<<"mejorpop"<<endl;
	res_posible= mejorarPokeparadas(gimnasios,pokeParadas,mochila,solucion_posible);
	imprimirSolucion(solucion_posible);
	validarSol(solucion_posible);
	cerr<<"bloques 2"<<endl;
	imprimirSolucion(gimnasios,pokeParadas,solucion_posible);
	bloques = dameBloques(gimnasios,solucion_posible);
	solucion_posible.clear();
	imprimirSolucion(bloques);
	cerr<<"llamo a mejorbloques"<<endl;
	mejorOrdenDeBloques(gimnasios, pokeParadas,mochila, bloques);
	cerr<<"voy a juntar todo baby"<<endl;
	for (auto bloque: bloques){
		solucion_posible.insert(solucion_posible.end(),bloque.begin(),bloque.end());
	}
	validarSol(solucion_posible);
	cerr<<"cerrando el trato"<<endl;
	res_posible= distancia(gimnasios,pokeParadas,solucion_posible);
	if(res_posible<valor){
		solucion=solucion_posible;
		valor= res_posible;
	}
	//imprimirSolucion(gimnasios,pokeParadas,solucion);
	return valor;
}
double  pto3b(vnod gimnasios, vnod pokeParadas, Mochila mochila, vint &solucion) {
	cerr<<"Empece pto3b"<<endl;
	sort(gimnasios.begin(), gimnasios.end(),[](Nodo a, Nodo b){return a.DamePociones()<b.DamePociones();});
	vnod solucioNodos(1,Nodo(27,27,27,27));
	auto dist =  tirarPokeParadas(pokeParadas, gimnasios,  mochila, solucioNodos);
	if (dist <0){
		cout<<"aah dio mal"<<endl;
		return -1;
	}
	for(auto nodo : solucioNodos){
		solucion.push_back(nodo.DameIndice());
	}
	if(!isnormal(dist)){
		cerr<<"EXPLOTOAH"<<endl;
	}
	//imprimirSolucion(gimnasios,pokeParadas, solucion);
	cerr<<"llamo a BusquedaLocalb"<<endl;
	BusquedaLocalb(gimnasios,pokeParadas, mochila, solucion,distancia(gimnasios,pokeParadas,solucion));
	//imprimirSolucion(gimnasios,pokeParadas, solucion);
	cerr<<"termine pto3b"<<endl;
	return distancia(gimnasios,pokeParadas,solucion);
}
