#include "../clases.h"
#include <iostream>
#include <chrono>
#include <limits>


using namespace std;
/*
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
*/

//declaracion de funciones
void BTSP();
void BTA();
void BTB();
void BTC();
void BTAB();
void BTAC();
void BTBC();
void BTABC();
void voySP(Nodo & p);
void voyA(Nodo & p);
void voyB(Nodo & p);
void voyC(Nodo & p);
void voyAB(Nodo & p);
void voyAC(Nodo & p);
void voyBC(Nodo & p);
void voyABC(Nodo & p);
//bool puedoIrG(Nodo & p);
//bool puedoIrPP(Nodo & p);
bool puedoIrPPA(Nodo & p);
bool puedoIrPPB(Nodo & p);
bool puedoIrPPC(Nodo & p);
bool puedoIrPPAB(Nodo & p);
bool puedoIrPPAC(Nodo & p);
bool puedoIrPPBC(Nodo & p);
bool puedoIrPPABC(Nodo & p);
//Nodo & BuscarNodo(int n);
//int Maximo(int a, int b);
//void Reset(vnod & PP, vnod & G, Mochila mochil);
void CorrerPodas(vnod gim, vnod pp, Mochila mochil, ofstream & podas);
void Imprimir(vint sol, ofstream & podas);
//funciones

void Imprimir(vint sol, ofstream & podas){
	for(int i = 0; i<sol.size(); i++)podas<< sol[i]<<" ";
}

void CorrerPodas(vnod GAux, vnod PPAux, Mochila mochil, ofstream & podas){
	cout<<"Entre a CorrerPodas con "<<PPAux.size()<<" pokeparadas y "<<GAux.size()<<" gimnasios"<<endl;
	cout<<"las copias son en gim ";
	ImprimirNod(GAux);
	cout<<"en pp son ";
	ImprimirNod(PPAux); 
	
	Reset(PPAux, GAux, mochil);
	cout<<"antes de llamar al BT post reset";
	cout<<"post reset los valores son ";
	cout<< CantBT<<" cant, "<< MinGlobal<<" minGlob, "<<MinActual<<" minActual, ";
	cout<< GimRecorridos<<" gimRecc, "<<PPRecorridas<<" PPreco, ";
	cout<<"los Gim y pp "<<endl;
	ImprimirNod(Gimnasios);
	ImprimirNod(PokeParadas);
	
	BTSP();
	int Cbt = CantBT;
	double dist = MinGlobal;
	vint Solbt = RecorridoGlobal;
	
	cout<<"pre reset los valores son ";
	cout<< CantBT<<" cant, "<< MinGlobal<<" minGlob, "<<MinActual<<" minActual, ";
	cout<< GimRecorridos<<" gimRecc, "<<PPRecorridas<<" PPreco, ";
	cout<<"los Gim y pp "<<endl;
	ImprimirNod(Gimnasios);
	ImprimirNod(PokeParadas);
	cout<<"Recorrido BT ";
	for(int i = 0; i<Solbt.size();i++) cout<< Solbt[i]<<" ";
	cout<<endl;
	Reset(PPAux, GAux, mochil);
	BTA();
	int CbtA = CantBT;
	double distA = MinGlobal;
	vint SolbtA = RecorridoGlobal;
	
	Reset(PPAux, GAux, mochil);
	BTB();
	int CbtB = CantBT;
	double distB = MinGlobal;
	vint SolbtB = RecorridoGlobal;
	
	Reset(PPAux, GAux, mochil);
	BTC();
	int CbtC = CantBT;
	double distC = MinGlobal;
	vint SolbtC = RecorridoGlobal;
	
	Reset(PPAux, GAux, mochil);
	BTAB();
	int CbtAB = CantBT;
	double distAB = MinGlobal;
	vint SolbtAB = RecorridoGlobal;
	
	Reset(PPAux, GAux, mochil);
	BTAC();
	int CbtAC = CantBT;
	double distAC = MinGlobal;
	vint SolbtAC = RecorridoGlobal;
	
	Reset(PPAux, GAux, mochil);
	BTBC();
	int CbtBC = CantBT;
	double distBC = MinGlobal;
	vint SolbtBC = RecorridoGlobal;
	
	Reset(PPAux, GAux, mochil);
	BTABC();
	int CbtABC = CantBT;
	double distABC = MinGlobal;
	vint SolbtABC = RecorridoGlobal;
	
	podas<< Cbt<<" & "<<dist<<" & ";
	Imprimir(Solbt, podas);
	podas<<" & "<<CbtA<<" & "<<distA<<" & ";
	Imprimir(SolbtA, podas);
	podas<<" & "<<CbtB<<" & "<<distB<<" & ";
	Imprimir(SolbtB, podas);
	podas<<" & "<<CbtC<<" & "<<distC<<" & ";
	Imprimir(SolbtC, podas);
	podas<<" & "<<CbtAB<<" & "<<distAB<<" & ";
	Imprimir(SolbtAB, podas);
	podas<<" & "<<CbtAC<< " & "<< distAC<<" & ";
	Imprimir(SolbtAC, podas);
	podas<<" & "<<CbtBC<<" & "<<distBC<<" & ";
	Imprimir(SolbtAC, podas);
	podas<<" & "<<CbtABC<<" & "<<distABC<<" & ";
	Imprimir(SolbtABC, podas);
	cout<<"termine correr Podas"<<endl;
	
}


/*
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
*/
void BTSP(){
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
					BTSP();
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
						BTSP();
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
					voySP(gim);
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
					voySP(pp);
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

//Aca se decide ir a un Nodo sin importar si es PP o gimnasio, basicamente se marcan los estados para que el BT funcione bien
void voySP(Nodo & p) {
	p.Recorrer(true);
	Nodo origen = BuscarNodo(RecorridoActual.back());
	double dist = origen.Distancia(p);
	MinActual += dist;
	RecorridoActual.push_back(p.DameIndice());
	int pociones = p.DamePociones();
	int pocionesEnMoch = moch.DamePeso();
	moch.usarMochila(pociones);
	BTSP();
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

