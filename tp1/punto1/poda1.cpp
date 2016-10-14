#include <iostream>
#include <chrono>
#include <vector>
#include <set>
#include <tuple>
#include <utility>
#include <limits>

using namespace std;

//Tipos
typedef vector<int> vint;
typedef tuple<vint, vint> ins_;
typedef set<ins_> instancias_set;
typedef vector<ins_> instancias_vector;
typedef instancias_set::iterator itSet;

//Statics
static int MAX = numeric_limits<int>::max();

//variables GLobales
instancias_set mInstanciasSet;
int mMinimoGlobal;
int mMinActual;
vint arqA;
vint arqB;
vint canA;
vint canB;

//Decalracion de funciones
void BT();
void voyConA(int velElem1);
void voyConC(int velElem1);
void vuelvoCon();
bool esValida(ins_ instancia);
int cant(vint v);
int maxNuestro(int, int);
void sacar11();
void sacarArq();
void sacarCan();

//Comienzo Main
int main(){
	//Inicializa minGlobal con lo mas grandeposible
	mMinimoGlobal = MAX;
	int n, m;
	//Lee la entrada
	cin >> n >> m;
	//Si hay mas canivales que arqueologos termina
	if (n < m)
	{
		cout << -1 << endl;
		return 0;
	}

	for (int i = 0; i < n; ++i)
	{
		int arq;
		cin >> arq;
		arqA.push_back(arq);
	}

	for (int i = 0; i < m; ++i)
	{
		int can;
		cin >> can;
		canA.push_back(can);
	}

	//Inicializa el otro lado del puente con todos "vacios"
	for (int i = 0; i < arqA.size(); ++i)
	{
		arqB.push_back(0);
	}

	for (int i = 0; i < canA.size(); ++i)
	{
		canB.push_back(0);
	}
	//Agrega la instancia inicial al set de instancias, esta no se saca nunca
	ins_ instanciaA = make_tuple(arqA,canA);
	mInstanciasSet.insert(instanciaA);
	//Se corre el BT
	BT();
	cout<< mMinimoGlobal <<endl;
	return 0;
}
//Fin Main

void BT() {

	//Si llega una isntancia invalidad la descartamos
	//Si ya nos pasamos del minimo actual cortamos, no nos interesa (Poda)
	ins_ instanciaA = make_tuple(arqA,canA);
	ins_ inatanciaB = make_tuple(arqB,canB);
	if (!esValida(instanciaA) || !esValida(inatanciaB)  ||mMinActual >= mMinimoGlobal){
		return;
	}

 	//Por cada arqueologo que esta del lado inicial del puente lo hacemos cruzar con todos los arq y can que estan con el/ella
	for (size_t i = 0; i < arqA.size(); i++) {
	    int valElem = arqA[i];
	   	if (valElem > 0)
	   	{
		   	arqA[i] = 0;
		    arqB[i] = valElem;
		    voyConA(valElem);
		    voyConC(valElem);
		    arqB[i] = 0;
		    arqA[i] = valElem;
	   	}
	}
	//Por cada canival del lado inicial del puente lo hacemos cruzar con todo canival de su lado (es la unica combinacion que falta)
	for (size_t i = 0; i < canA.size(); i++) {

	  	int valElem = canA[i];
	  	if (valElem > 0)
	  	{
		  	canA[i] = 0;
		    canB[i] = valElem;
		    voyConC(valElem);
		   // voyConA(valElem);
		    canB[i] = 0;
		    canA[i] = valElem;
	  	}

	}

}


//Hace que efectivamente cruce un segundo Arq y suma al tiempo el maximo entre ambos arq
void voyConA(int velElem1) {

	for (int i = 0; i < arqA.size(); ++i)
	{

		if (arqA[i] > 0)
		{
			int valElem = arqA[i];
			int maximo = maxNuestro(valElem, velElem1);
			mMinActual += maximo;
			arqB[i] = valElem;
			arqA[i] = 0;
			vuelvoCon();
			mMinActual -= maximo;
			arqA[i] = valElem;
			arqB[i] = 0;

		}
	}
}

//Hace que efectivamente cruce un segundo can o un can con un arq y suma al tiempo el maximo entre ambos
void voyConC(int velElem1) {

	for (int i = 0; i < canA.size(); ++i)
	{

		if (canA[i] > 0)
		{
			int valElem = canA[i];
			int maximo = maxNuestro(valElem, velElem1);
			mMinActual += maximo;
			canB[i] = valElem;
			canA[i] = 0;
			vuelvoCon();
			mMinActual -= maximo;
			canA[i] = valElem;
			canB[i] = 0;
		}
	}
}


void vuelvoCon() {

	//Si llega una isntancia invalidad la descartamos
	ins_ instanciaA = make_tuple(arqA,canA);
	ins_ inatanciaB = make_tuple(arqB,canB);

	if (!esValida(instanciaA) || !esValida(inatanciaB)) {
		return;
	}
	//Si ya cruzaron todos nos fijamos si el min obtenido es mejor que el global
	if (cant(arqB) == arqB.size() && cant(canB) == canB.size())
	{
		if (mMinActual < mMinimoGlobal )
		{
			mMinimoGlobal = mMinActual;
		}
		return;
	}

	if (cant(arqA)==cant(canA) && cant(arqB)==cant(canB)&& cant(arqB)!=1)
	{
		sacar11();

	}
	else{
		//esto implica cant(arqB)>cant(canB)
		if(cant(arqA)==cant(canA)){
			sacar11();
			sacarArq();
		}
		else{
			//cant(arqA)>cant(canA)
			if (cant(arqB)==cant(canB))
			{
				sacarCan();
				sacar11();
			}
			else{
				sacar11();
				sacarCan();
				sacarArq();
			}
		}

	}


}


//Checquea que una isntancia es valida (una isntancia es  un solo lado del puente)
bool esValida(ins_ instancia) {

	return ((cant(get<0>(instancia)) >= cant(get<1>(instancia))) || cant(get<0>(instancia)) == 0);
}

//Deveuelve la cantidad de valores no 0s (la cantidad de gente que realmente hay de ese lado del puente)
int cant(vint v) {
	int res = 0;
	for (int i = 0; i < v.size(); ++i)
	{
		if (v[i] != 0)
		{
			res++;
		}
	}
	return res;
}

//Max entre 2 valores
int maxNuestro(int a, int b){
	if (a <= b)
	{
		return b;
	}
	return a;
}





void sacar11(){
	//Hacemos que vuelvan 2, 1 arq y 1 can, agregando el maximo de los dos tiempos al total
	//Solo se prueba con uno y uno porq volver con 2 y 0 es inutil

	for (int i = 0; i < arqB.size(); ++i)
	{
		int valElemArq = arqB[i];
		if (valElemArq > 0)
		{
			arqA[i]=valElemArq;
			arqB[i]=0;
			for (int j = 0; j < canB.size(); ++j)
			{
				int valElemCan = canB[j];
				if (valElemCan > 0)
				{
					canA[j] = valElemCan;
					canB[j] = 0;
					ins_ instanciaA = make_tuple(arqA, canA);
					itSet finder = mInstanciasSet.find(instanciaA);
					if (finder == mInstanciasSet.end())
					{
						int maximo = maxNuestro(valElemArq,valElemCan);
						mMinActual += maximo;
						pair<itSet, bool> reference = mInstanciasSet.insert(instanciaA);
						BT();
						mInstanciasSet.erase(reference.first);
						mMinActual -= maximo;

					}
					canB[j] = valElemCan;
					canA[j] = 0;
				}
			}
			arqB[i] = valElemArq;
			arqA[i] = 0;
		}
	}
}



void sacarArq(){
	//Hacemos que vuelvan todos los arq que se puedan
	for (int i = 0; i < arqB.size(); ++i)
	{
		if (arqB[i] > 0)
		{
			int valElem=arqB[i];
			arqA[i]=valElem;
			arqB[i]=0;
			//se Chequea que no se repitan instancias
			ins_ instancia = make_tuple(arqA, canA);
			itSet finder = mInstanciasSet.find(instancia);
			if (finder == mInstanciasSet.end())
			{
				//Si la isntancia no se repite, se agrega el tiempo de la vuelta y se agrega la nueva instancia al set
				mMinActual += valElem;
				pair<itSet, bool> reference = mInstanciasSet.insert(instancia);
				BT();
				mInstanciasSet.erase(reference.first);
				mMinActual -= valElem;
			}
			arqB[i] = valElem;
			arqA[i] = 0;
		}
	}
}


void sacarCan(){

	//Hacemos que vuevlan todos los canivales de la misma forma
	for (int i = 0; i < canB.size(); ++i)
	{
		if (canB[i] > 0)
		{
			int valElem = canB[i];
			canA[i] = valElem;
			canB[i] = 0;
			ins_ instancia = make_tuple(arqA, canA);
			itSet finder = mInstanciasSet.find(instancia);
			if (finder == mInstanciasSet.end())
			{
				mMinActual += valElem;
				pair<itSet,bool> reference = mInstanciasSet.insert(instancia);
				BT();
				mInstanciasSet.erase(reference.first);
				mMinActual -= valElem;
			}
			canB[i] = valElem;
			canA[i] = 0;
		}
	}
}
