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
void BTA();
void BTB();
void BTC();
void BTAB();
void BTAC();
void BTBC();
void BTABC();
void voy(Nodo & p);
void voyA(Nodo & p);
void voyB(Nodo & p);
void voyC(Nodo & p);
void voyAB(Nodo & p);
void voyAC(Nodo & p);
void voyBC(Nodo & p);
void voyABC(Nodo & p);
bool puedoIrG(Nodo & p);
bool puedoIrPP(Nodo & p);
bool puedoIrPPA(Nodo & p);
bool puedoIrPPB(Nodo & p);
bool puedoIrPPC(Nodo & p);
bool puedoIrPPAB(Nodo & p);
bool puedoIrPPAC(Nodo & p);
bool puedoIrPPBC(Nodo & p);
bool puedoIrPPABC(Nodo & p);
Nodo & BuscarNodo(int n);
int Maximo(int a, int b);
void LecturaDatos();
void Reset(vnod & PP, vnod & G, int pocNecAux);


//funciones

int main(){
	MinGlobal = MAX;
	MinActual=0;
	vnod PPAux;
	vnod GAux;
	int pocNecAux;
	LecturaDatos();
	PPAux = PokeParadas;
	GAux = Gimnasios;
	pocNecAux = PocionesNecesarias;
	BT();
	int Cbt = CantBT;
	int dist = MinGlobal;
	vint Solbt = RecorridoGlobal;
	Reset(PPAux, GAux, pocNecAux);
	BTA();
	int CbtA = CantBT;
	int distA = MinGlobal;
	vint SolbtA = RecorridoGlobal;
	Reset(PPAux, GAux, pocNecAux);
	BTB();
	int CbtB = CantBT;
	int distB = MinGlobal;
	vint SolbtB = RecorridoGlobal;
	Reset(PPAux, GAux, pocNecAux);
	BTC();
	int CbtC = CantBT;
	int distC = MinGlobal;
	vint SolbtC = RecorridoGlobal;
	Reset(PPAux, GAux, pocNecAux);
	BTAB();
	int CbtAB = CantBT;
	int distAB = MinGlobal;
	vint SolbtAB = RecorridoGlobal;
	Reset(PPAux, GAux, pocNecAux);
	BTAC();
	int CbtAC = CantBT;
	int distAC = MinGlobal;
	vint SolbtAC = RecorridoGlobal;
	Reset(PPAux, GAux, pocNecAux);
	BTBC();
	int CbtBC = CantBT;
	int distBC = MinGlobal;
	vint SolbtBC = RecorridoGlobal;
	Reset(PPAux, GAux, pocNecAux);
	BTABC();
	int CbtABC = CantBT;
	int distABC = MinGlobal;
	vint SolbtABC = RecorridoGlobal;
	if(distABC == dist && distBC == distAC && distAB == distC && distB == distA && distC == distB && dist == distAC && dist == distA){
		cout<<"Cantidad de llamadas al BT dependiendo de las Podas, Sin Podas "<< Cbt<<", con Poda A "<<CbtA<<", con Poda B "<<CbtB;
		cout<<", con Poda C "<<CbtC<<", Con Poda AB "<<CbtAB<<", con Poda AC "<<CbtAC<<", con Poda BC "<<CbtBC<<", con poda ABC "<<CbtABC<<endl; 
	}
	else{
		cout<<"La Cagaste con una poda por favor no pls no sir pls no"<<endl;
		cout<<"Distancia dependiendo de las Podas, Sin Podas "<< dist<<", con Poda A "<<distA<<", con Poda B "<<distB<<", con Poda C "<<distC<<", Con Poda AB "<<distAB<<", con Poda AC "<<distAC<<", con Poda BC "<<distBC<<", con poda ABC "<<distABC<<endl; 
		cout<<"Sin Podas El recorrido es ";
		for(int i = 0; i < Solbt.size(); i++) cout<<Solbt[i]<<" ";
		cout<<"\nCon Poda A El recorrido es ";
		for(int i = 0; i <SolbtA.size(); i++) cout<<SolbtA[i]<<" ";
		cout<<endl;
	}

	cout<< endl;
	return 0;
}

void Reset(vnod & PPAux,vnod & GAux,int pocNecAux){
	CantBT = 0;
	MinGlobal = MAX;
	MinActual=0;
	RecorridoGlobal.clear();
	RecorridoActual.clear();
	GimRecorridos = 0;
	PPRecorridas = 0;
	PocionesNecesarias = pocNecAux;
	PokeParadas = PPAux;
	Gimnasios = GAux;
	moch.Restaurar(0);
}

void LecturaDatos(){
	int n, m, k;
	int maxPos = 0;
	cin>> n >> m >> k;
	moch.CambiarCapacidad(k);
	for(int i=1; i<=n; i++){
		int x,y,p;
		cin>> x >> y >> p;
		PocionesNecesarias += p;
		if(maxPos < p) maxPos = p;
		Nodo nuevo = Nodo(-p,i,x,y);
		Gimnasios.push_back(nuevo);		
	}
	if(maxPos > k || m*3 < PocionesNecesarias){
	cout<< -1<<endl;
	return;
	}
	for(int i=n+1; i<= n+m; i++){
		int x,y;
		cin>> x >> y;
		Nodo nuevo= Nodo(3,i,x,y);
		//cout<<"("<<x<<","<<y<<")"<<i<<endl;
		PokeParadas.push_back(nuevo); 
	}
}

void BT(){
	CantBT++;
	//Quiero cortar o en el caso de que ya hay una solucion mejor o cuando ya recorri todos los gimnasios.
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

void BTA(){
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
					BTA();
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
						BTA();
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
					voyA(gim);
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
					voyA(pp);
				}
				PPRecorridas--;
			}
		}				
	}
}

void BTB(){
	CantBT++;
	//Quiero cortar o en el caso de que ya hay una solucion mejor o cuando ya recorri todos los gimnasios.
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
					BTB();
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
						BTB();
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
					voyB(gim);
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
				if(puedoIrPPB(pp)){
					voyB(pp);
				}
				PPRecorridas--;
			}
		}				
	}
}

void BTC(){
	CantBT++;
	//Quiero cortar o en el caso de que ya hay una solucion mejor o cuando ya recorri todos los gimnasios.
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
					BTC();
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
						BTC();
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
					voyC(gim);
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
				if(puedoIrPPC(pp)){
					voyC(pp);
				}
				PPRecorridas--;
			}
		}				
	}
}

void BTAB(){
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
					BTAB();
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
						BTAB();
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
					voyAB(gim);
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
				if(puedoIrPPB(pp)){
					voyAB(pp);
				}
				PPRecorridas--;
			}
		}				
	}
}

void BTAC(){
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
					BTAC();
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
						BTAC();
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
					voyAC(gim);
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
				if(puedoIrPPC(pp)){
					voyAC(pp);
				}
				PPRecorridas--;
			}
		}				
	}
}

void BTBC(){
	CantBT++;
	//Quiero cortar o en el caso de que ya hay una solucion mejor o cuando ya recorri todos los gimnasios.
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
					BTBC();
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
						BTBC();
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
					voyBC(gim);
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
				if(puedoIrPPBC(pp)){
					voyBC(pp);
				}
				PPRecorridas--;
			}
		}				
	}
}

void BTABC(){
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
					BTABC();
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
						BTABC();
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
					voyABC(gim);
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
				if(puedoIrPPBC(pp)){
					voyABC(pp);
				}
				PPRecorridas--;
			}
		}				
	}
}

//aca se fija si ya recorrio esta PP.
bool puedoIrPP( Nodo & p){
	return !p.Recorrido();
}

//Idem puedoIRPP pero con Poda c
bool puedoIrPPC(Nodo & p){
	return !moch.estaLLena() && !p.Recorrido();
}

//IdemPuedoIrPP pero con poda B
bool puedoIrPPB(Nodo & p){
	bool NoConsumoDemas = true;
	int pociones = p.DamePociones();
	int pocionesEnMoch = moch.DamePeso();
	moch.usarMochila(pociones);
	int MochilaPost = moch.DamePeso();
	moch.Restaurar(pocionesEnMoch);
	int PPRestantes = PokeParadas.size() - PPRecorridas;
	if(MochilaPost + (3*PPRestantes) < PocionesNecesarias) NoConsumoDemas = false;
	return (p.Recorrido() == false) && NoConsumoDemas;

}

//Idem PuedoIrPP pero con poda B y C
bool puedoIrPPBC(Nodo & p){
	bool NoConsumoDemas = true;
	int pociones = p.DamePociones();
	int pocionesEnMoch = moch.DamePeso();
	moch.usarMochila(pociones);
	int MochilaPost = moch.DamePeso();
	moch.Restaurar(pocionesEnMoch);
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

void voyA(Nodo & p) {
	p.Recorrer(true);
	Nodo origen = BuscarNodo(RecorridoActual.back());
	double dist = origen.Distancia(p);
	MinActual += dist;
	RecorridoActual.push_back(p.DameIndice());
	int pociones = p.DamePociones();
	int pocionesEnMoch = moch.DamePeso();
	moch.usarMochila(pociones);
	BTA();
	MinActual -= dist;
	RecorridoActual.pop_back();
	p.Recorrer(false);
	moch.Restaurar(pocionesEnMoch);
}

void voyB(Nodo & p) {
	p.Recorrer(true);
	Nodo origen = BuscarNodo(RecorridoActual.back());
	double dist = origen.Distancia(p);
	MinActual += dist;
	RecorridoActual.push_back(p.DameIndice());
	int pociones = p.DamePociones();
	int pocionesEnMoch = moch.DamePeso();
	moch.usarMochila(pociones);
	BTB();
	MinActual -= dist;
	RecorridoActual.pop_back();
	p.Recorrer(false);
	moch.Restaurar(pocionesEnMoch);
}

void voyC(Nodo & p) {
	p.Recorrer(true);
	Nodo origen = BuscarNodo(RecorridoActual.back());
	double dist = origen.Distancia(p);
	MinActual += dist;
	RecorridoActual.push_back(p.DameIndice());
	int pociones = p.DamePociones();
	int pocionesEnMoch = moch.DamePeso();
	moch.usarMochila(pociones);
	BTC();
	MinActual -= dist;
	RecorridoActual.pop_back();
	p.Recorrer(false);
	moch.Restaurar(pocionesEnMoch);
}

void voyAB(Nodo & p) {
	p.Recorrer(true);
	Nodo origen = BuscarNodo(RecorridoActual.back());
	double dist = origen.Distancia(p);
	MinActual += dist;
	RecorridoActual.push_back(p.DameIndice());
	int pociones = p.DamePociones();
	int pocionesEnMoch = moch.DamePeso();
	moch.usarMochila(pociones);
	BTAB();
	MinActual -= dist;
	RecorridoActual.pop_back();
	p.Recorrer(false);
	moch.Restaurar(pocionesEnMoch);
}

void voyAC(Nodo & p) {
	p.Recorrer(true);
	Nodo origen = BuscarNodo(RecorridoActual.back());
	double dist = origen.Distancia(p);
	MinActual += dist;
	RecorridoActual.push_back(p.DameIndice());
	int pociones = p.DamePociones();
	int pocionesEnMoch = moch.DamePeso();
	moch.usarMochila(pociones);
	BTAC();
	MinActual -= dist;
	RecorridoActual.pop_back();
	p.Recorrer(false);
	moch.Restaurar(pocionesEnMoch);
}

void voyBC(Nodo & p) {
	p.Recorrer(true);
	Nodo origen = BuscarNodo(RecorridoActual.back());
	double dist = origen.Distancia(p);
	MinActual += dist;
	RecorridoActual.push_back(p.DameIndice());
	int pociones = p.DamePociones();
	int pocionesEnMoch = moch.DamePeso();
	moch.usarMochila(pociones);
	BTBC();
	MinActual -= dist;
	RecorridoActual.pop_back();
	p.Recorrer(false);
	moch.Restaurar(pocionesEnMoch);
}

void voyABC(Nodo & p) {
	p.Recorrer(true);
	Nodo origen = BuscarNodo(RecorridoActual.back());
	double dist = origen.Distancia(p);
	MinActual += dist;
	RecorridoActual.push_back(p.DameIndice());
	int pociones = p.DamePociones();
	int pocionesEnMoch = moch.DamePeso();
	moch.usarMochila(pociones);
	BTABC();
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
