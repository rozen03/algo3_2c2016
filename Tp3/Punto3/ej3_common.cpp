#include "ej3.h"
using namespace std;
double long tirarPokeParadas(vnod pokeParadas, vnod &gimnasios, Mochila mochila, vnod &solucion) {
	int suma = 0;
	int distancia = 0;
	bool esSolucionFinal = false;
	bool hayUltimo=false;
	Nodo ultimo= pokeParadas[0];//le meto uno cualquiera por q no hay constructor vacio lpm
	Nodo ultimoIter=pokeParadas[0];
	auto iterUltimo=pokeParadas[0];
	bool hayIterUltimo=false;
	vnod parteDeSolucion;

	if (!solucion.empty()) {
		esSolucionFinal = true;
		solucion.clear();
	}

	for (vnod::iterator it = gimnasios.begin(); it != gimnasios.end(); ++it) {
		parteDeSolucion.clear();
		int peso = -it->DamePociones();
		while (suma < peso) {
			if (pokeParadas.empty()){
				return -1;
			}
			suma += 3;
			if (suma > mochila.DameCapacidad()){
				suma = mochila.DameCapacidad();
			}
			auto compararDistancia = [=](Nodo a, Nodo b) {
				if(hayIterUltimo){
					return iterUltimo.Distancia(a) < iterUltimo.Distancia(b);
				}
				if(it->Distancia(a) == it->Distancia(b)){
					Nodo centro = Nodo(0,0,0,0);
					return centro.Distancia(a)<centro.Distancia(b);
				}
				return it->Distancia(a) < it->Distancia(b);
			};
			vnod::iterator pokeParadaCerca = min_element(
				pokeParadas.begin(), pokeParadas.end(), compararDistancia);
				parteDeSolucion.push_back(*pokeParadaCerca);
				pokeParadas.erase(pokeParadaCerca);
				iterUltimo = *pokeParadaCerca;
				hayIterUltimo=true;
			}
			for (int i =parteDeSolucion.size() -1; i >-1; i--) {
				//    for (size_t i =0 ; i < parteDeSolucion.size(); i++) {
				if (hayUltimo){
					distancia += ultimo.Distancia(parteDeSolucion[i]);
				}else{
					hayUltimo=true;
				}
				ultimo= parteDeSolucion[i];
				if (esSolucionFinal) {
					solucion.push_back(parteDeSolucion[i]);
				}
			}
			if (hayUltimo){
				distancia += ultimo.Distancia(*it);
			}else{
				hayUltimo=true;
			}

			ultimo=*it;
			iterUltimo=*it;
			suma-=peso;

			if (esSolucionFinal) {
				solucion.push_back(*it);
			}
		}
		return distancia;
	}

	Nodo &dameNodo(vnod gimnasios, vnod &pokeParadas,  int indice){
		if(indice == -1){
			cout<<"Pusiste indice == -1, por eso te explota "<<endl;
		}
		if(indice < gimnasios.size()){
			return gimnasios[indice];
		}else{
			return pokeParadas[indice-gimnasios.size()-1];
		}
	}
	void imprimirSolucion(vint& solucion){
		cout<<"Solucion:";
		for (auto indice:solucion){
			cout<<indice<< " ";
		}
		cout<<endl;
	}
	void imprimirSolucion(vvint& bloques){
		cout<<"Solucion:";
		for (auto bloque:bloques){
			cout<<" | ";
			for (auto indice:bloque){
				cout<<indice<< " ";
			}
		}
		cout<<endl;
	}

	double long distancia (vnod &gimnasios, vnod &pokeParadas,  vint & solucion){
		auto ultimo = dameNodo(gimnasios,pokeParadas,solucion[0]);
		auto proximoUltimo=ultimo;
		double long suma=0;
		auto dis =0;
		//cout<<"suma"<<endl;
		for(auto indice:solucion){
			if (indice==solucion[0]){// ||  indice ==ultimo.DameIndice()){
				continue;
			}
			//for (size_t i = 1; i < solucion.size(); i++) {
			//    auto indice = solucion[i];
			proximoUltimo=dameNodo(gimnasios,pokeParadas,indice);

			int x = proximoUltimo.CordenadaX() - ultimo.CordenadaX();
			int y = proximoUltimo.CordenadaY() - ultimo.CordenadaY();
			if(x==0 && y==0){
				dis=0;
			}else{
				auto pre = pow(x, 2) + pow(y, 2);
				pre= sqrt(pre);
				if(!isnormal(pre)){
					dis=0;
				}else{
					dis= pre;
				}
			}
			//auto dis = proximoUltimo.Distancia(ultimo);
			if(!isnormal(dis)){

				cerr<<"ME DIO NAN"<<endl;
				cerr<<"Tenia dist: "<< suma<<"\t  e \t  Indice: "<<indice<<endl;
				cerr<<"Tenia desde nodo de indice "<<ultimo.DameIndice()<< " \t con pociones: "<<ultimo.DamePociones()<<endl;
				cerr<<"Tenia hasta nodo de indice "<<proximoUltimo.DameIndice()<< " \t con pociones: "<<proximoUltimo.DamePociones()<<endl;
				cerr<<"desde ( "<<proximoUltimo.CordenadaX()<<","<<proximoUltimo.CordenadaY()<< ") \t hasta: ("<<ultimo.CordenadaX()<<","<<ultimo.CordenadaY()<< ")"<<endl;
				imprimirSolucion(solucion);
				exit(1);
				//kill(getpid(), sig)
			}

			suma+=dis;
			ultimo=proximoUltimo;

		}
		return suma;
	}
	bool validarSol(vint & solucion){
		for (size_t i = 1; i < solucion.size(); i++) {
			if (solucion[i]==solucion[i-1]){
				//cerr<<"Boludo la puta q te pario esta repetido "<< solucion[i]<<endl;
				//exit(1);
				return false;
			}
		}
		return true;
	}
	bool validarSol(vnod& gimnasios,vint & solucion){
		int gimns=0;
		if (solucion[0]<= gimnasios.size()){ gimns++;}
		for (size_t i = 1; i < solucion.size(); i++) {
			if (solucion[i]==solucion[i-1]){
				//cerr<<"Boludo la puta q te pario esta repetido "<< solucion[i]<<endl;
				//exit(1);
				return false;
			}
			if (solucion[i]<= gimnasios.size()){ gimns++;}
		}

		return gimns==gimnasios.size();
	}
	void imprimirSolucion(vnod gimnasios, vnod pokeParadas,vint& solucion){
		cout<<"Solucion: dist= "<<distancia(gimnasios,pokeParadas,solucion)<<" ";
		for (auto indice:solucion){
			cout<<indice<< " ";
		}
		cout<<endl;
	}
