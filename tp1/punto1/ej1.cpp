#include <list>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
//#include <math>
#include <algorithm>

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

void lecturaDatos(string input, vector<int>& arq, vector<int>& can){
	fstream ip;
	ip.open(input);
	int n;
    int m;
    ip >> n >> m;
    int aux;
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
		sort(can.begin(), can.end());
		sort(arq.begin(), arq.end());
		sort(arqueologos.begin(),arqueologos.end());
		sort(canibales.begin(),canibales.end());
}

//saca un solo elemento igual a elem
void sacar(vector<int>& ls, int elem){
	for(unsigned int i = 0; i<ls.size();i++){
		if(ls[i] == elem){
			ls[i] = ls[ls.size()];
			ls.pop_back();
			break;
		}
	}
}

int maximo(const vector<int>& a){
	if(a.empty()) return -1;
	int max = a[0];
	for(unsigned int i = 0; i<a.size(); i++){
		if(max<a[i]) max = a[i];
	}
	return max;
}

int minimo(const vector<int>& a){
	if(a.empty()) return -1;
	int min = a[0];
	for(unsigned int i = 0; i <a.size();i++){
		if(a[i]<min) min = a[i];
	}
	return min;
}
/*
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
*/
/*
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
*/
//devuelve el integrante mas lento duh si no hay integrantes lo cual es medio tonto devueve -1
int integranteLento(const vector<int>& a, const vector<int>& b, const vector<int>& c, const vector<int>& d){
	vector<int> solus;
	int as = maximo(a);
	int bs = maximo(b);
	int cs = maximo(c);
	int ds = maximo(d);
	solus.push_back(as);
	solus.push_back(bs);
	solus.push_back(cs);
	solus.push_back(ds);
	return maximo(solus);
}

int suma(const vector<int>& ls){
	int sol = 0;
	for(unsigned int i = 0; i<ls.size(); i++) sol += ls[i];
	return sol;
}

int backtracking(vector<int> arqA, vector<int> canA, vector<int> arqB, vector<int> canB, vector<int>  victor){
	int acantB = arqB.size();
	int ccantB = canB.size();
	int acantA = arqA.size();
	int ccantA = canA.size();
	if(acantA== 0 && ccantA == 0) return 0;
	if(acantB == 0 && ccantB== 0 && acantA < ccantA) return -1;//es raro (marce) Caso mas canibales que arquelogos y no hayas llevado a nadie del otro lado. es decir todos los casos no validos(Javi)
	int lento = integranteLento(arqA, canA, arqB, canB);
	int cantot = acantA+ccantA +arqB.size()+canB.size();
	int oruga = (lento*cantot*10000) + 1; //este es un "caso peor", de manera que cualquier camino posible sea menor a este.
	//Es cuando solo hay canibales
	if(!canA.empty() && arqA.empty() && canB.empty() && arqB.empty()){
		if(canA.size() == 1) return canA.front();
		int rapido = minimo(canA);
		sacar(canA, rapido);
		int solpar = suma(canA);//cada elemento tiene que pasar, y siempre va acompañado del mas rapido.
		int sol = solpar + (ccantA-2)*rapido;//ccantA-2 es la cantidad de veces que vuelve el mas rapido.
		return sol;
	}
	//Es cuando solo hay Arqueologos
	if(canA.empty() && !arqA.empty() && canB.empty() && arqB.empty()){
		if(arqA.size() == 1) return arqA.front();
		int rapido = minimo(arqA);
		sacar(arqA, rapido);
		int solpar = suma(arqA);//cada elemento tiene que pasar, y siempre va acompañado del mas rapido.
		int sol = solpar + (acantA-2)*rapido;//ccantA-2 es la cantidad de veces que vuelve el mas rapido.
		return sol;
	}
	victor[numeroArqueologos(arqA)+numeroCanibales(canA)] = 1;
	vector<int> soluciones;
	cout<<"hice algo con victor bien piola, marque esta posicion "<<numeroArqueologos(arqA)+numeroCanibales(canA) <<endl;
	//ahora veo que personajes puedo enviar al lado B y que hacer con ellos
	int segundoArqueologo=-1;
	int segundoCanibal = -1;
	int contador = 0;
	int contador_dos=0;
	for (int i = -1; i < acantA; i++) {//itero sobre los arqueologos del lado A
		for (int j = -1; j < ccantA; j++) {//itero sobre los canibales del lado A
			int velIda=0;
			if(i<0 && j<0) continue;
			segundoArqueologo=-1;
			segundoCanibal = -1;
			vector<int> arqAbis=arqA;
			vector<int> canAbis=canA;
			vector<int> arqBbis = arqB;
			vector<int> canBbis = canB;
			cerr<<"La cantidad de arq y can del lado A es "<<acantA<<", "<<ccantA<<endl;
			cerr<<"estoy mandando al "<<i<<" arqueologo y al "<<j<<" canibal";

			if(i>-1){
				//habia un remove fijarse si el orden importa, remove no tenemos uso sacar
				sacar(arqAbis, arqA[i]);
				//no lo metiamos, no tiene sentido.
				arqBbis.push_back(arqA[i]);
				contador=0;
			}else{
				//esto es cuando no mandas arqueologos, por lo que entendi contador tendria que ser canAbis.size()-1 ya que queres mandar un segundo canibal
				//contador = arqAbis.size();
				contador = canAbis.size() -1;//le resto 1 por que todavia no saque esse elemento entonces va a irse de rango si no se lo resto
			}
			if(j>-1){
				//Habia Rm(era conAbis pero creo que querias que sea canAbis
				sacar(canAbis,canA[j]);
				//no lo metiamos antes, lo cual no tiene sentido
				canBbis.push_back(canA[j]);
				contador=0;
			}else{
				//esto es cuando no mandas canibales, por lo que entendi contador tendria que ser arqAbis.size()-1 ya que queres mandar un segundo arqueologo
				//contador = canAbis.size();
				contador = arqAbis.size();//no le resto 1 por que ya se lo saque.
			}
			if(i==-1){
				velIda=canA[j];
			}else if(j==-1){
				velIda=arqA[i];
			}else{
				velIda=max(canA[j],arqA[i]);
			}
			acantB = arqBbis.size();
			ccantB = canBbis.size();
			cerr<<" El contador es "<<contador<<" La velocidad de Ida es "<<velIda<<endl;
			for (int segundo = -1; segundo < contador; segundo++) {//esta iteracion esta hecha para considerar si se manda un segundo arqueologo o canibal
											//cuestion q si se manda uno y uno contador vale 0 y entonces mas abajo donde se chequea la variable segundo
											//no va a tomar en cuenta su valor q va a ser solamente -1.
				for(int k = -1; k<acantB;k++){//arqueologos
					for(int l = -1; l<ccantB; l++){//canibales es 5 veces
						if(arqAbis.size()==0 && canAbis.size()==0) return velIda;
						int velVuelta = - oruga;
						//cree copias, por que si no estas devolviendo sobre cosas ya devueltas todo un quilombo, lo que aux era bis.
						vector<int> arqAaux(arqAbis);
						vector<int> canAaux(canAbis);
						vector<int> arqBaux(arqBbis);
						vector<int> canBaux(canBbis);
						cerr<<"estan volviendo con el "<< k<<" arqueologo y el "<<l<<" canibal el segundo es "<<segundo<<endl;
						if(l < 0 && k < 0) continue;
						int solbc = 0;
						if(i>-1){//me parece que por ahi lo del segundo es mas facil pensar con un if(i<0) como no mande arqueologos
							// mandaste arqueologos, queres ver si tenes que mandar otro, (sin contar que esto se rompe en la primer iteracion
							//-1 no esta en rango), me parece que lo que queres hacer aca es adentro del if. lo metes dos veces no tiene sentido
							//ademas te olvidas de sacarlo de la lista de arqAbis
							//arqBbis.push_back(arqAbis[segundo]);
							if(segundo>-1){
								arqBaux.push_back(arqAbis[segundo]);
								velIda=max(velIda,arqAbis[segundo]);
								cerr<<"en realidad estoy mandando dos arquelogos su velocidad de ida es "<<velIda<<endl;
								sacar(arqAaux, arqAbis[segundo]);//me parece que tenemos que sacarlo si lo mandamos al otro lado
							}
						}
						if(j>-1){
							//leer arriba analogo
							//canBbis.push_back(canAbis[segundo]);
							if(segundo>-1){
								canBaux.push_back(canAbis[segundo]);
								velIda=max(velIda,canAbis[segundo]);
								cerr<<"en realidad estoy mandando dos canibales su velocidad de ida es "<<velIda<<endl;
								sacar(canAaux, canAbis[segundo]);
							}
						}
						if(k>-1){
							arqAaux.push_back(arqBbis[k]);
							//Habia Rm
							sacar(arqBaux, arqBbis[k]);
							contador_dos=0;
						}else{
							//idem arriba me pa que aca va el canBbis por que no estas mandando arqueologos devuelta
							//contador_dos = arqBbis.size();
							contador_dos = canBbis.size()-1; //le resto uno por que no modifique canBbis todavia
						}
						if(l>-1){
							canAaux.push_back(canBbis[j]);
							//Habia Rm
							sacar(canBaux, canBbis[i]);
							contador_dos=0;
						}else{//idem arriba
							//contador_dos = canBbis.size();
							contador_dos = arqBbis.size();
						}
						if(k==-1){
							velVuelta=canBbis[l];
						}else if(j==-1){
							velVuelta=arqBbis[k];
						}else{
							velVuelta=max(canBbis[l],arqBbis[k]);
						}
						cerr<<" El contador es "<< contador_dos;
						for (int segundo_que_vuelve = -1; segundo_que_vuelve < contador_dos;segundo_que_vuelve++) {
							if(k>-1){//caso analogo arribaa
								//arqBbis.push_back(arqAbis[segundo_que_vuelve]);
								if(segundo_que_vuelve>-1){
									arqAaux.push_back(arqBbis[segundo_que_vuelve]);
									velVuelta=max(velVuelta,arqBbis[segundo_que_vuelve]);
									sacar(arqBaux, arqBbis[segundo_que_vuelve]);
								}
							}
							if(l>-1){//casoAnalogoarriba me parece tambien que es canAbisPushback(canBbis[])
								//canAbis.push_back(canAbis[segundo_que_vuelve]);
								if(segundo_que_vuelve>-1){
									canAaux.push_back(canAbis[segundo_que_vuelve]);
									velVuelta = max(velVuelta,canBbis[segundo_que_vuelve]);
									sacar(canBaux, canBbis[segundo_que_vuelve]);
								}
							}
						cerr<<" la velocidad de vuelta es "<<velVuelta<<endl;
						cerr<<"el tamaño de victor es "<<victor.size()<< " y quiero acceder a "<< numeroArqueologos(arqAaux)+numeroCanibales(canAaux)<<endl;
						if(victor[numeroArqueologos(arqAaux)+numeroCanibales(canAaux)] == 0){
							cerr<<"victor funciono entro en el bc"<<endl;
							solbc = backtracking(arqAaux, canAaux, arqBaux, canBaux, victor);
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
	vector<int> solrec;
	for(unsigned int i = 0; i<soluciones.size(); i++){
		if(soluciones[i] >= 0) solrec.push_back(soluciones[i]);
	}
	if(solrec.empty()) return -1;
	int sol = solrec[0];
	for(unsigned int i = 0; i<solrec.size(); i++){
		if(solrec[i] < sol) sol = solrec[i];
	}
	return sol;
}

int solucion(const vector<int>& arq,const vector<int>& can){
	vector<int> arqB;
	vector<int> canB;
	vector<int> n(can.size() +1, 0);
	//vector< vector<int> > matriz(arq.size()+1, n);
	cerr<<"que pija es 1<<(arq.size()+can.size()-1)? "<< (1<<(arq.size()+can.size()))<<endl;
	vector<int> victor(1<<(arq.size()+can.size()), 0);
cout<<"cree victor entro en BC"<<endl;
	//la matriz chequea que esa combinacion de arqueologos/canibales no hayan esperado del lado A antes.
	return backtracking(arq, can, arqB, canB, victor);
}


int main(int argc, char *argv[]){

    vector<int> arqA;
    vector<int> canA;



    string input = argv[1];
    lecturaDatos(input, arqA,canA);

	cout<< solucion(arqA, canA)<<endl;

    return 0;

}
