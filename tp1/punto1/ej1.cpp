#include <list>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

using namespace std;

/*
 Comentarios de  una mente tormentada(?:
 
 Bueno basicamente se rompe en todos lados, puedensalir es el peor funcion de cuatro lineas que escribi en mi vida...
 basicamente se fija si esa cantidad de arqueologos y canibales pueden salir, pero le dice que no a casos re obvio 1-1 y otros.
 
 otro lugar donde se rompe, esta devolviendo como valor optimo los minimos de cada archivo, lo cual esta mal, puede estar en un millon de lados,
 la oruga funciona, osea hace bien el calculo, pero no funciona como deberia, basicamente la idea era que cuando esl algoritmo corte por que no
 encontraba la forma de avanzar sin que se lo coman los canibales ponga un valor negativo para filtrarlo despues.
 
 errores por todos lados es la conclusion y mañana va dentro de un par de horas con una cabeza mas sana probablemente pueda arreglar cosas.
 hasta ese momento se los dejo a ustedes.
 
 sigo escribiendo por que justo salio alta cancion y bue algo tengo que hacer, no?
 */

//se asegura que al enviar a cantA y cantC no haya una muerte sangrienta de algun lado
bool puedensalir(int cantA, int cantC, int arcMismoLado, int canMismoLado, int arcOtroLado, int canOtroLado){
	//cerr<<"entro a pueden salir"<<endl;
	bool p =arcMismoLado - cantA >= canMismoLado - cantC || arcMismoLado - cantA == 0;
	bool q = arcOtroLado +cantA >= canOtroLado + cantC || arcOtroLado +cantA == 0;
	bool s = arcMismoLado - cantA >= 0 && canMismoLado - cantC >= 0;
	//cerr<<"salgo de pueden salir y el valor es "<<p && q && s;
	return p && q && s;
}

void lecturaDatos(string input, list<long>& arq, list<long>& can){
	fstream ip;
	ip.open(input);
	int n;
    int m;
    ip >> n >> m;

    long aux;
	//cout<< input<<endl;
    for (int i = 0; i < n; ++i){
        ip >> aux;
        arq.push_back(aux);
        }
    for (int i = 0; i < m; ++i){
        ip >> aux;
        can.push_back(aux);
        }
}

//saca un solo elemento igual a elem
list<long> sacar(list<long> ls, long elem){
	list<long> res;
	/*
				list<long> arqAm(ls);
				cerr<<"ls(sacar) tiene\n";
				while(!arqAm.empty()){
					long aux = arqAm.front();
					arqAm.pop_front();
					cerr<< aux<<" ";
				}cerr<<endl;
*/
	
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
	/*
	list<long> arqA(res);
				cerr<<"res(sacar) tiene\n";
				while(!arqA.empty()){
					long aux = arqA.front();
					arqA.pop_front();
					cerr<< aux<<" ";
				}cerr<<endl;*/
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
  if(a>=b){
    res=a;
  }
  else{
    res=b;
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
    //~ cerr<<"estoy en meter ida 2 can el valor es " << a<<endl;
    res= a;
}
  if(j==2){
    long a= maximo(CanA);
    long b= minimo(CanA);
    CanB.push_front(a);
    CanB.push_front(b);
    CanA= sacar(CanA, a);
    CanA = sacar(CanA, b);
    //~ cerr<<"estoy en meter ida 2 can el valor es " << a<<endl;
    res=a;
  }
  if (i==1 && j==1){    //vuelven los dos mas chicos(!?!?!?!)
    long a=minimo(ArqA);
    long b=minimo(CanA);
    if(a >= b){
      long c= maximo(ArqA);
      CanB.push_front(b);
      CanA = sacar(CanA, b);
      ArqB.push_front(c);
      ArqA = sacar(ArqA, c);
      res=c;
      
      //~ cerr<<"estoy en meter ida ij = 1 el mas rapido es canibal y el valor es " <<res <<endl;
    }else{
	  long c= maximo(CanA);
      ArqB.push_front(a);
      ArqA = sacar(ArqA, a);
      CanB.push_front(c);
      CanA = sacar(CanA, c);
      res=c;
      
      //~ cerr<<"estoy en meter ida ij = 1 el mas rapido es arq y el valor es " <<res <<endl;
    }
  }else if (i==1) {
		long a=minimo(ArqA);
		ArqB.push_front(a);
		ArqA = sacar(ArqA, a);
		res=a;
		
      //~ cerr<<"estoy en meter ida i = 1 el mas rapido es canibal y el valor es " <<res <<endl;
	}else if (j==1) {
			long a= minimo(CanA);
			CanB.push_front(a);
			CanA =sacar(CanA, a);
			
			/*list<long> canAm(CanA);
				
				cerr<<"\ncanAux tiene\n";
				while(!canAm.empty()){
					long aux = canAm.front();
					canAm.pop_front();
					cerr<<aux<<" ";
				}cerr<<endl;
			*/res=a;
			
      //~ cerr<<"estoy en meter ida j = 1 el mas rapido es canibal y el valor es " <<res <<endl;
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
	/*
	cerr<<"tengo que entrar aca si el input es solo canibales"<<endl;
	list<long> arqAm(ls);
				cerr<<"ls(suma) tiene\n";
				while(!arqAm.empty()){
					long aux = arqAm.front();
					arqAm.pop_front();
					cerr<< aux<<" ";
				}*/
	
	while(!ls.empty()){
		long aux = ls.front();
		ls.pop_front();
		sol += aux;
	}
	return sol;
}

long backtracking(list<long> arqA, list<long> canA, list<long> arqB, list<long> canB, vector<vector<int> > matriz){
	int acantB = arqB.size();
	int ccantB = canB.size();
	int acantA = arqA.size();
	int ccantA = canA.size();
	if(acantA== 0 && ccantA == 0) return 0;
	if(acantB == 0 && ccantB== 0 && acantA < ccantA) return -1;//es raro (marce)
	long lento = integranteLento(arqA, canA, arqB, canB);
	int cantot = acantA+ccantA +arqB.size()+canB.size();
	long oruga = (lento*cantot*10000) + 1; //este es un "caso peor", de manera que cualquier camino posible sea menor a este.
	if(!canA.empty() && arqA.empty() && canB.empty() && arqB.empty()){
		if(canA.size() == 1) return canA.front();
		long rapido = minimo(canA);
		long solpar = suma(sacar(canA, rapido));//cada elemento tiene que pasar, y siempre va acompañado del mas rapido.
		long sol = solpar + (ccantA-2)*rapido;//ccantA-2 es la cantidad de veces que vuelve el mas rapido.
		return sol;
	}
	if(canA.empty() && !arqA.empty() && canB.empty() && arqB.empty()){
		if(arqA.size() == 1) return arqA.front();
		long rapido = minimo(arqA);
		long solpar = suma(sacar(arqA, rapido));//cada elemento tiene que pasar, y siempre va acompañado del mas rapido.
		long sol = solpar + (acantA-2)*rapido;//ccantA-2 es la cantidad de veces que vuelve el mas rapido.
		return sol;
	}
	
	
	
	matriz[acantA][ccantA] = 1;
	vector<long> soluciones;
	//ahora veo que personajes puedo enviar al lado B y que hacer con ellos
	for(int i = 0; i < 3; i++){//arquelogos
		for(int j = 0;j + i < 3; j++){//canibales Esta combinacion ij hace 5 iteraciones
			long velIda = -1;
			//cerr<<"Quiero ver quienes pueden ir a B "<< i <<" arqueologos y "<< j <<" canibales"<<endl;
			if( (i == 0 && j == 0) || (i == 0 && j == 1) || (i == 1 && j == 0)) continue;
			if(puedensalir(i, j, acantA, ccantA,arqB.size(), canB.size())){
				//cerr<<"Pueden ir a B " <<i << "arqueologos y " << j <<" canibales"<<endl;
				list<long> arqAux(arqA);
				list<long> canAux(canA);
				list<long> arqBaux(arqB);
				list<long> canBaux(canB);
/*
  			    list<long> arqAm(arqA);
				list<long> canAm(canA);
				list<long> arqBm(arqB);
				list<long> canBm(canB);
				cerr<<"PreMeterIda\n";
				cerr<<"arqAux tiene\n";
				while(!arqAm.empty()){
					long aux = arqAm.front();
					arqAm.pop_front();
					cerr<< aux<<" ";
				}
				cerr<<"\ncanAux tiene\n";
				while(!canAm.empty()){
					long aux = canAm.front();
					canAm.pop_front();
					cerr<<aux<<" ";
				}cerr<<"\narqBaux tiene\n";
				while(!arqBm.empty()){
					long aux = arqBm.front();
					arqBm.pop_front();
					cerr<<aux<<" ";
				}cerr<<"\ncanBaux tiene\n";
				while(!canBm.empty()){
					long aux = canBm.front();
					canBm.pop_front();
					cerr<<aux<<" ";
				}cerr<<endl;
				
	*/			
					velIda = meterIda(i, j, arqAux,canAux,arqBaux, canBaux);
			/*		
					arqAm =arqAux;
					canAm =canAux;
					arqBm =arqBaux;
					canBm =canBaux;
					cerr<<"Post meterIda"<<endl;
					cerr<<"arqAux tiene\n";
					while(!arqAm.empty()){
						long aux = arqAm.front();
						arqAm.pop_front();
						cerr<< aux<<" ";
					}
					cerr<<"\ncanAux tiene\n";
					while(!canAm.empty()){
						long aux = canAm.front();
						canAm.pop_front();
						cerr<<aux<<" ";
					}cerr<<"\narqBaux tiene\n";
					while(!arqBm.empty()){
						long aux = arqBm.front();
						arqBm.pop_front();
						cerr<<aux<<" ";
					}cerr<<"\ncanBaux tiene\n";
					while(!canBm.empty()){
						long aux = canBm.front();
						canBm.pop_front();
						cerr<<aux<<" ";
					}cerr<<endl<<endl;
				*/	
					for(int k = 0; k<3;k++){//arqueologos
						for(int l = 0; l+k<3; l++){//canibales es 5 veces
							//cerr<<"Entro en el for para ver quienes pueden volver Arc "<< k<<" can "<<l<<" Velocidad Ida " <<velIda<<endl;
							//cerr<<"estan vacias las listas? "<<arqAux.empty()<< " esa es arc, la proxima es can "<<canAux.empty()<<endl;
							long velVuelta = - oruga;
							long solbc = 0;
							int acant = arqAux.size();
							int ccant = canAux.size();
							if(l == 0 && k == 0) continue;
							if(arqAux.empty() && canAux.empty()) velVuelta =0;//caso base
							if(puedensalir(k, l, arqBaux.size(), canBaux.size(),acant, ccant) && matriz[acant+k][ccant+l] == 0){
							//	cerr<<"Pueden ir a A " <<k << "arqueologos y " << l <<" canibales"<<endl;
								list<long> arqAbis(arqAux);
								list<long> canAbis(canAux);
								list<long> arqBbis(arqBaux);
								list<long> canBbis(canBaux);
								velVuelta = meterVuelta(k, l, arqAbis, canAbis, arqBbis, canBbis);
								
					/*			arqAm =arqAbis;
								canAm =canAbis;
								arqBm =arqBbis;
								canBm =canBbis;
								cerr<<"Post meterVuelta"<<endl;
								cerr<<"arqAux tiene\n";
								while(!arqAm.empty()){
									long aux = arqAm.front();
									arqAm.pop_front();
									cerr<< aux<<" ";
								}
								cerr<<"\ncanAux tiene\n";
								while(!canAm.empty()){
									long aux = canAm.front();
									canAm.pop_front();
									cerr<<aux<<" ";
								}cerr<<"\narqBaux tiene\n";
								while(!arqBm.empty()){
									long aux = arqBm.front();
									arqBm.pop_front();
									cerr<<aux<<" ";
								}cerr<<"\ncanBaux tiene\n";
								while(!canBm.empty()){
									long aux = canBm.front();
									canBm.pop_front();
									cerr<<aux<<" ";
								}cerr<<endl<<endl;
								
						*/		
								solbc = backtracking(arqAbis, canAbis, arqBbis, canBbis, matriz);
							}
							//cerr<<"estoy metiendo esto en soluciones " <<velIda+velVuelta+solbc<<" Desglozado seria velIda "<<velIda<<" velVuelta "<<velVuelta<<" solbc "<<solbc<<" y oruga "<<oruga<< endl;
							soluciones.push_back(velIda + velVuelta + solbc);
						}
					}
				}
		}
	}
	//cerr<<"hola?"<<endl;
	vector<long> solrec;
	for(unsigned int i = 0; i<soluciones.size(); i++){
		//~ cerr<<soluciones[i]<<" ";
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
	vector< vector<int> > matriz(arq.size()+1, n);
	
	//la matriz chequea que esa combinacion de arqueologos/canibales no hayan esperado del lado A antes.
	return backtracking(arq, can, arqB, canB, matriz);
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