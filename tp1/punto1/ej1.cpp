#include <list>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <math>

using namespace std;
std::vector<int> arqueologos;
std::vector<int> canibales;

int indiceCanibal(int velocidad){
	size_t i = 0;
	int res=-1;
	while ( i < canibales.size()) {
		if(canibales[i] ==velocidad ){
			res=i;
			i=canibales.size();
		}
		i++;
	}
	return res;
}

int indiceArqueologo(int velocidad){
	size_t i = 0;
	int res=-1;
	while (i < arqueologos.size()) {
		if(arqueologos[i] ==velocidad){
			res=i;
			i=arqueologos.size();
		}
		i++;
	}
	return res;
}

int mascaraCanibal(int velocidad){
 return 1<<(arqueologos.size() +indiceCanibal(velocidad));
}
int mascaraArqueologo(int velocidad){
 return 1<<indiceArqueologo(velocidad);
}
int numeroCanibales(vector <int> can){
	int res=0;
	for (size_t i = 0; i < can.size(); i++) {
		res+=mascaraCanibal(can[i]);
	}
	return res;
}
int numeroArqueologos(vector <int> arq){
	int res=0;
	for (size_t i = 0; i < arq.size(); i++) {
		res+=mascaraArqueologo(arq[i]);
	}
	return res;
}
//se asegura que al enviar a cantA y cantC no haya una muerte sangrienta de algun lado
bool puedensalir(int cantA, int cantC, int arcMismoLado, int canMismoLado, int arcOtroLado, int canOtroLado){
	bool p =arcMismoLado - cantA >= canMismoLado - cantC || arcMismoLado - cantA == 0;
	bool q = arcOtroLado +cantA >= canOtroLado + cantC || arcOtroLado +cantA == 0;
	bool s = arcMismoLado - cantA >= 0 && canMismoLado - cantC >= 0;
	return p && q && s;
}

void lecturaDatos(string input, list<long>& arq, list<long>& can){
	fstream ip;
	ip.open(input);
	int n;
    int m;
    ip >> n >> m;
    long aux;
    for (int i = 0; i < n; ++i){
        ip >> aux;
        arq.push_back(aux);
				arqueologos.push_back(aux);
    }
    for (int i = 0; i < m; ++i){
        ip >> aux;
        can.push_back(aux);
				canibales.push_back(aux);
    }
		can.sort(can.begin(),can.end());
		arq.sort(arq.begin(),arq.end());
		arqueologos.sort(arqueologos.begin(),arqueologos.end());
		canibales.sort(canibales.begin(),canibales.end());
}

//saca un solo elemento igual a elem
list<long> sacar(list<long> ls, long elem){
	list<long> res;
	bool noencontre = true;
	while(!ls.empty()){
		long aux = ls.front();
		ls.pop_front();
		if(elem == aux){
			if(noencontre){
				noencontre = false;
			}
			else{
				res.push_front(aux);
			}
		}
		else{
			res.push_front(aux);
		}
	}
	return res;
}

long maximo(list<long> a){
	if(a.empty()) return -1;
	long max = a.front();
	while(!a.empty()){
		if(max < a.front()) max = a.front();
		a.pop_front();
	}
	return max;
}

long minimo(list<long> a){
	if(a.empty()) return -1;
	long min = a.front();
	while(!a.empty()){
		if(min > a.front()) min = a.front();
		a.pop_front();
	}
	return min;
}

long meterVuelta(int i, int j, list<long>& ArqA,list<long>& CanA, list<long>& ArqB, list<long>& CanB ){//esta funcion mantiene la hipotesis de que siempre combiene mandar el mas lento y el mas rapido
	long res;
	if (i==2) {
		long a= minimo(ArqB);
		ArqB = sacar(ArqB, a);
		long b= minimo(ArqB);
		ArqB = sacar(ArqB, b);
		ArqA.push_front(b);
		ArqA.push_front(a);
		res=b;
	}
	if (j==2) {
		long a= minimo(CanB);
		CanB = sacar(CanB, a);
		long b= minimo(CanB);
		CanB = sacar(CanB, b);
		CanA.push_front(b);
		CanA.push_front(a);
		res=b;
	}
	if (i==1 && j==1) {
	  long a= minimo(ArqB);
	  long b= minimo(CanB);
	  ArqB = sacar(ArqB, a);
	  ArqA.push_front(a);
	  CanB = sacar(CanB, b);
	  CanA.push_front(b);
	  res = b;
	  if(a>=b){
		res=a;
	  }
	}else if (i==1) {
		long a= minimo(ArqB);
		ArqB = sacar(ArqB,a);
		ArqA.push_front(a);
		res=a;
		}else if (j==1) {
			long a = minimo(CanB);
			CanB = sacar(CanB, a);
			CanA.push_front(a);
			res=a;
		}
return res;
}

long meterIda(int i, int j, list<long>& ArqA,list<long>& CanA, list<long>& ArqB, list<long>& CanB ){//MODIFICAR PARA QUE CONTEMPLE TODOS LOS CASOS
  long res=0;
  if(i==2){
    long a=maximo(ArqA);
    long b=minimo(ArqA);
    ArqB.push_front(a);
    ArqB.push_front(b);
    ArqA = sacar(ArqA, a);
    ArqA = sacar(ArqA, b);
    res= a;
}
  if(j==2){
    long a= maximo(CanA);
    long b= minimo(CanA);
    CanB.push_front(a);
    CanB.push_front(b);
    CanA= sacar(CanA, a);
    CanA = sacar(CanA, b);
    res=a;
  }
  if (i==1 && j==1){    //vuelven los dos mas chicos(!?!?!?!)Serian los mas rapidos
    long a=minimo(ArqA);
    long b=minimo(CanA);
    if(a >= b){
      long c= maximo(ArqA);
      CanB.push_front(b);
      CanA = sacar(CanA, b);
      ArqB.push_front(c);
      ArqA = sacar(ArqA, c);
      res=c;
  }else{
	  long c= maximo(CanA);
      ArqB.push_front(a);
      ArqA = sacar(ArqA, a);
      CanB.push_front(c);
      CanA = sacar(CanA, c);
      res=c;
    }
  }else if (i==1) {
		long a=minimo(ArqA);
		ArqB.push_front(a);
		ArqA = sacar(ArqA, a);
		res=a;
	}else if (j==1) {
			long a= minimo(CanA);
			CanB.push_front(a);
			CanA =sacar(CanA, a);
			res=a;
		}
return res;
}

//devuelve el integrante mas lento duh si no hay integrantes lo cual es medio tonto devueve -1
long integranteLento(const list<long>& a, const list<long>& b, const list<long>& c, const list<long>& d){
	list<long> solus;
	long as = maximo(a);
	long bs = maximo(b);
	long cs = maximo(c);
	long ds = maximo(d);
	solus.push_front(as);
	solus.push_front(bs);
	solus.push_front(cs);
	solus.push_front(ds);
	return maximo(solus);
}

long suma(list<long> ls){
	long sol = 0;
	while(!ls.empty()){
		long aux = ls.front();
		ls.pop_front();
		sol += aux;
	}
	return sol;
}

long backtracking(list<long> arqA, list<long> canA, list<long> arqB, list<long> canB, vector<int>  victor){
	int acantB = arqB.size();
	int ccantB = canB.size();
	int acantA = arqA.size();
	int ccantA = canA.size();
	if(acantA== 0 && ccantA == 0) return 0;
	if(acantB == 0 && ccantB== 0 && acantA < ccantA) return -1;//es raro (marce) Caso mas canibales que arquelogos y no hayas llevado a nadie del otro lado. es decir todos los casos no validos(Javi)
	long lento = integranteLento(arqA, canA, arqB, canB);
	int cantot = acantA+ccantA +arqB.size()+canB.size();
	long oruga = (lento*cantot*10000) + 1; //este es un "caso peor", de manera que cualquier camino posible sea menor a este.
	//Es cuando solo hay canibales
	if(!canA.empty() && arqA.empty() && canB.empty() && arqB.empty()){
		if(canA.size() == 1) return canA.front();
		long rapido = minimo(canA);
		long solpar = suma(sacar(canA, rapido));//cada elemento tiene que pasar, y siempre va acompañado del mas rapido.
		long sol = solpar + (ccantA-2)*rapido;//ccantA-2 es la cantidad de veces que vuelve el mas rapido.
		return sol;
	}
	//Es cuando solo hay Arqueologos
	if(canA.empty() && !arqA.empty() && canB.empty() && arqB.empty()){
		if(arqA.size() == 1) return arqA.front();
		long rapido = minimo(arqA);
		long solpar = suma(sacar(arqA, rapido));//cada elemento tiene que pasar, y siempre va acompañado del mas rapido.
		long sol = solpar + (acantA-2)*rapido;//ccantA-2 es la cantidad de veces que vuelve el mas rapido.
		return sol;
	}
	victor[numeroArqueologos(arqA)+numeroCanibales(canA)] = 1;
	vector<long> soluciones;
	//ahora veo que personajes puedo enviar al lado B y que hacer con ellos
	int segundoArqueologo=-1;
	int segundoCanibal = -1;
	int contador = 0;
	int contador_dos=0;
	for (size_t i = -1; i < arqA.size(); i++) {//itero sobre los arqueologos del lado A
		for (size_t j = -1; j < canA.size(); j++) {//itero sobre los canibales del lado A
			int velIda=0;
			if(i<0 && j<0) continue;
			segundoArqueologo=-1;
			segundoCanibal = -1;
			list<long> arqAbis=arqA;
			list<long> canAbis=canA;

			if(i>-1){
				arqAbis.remove(arqA[i]);
				contador=0;
			}else{
				contador = arqAbis.size();
			}
			if(j>-1){
				conAbis.remove(conA[i]);
				contador=0;
			}else{
				contador = canAbis.size();
			}
			if(i==-1){
				velIda=conAbis[j];
			}else i (j==-1){
				velIda=arqAbis[i];
			}else{
				velIda=max(conAbis[j],arqAbis[i]);
			}
			for (size_t segundo = -1; segundo < contador; segundo++) {//esta iteracion esta hecha para considerar si se manda un segundo arqueologo o canibal
																																//cuestion q si se manda uno y uno contador vale 0 y entonces mas abajo donde se chequea la variable segundo
																																//no va a tomar en cuenta su valor q va a ser solamente -1.
				for(int k = -1; k<arqB.size();k++){//arqueologos
					for(int l = -1; l<canB.size(); l++){//canibales es 5 veces
						if(l < 0 && k < 0) continue;
						long velVuelta = - oruga;
						long solbc = 0;
						if(i>-1){
							arqBbis.push_back(arqAbis[segundo]);
							if(segundo>-1){
								arqBbis.push_back(arqAbis[segundo]);
								velIda=max(velIda,arqAbis[segundo]);
							}
						}
						if(j>-1){
							conBbis.push_back(conAbis[segundo]);
							if(segundo>-1){
								conBbis.push_back(conAbis[segundo]);
								velIda=max(velIda,conAbis[segundo]);
							}
						}
						if(k>-1){
							arqAbis.push_back(arqBbis[k]);
							arqBbis.remove(arqBbis[k]);
							contador_dos=0;
						}else{
							contador_dos = arqBbis.size();
						}
						if(l>-1){
							conAbis.push_back(conBbis[j]);
							conBbis.remove(conBbis[i]);
							contador_dos=0;
						}else{
							contador_dos = conBbis.size();
						}
						if(k==-1){
							velVuelta=conBbis[l];
						}else i (j==-1){
							velVuelta=arqNbis[k];
						}else{
							velVuelta=max(conBbis[l],arqBbis[k]);
						}
						for (size_t segundo_que_vuelve = -1; segundo_que_vuelve < contador_dos;segundo_que_vuelve++) {
							if(k>-1){
								arqBbis.push_back(arqAbis[segundo_que_vuelve]);
								if(segundo_que_vuelve>-1){
									arqAbis.push_back(arqBbis[segundo_que_vuelve]);
									velVuelta=max(velVuelta,)
								}
							}
							if(l>-1){
								conAbis.push_back(conAbis[segundo_que_vuelve]);
								if(segundo_que_vuelve>-1){
									conAbis.push_back(conAbis[segundo_que_vuelve]);
								}
							}
						if(victor[numeroArqueologos(arqAbis)+numeroCanibales(canAbis)] == 0){
							solbc = backtracking(arqAbis, canAbis, arqBbis, canBbis, victor);
							if(solbc >-1){
								soluciones.push_back(velIda + velVuelta + solbc);
							}
						}
						}
					}
				}
			}
		}
	}
	vector<long> solrec;
	for(unsigned int i = 0; i<soluciones.size(); i++){
		if(soluciones[i] >= 0) solrec.push_back(soluciones[i]);
	}
	if(solrec.empty()) return -1;
	long sol = solrec[0];
	for(unsigned int i = 0; i<solrec.size(); i++){
		if(solrec[i] < sol) sol = solrec[i];
	}
	return sol;
}

long solucion(const list<long>& arq,const list<long>& can){
	list<long> arqB;
	list<long> canB;
	vector<int> n(can.size() +1, 0);
	//vector< vector<int> > matriz(arq.size()+1, n);
	vector<int> victor(1<<(arq.size()+can.size()-1), 0);

	//la matriz chequea que esa combinacion de arqueologos/canibales no hayan esperado del lado A antes.
	return backtracking(arq, can, arqB, canB, victor);
}

/*
int main(int argc, char *argv[]){

    list<long> arqA;
    list<long> canA;



    string input = argv[1];
    lecturaDatos(input, arqA,canA);

	cout<< solucion(arqA, canA)<<endl;

    return 0;

}

*/
