#include "../clases.h"
#include <iostream>
#include <chrono>
#include <limits>


using namespace std;

//Statics
static double MAX = numeric_limits<double>::max();

//Tipos
typedef vector<int> vint;


//variables globales
double MinGlobal;
double MinActual;
vint RecorridoGlobal;
vint RecorridoActual;
vnod PokeParadas;
vnod Gimnasios;
int GimRecorridos;
int PPRecorridas;
Mochila moch(0);
int PocionesNecesarias;
int CantBT;


//declaracion de funciones
void BT();
void voy(Nodo & p);
bool puedoIrG(Nodo & p);
bool puedoIrPP(Nodo & p);
Nodo & BuscarNodo(int n);
int Maximo(int a, int b);
void LecturaDatos();


//funciones

int main(){
	MinGlobal = MAX;
	MinActual=0;
	LecturaDatos();
	BT();
	cout<<"cant BT "<<CantBT<<endl;
	if(RecorridoGlobal.size() != 0){
		cout<< MinGlobal << " "<< RecorridoGlobal.size() <<" ";
		for(int i=0; i<RecorridoGlobal.size(); i++){
			cout<< RecorridoGlobal[i] << " ";	
		} 
	}
	else{
		cout<< -1;
	}
	cout<< endl;
	return 0;
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
	CantBT++;
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
	for (int i = 0; i < Maximo(Gimnasios.size(), PokeParadas.size()) ; ++i){
			//esto elige de donde salimos
			if(RecorridoActual.empty()){
				if(i<PokeParadas.size()){
					Nodo & pp = PokeParadas[i];
					int pociones = pp.DamePociones();
					//Como es la primer instancia siempre puedo ir, caso mochila capacidad 0 gimansios > 0 ya se descarta
					pp.Recorrer(true);
					RecorridoActual.push_back(pp.DameIndice());
					PPRecorridas++;
					moch.usarMochila(pociones);
					BT();
					pp.Recorrer(false);
					RecorridoActual.pop_back();
					PPRecorridas--;
					moch.Restaurar(0);
			 	}
			 	
			 	//Puede haber gimnasios que necesitan 0 Pociones
			 	if(i<Gimnasios.size()){
					Nodo & gim = Gimnasios[i];
					//si es posible ir con el gimnasio, marco y voy y desmarco
					if (puedoIrG(gim)){
						GimRecorridos++;
						gim.Recorrer(true);
						RecorridoActual.push_back(gim.DameIndice());
						BT();
						RecorridoActual.pop_back();
						gim.Recorrer(false);
						GimRecorridos--;
					}
				}
			}
			else{
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
	if(MochilaPost + (3*PPRestantes) < PocionesNecesarias) NoConsumoDemas = false;
	
	return !moch.estaLLena() && (p.Recorrido() == false) && NoConsumoDemas;
}

//Aca se trata de ver si se puede ir a un Gimnasio, es decir que tengamos las pociones necesarias y no haberlo recorrido antes.
bool puedoIrG(Nodo & p){
	return moch.DamePeso() >= -(p.DamePociones()) && (p.Recorrido() == false);
}

//Aca se decide ir a un Nodo sin importar si es PP o gimnasio, basicamente se marcan los estados para que el BT funcione bien
void voy(Nodo & p) {
	p.Recorrer(true);
	Nodo origen = BuscarNodo(RecorridoActual.back());
	double dist = origen.Distancia(p);
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



Nodo & BuscarNodo(int n){
	if(n<= Gimnasios.size()){
		return Gimnasios[n-1];
	}
	else{
		return PokeParadas[n-Gimnasios.size()-1];
	}
}



//Max entre 2 valores
int Maximo(int a, int b){
	if (a <= b)
	{
		return b;
	}
	return a;
}

