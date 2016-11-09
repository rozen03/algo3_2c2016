#include "../clases.h"
#include <iostream>
#include <chrono>
#include <limits>


using namespace std;

//variables globales
unsigned int GimRecorridos;
int PPRecorridas;
int PocionesNecesarias;
int CantBT;
/*
vnod PokeParadas;
vnod Gimnasios;
Mochila moch(0);
double MinGlobal;
double MinActual;
vint RecorridoGlobal;
vint RecorridoActual;
*/

//declaracion de funciones
void BT();
void voy(Nodo & p);
bool puedoIrG(Nodo & p);
bool puedoIrPP(Nodo & p);
Nodo & BuscarNodo(unsigned int n);
unsigned int Maximo(unsigned int a,unsigned int b);
void LecturaDatos();
double pto1(vnod gim, vnod pp, Mochila moch, vint & recorrido);
//bool PodaPokeparadaMochila(vnod & gim, int cantPP, int capMoch);
void Reset(vnod & PP, vnod & G, Mochila mochil);


//funciones
/*
int main(){
	LecturaDatos();
	vnod ppAux = PokeParadas;
	vnod gimAux = Gimnasios;
	cout<<"imprimo pp y su copa, gimnasios y su copia \n";
	ImprimirNod(PokeParadas);
	cout<<endl;
	ImprimirNod(ppAux);
	cout<<endl;
	ImprimirNod(Gimnasios);
	cout<<endl;
	ImprimirNod(gimAux);
	cout<<"\n despues de borrar tienen que estar vacios"<<endl;
	Gimnasios.clear();
	PokeParadas.clear();
	ImprimirNod(Gimnasios);
	ImprimirNod(PokeParadas);
	cout<<"\n pero las copias tienen que funcionar"<<endl;
	ImprimirNod(gimAux);
	cout<<endl;
	ImprimirNod(ppAux);
	cout<<endl;
	Mochila mochAux(moch.DameCapacidad());
	moch.CambiarCapacidad(1);
	MinGlobal= -1000;
	MinActual = 1000;
	RecorridoGlobal.push_back(139);
	RecorridoActual.push_back(155);;
    GimRecorridos = 1;
    PPRecorridas = 100;
	PocionesNecesarias = -100;
	CantBT = 15;

	vint recorrido;
	double res = pto1(gimAux, ppAux, mochAux, recorrido);
	cout<<res<<" "<<recorrido.size()<<" ";
	if(res != -1){
		for(unsigned int i=0; i<RecorridoGlobal.size(); i++){
			cout<< RecorridoGlobal[i] << " ";
		}
	}
	else{
		cout<< -1;
	}
	/*MinGlobal = MAX;
	MinActual=0;
	LecturaDatos();
	bool superPoda = PodaPokeparadaMochila(gim, pp.size(), mochil.Capacidad());
	if(superPoda){
		BT();
		cout<<"cant BT "<<CantBT<<endl;
		if(RecorridoGlobal.size() != 0){
			cout<< MinGlobal << " "<< RecorridoGlobal.size() <<" ";
			for(unsigned int i=0; i<RecorridoGlobal.size(); i++){
				cout<< RecorridoGlobal[i] << " ";
			}
		}
		else{
			cout<< -1;
		}
		cout<< endl;
	}
	else{
		cout<<-1<<endl;
	}
	return 0;
}*/

void Reset(vnod & PPAux,vnod & GAux, Mochila mochil){
	CantBT = 0;
	MinGlobal = MAX;
	MinActual=0;
	RecorridoGlobal.clear();
	RecorridoActual.clear();
	GimRecorridos = 0;
	PPRecorridas = 0;
	PokeParadas = PPAux;
	Gimnasios = GAux;
	int pocNecAux = 0;
	for(unsigned int i = 0; i<GAux.size(); i++) pocNecAux -= GAux[i].DamePociones();
	PocionesNecesarias = pocNecAux;
	moch.CambiarCapacidad(mochil.DameCapacidad());
	moch.Restaurar(0);
}

/*
bool PodaPokeparadaMochila(vnod & gim, int cantPP, int capMoch){
	int sumaTotal;
	int max = 0;
	for(int i = 0; i< gim.size(); i++){
		int poc = - gim[i].DamePociones();
		if(poc > max) max = poc;
		suma += poc;
	}
	int cantMin cantPP+1;
	if(capMoch >= max + (max % 3)){
		double aux  = suma / 3;
		cantMin = floor(aux);
	}
	return cantMin <= cantPP;
}
*/
double pto1(vnod gim, vnod pp, Mochila mochil, vint & recorrido){
	Reset(pp, gim, mochil);
	bool superPoda = true ;//PodaPokeparadaMochila(gim, pp.size(), mochil.Capacidad());
	double res = -1;
	if(superPoda){
		BT();
		recorrido = RecorridoGlobal;
		res = MinGlobal;
	}
	if(recorrido.empty()) res = -1;
	return res;
}

void LecturaDatos(){
	int n, m, k;
	int maxPos = 0;
	cin>> n >> m >> k;
	moch.CambiarCapacidad(k);
	int PocionesQueDaPP = 3;
	if(k<3) PocionesQueDaPP = k;
	for(int i=1; i<=n; i++){
		int x,y,p;
		cin>> x >> y >> p;
		PocionesNecesarias += p;
		if(maxPos < p) maxPos = p;
		Nodo nuevo = Nodo(-p,i,x,y);
		Gimnasios.push_back(nuevo);
	}
	if(maxPos > k || m*PocionesQueDaPP < PocionesNecesarias) {
	cout<< -1<<endl;
	return;
	}
	for(int i=n+1; i<= n+m; i++){
		int x,y;
		cin>> x >> y;
		Nodo nuevo= Nodo(3,i,x,y);
		PokeParadas.push_back(nuevo);
	}
}

void BT(){
	//Quiero cortar o en el caso de que ya hay una solucion mejor o cuando ya recorri todos los gimnasios.
	if(MinActual> MinGlobal) return;
	if(GimRecorridos == Gimnasios.size()){
		if(MinActual < MinGlobal){
			MinGlobal=MinActual;
			RecorridoGlobal=RecorridoActual;
		}
		return;
	}
 	//Voy A un gimnasio o a una pokeparada.
	for (unsigned int i = 0; i < Maximo(Gimnasios.size(), PokeParadas.size()) ; ++i){
		if(i<Gimnasios.size()){
			Nodo & gim = Gimnasios[i];
			//si es posible ir con el gimnasio, marco y voy y desmarco
			if (puedoIrG(gim)){
				GimRecorridos++;
				//como las pociones de un gimnasio son negativas y quiero achicar la catidad de pociones se suma
				PocionesNecesarias += gim.DamePociones();
				voy(gim);
				PocionesNecesarias -= gim.DamePociones();
				GimRecorridos--;
			}
		}

		//Voy a pokeparadas
		if(i<PokeParadas.size()){
			Nodo & pp = PokeParadas[i];
			//Se marca afuera del if, por que el calculo de PPrecorridas se hace asumiendo que consumo esa
			//PP, si no podia ir por que ya habia ido corta por otro lado.
			PPRecorridas++;
			//si es posible ir a pokeparada, marco y voy y desmarco
			if(puedoIrPP(pp)){
				voy(pp);
			}
			PPRecorridas--;
		}
	}
}

/* Aca se Trata e fijarse si puedo ir a una PP, es decir si ya no fui, o si vale la pena ir, es decir si la mochila ya esta llena, no vale la pena ir
 *  ya que gasto esas pociones, si consumo de mas, es decir que si al ir a la PP tengo que tirar una pocion y esa pocion era necesaria para la solucion.
 *
 * Aca Hay dos Podas, si la Mochila esta LLena, y si Consumo de mas. a simple vista se puede pensar que la mochila este llena es abarcado por consumir de mas,
 * pero no, puedo tener situaciones donde descartar 3 pociones no me lleva a una instancia donde no tego forma de completar todos los gimnasios, ej PP>>gim
 */
bool puedoIrPP( Nodo & p){
	bool NoConsumoDemas = true;
	int pociones = p.DamePociones();
	int pocionesEnMoch = moch.DamePeso();
	moch.usarMochila(pociones);
	int MochilaPost = moch.DamePeso();
	moch.Restaurar(pocionesEnMoch);
	int pocionesQueDa = 3;
	if(moch.DameCapacidad()<3) pocionesQueDa = moch.DameCapacidad();
	int PPRestantes = PokeParadas.size() - PPRecorridas;
	if(MochilaPost + (pocionesQueDa*PPRestantes) < PocionesNecesarias) NoConsumoDemas = false;

	return !moch.estaLLena() && (p.Recorrido() == false) && NoConsumoDemas;
}

//Aca se trata de ver si se puede ir a un Gimnasio, es decir que tengamos las pociones necesarias y no haberlo recorrido antes.
bool puedoIrG(Nodo & p){
	return moch.DamePeso() >= -(p.DamePociones()) && (p.Recorrido() == false);
}

//Aca se decide ir a un Nodo sin importar si es PP o gimnasio, basicamente se marcan los estados para que el BT funcione bien
void voy(Nodo & p) {
	p.Recorrer(true);
	double dist = 0;
	if(!RecorridoActual.empty()){
		 Nodo origen = BuscarNodo(RecorridoActual.back());
		 dist = origen.Distancia(p);
	 }
	MinActual += dist;
	RecorridoActual.push_back(p.DameIndice());
	int pociones = p.DamePociones();
	int pocionesEnMoch = moch.DamePeso();
	moch.usarMochila(pociones);
	BT();
	MinActual -= dist;
	RecorridoActual.pop_back();
	p.Recorrer(false);
	moch.Restaurar(pocionesEnMoch);
}

Nodo & BuscarNodo(unsigned int n){
	if(n<= Gimnasios.size()){
		return Gimnasios[n-1];
	}
	else{
		return PokeParadas[n-Gimnasios.size()-1];
	}
}



//Max entre 2 valores
unsigned int Maximo(unsigned int a,unsigned int b){
	if (a <= b)
	{
		return b;
	}
	return a;
}
