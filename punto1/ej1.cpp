#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream> // std::ostringstream
#include <stdlib.h>
#include <string>
#include <tuple>
#include <vector>
using namespace std;



<int> canibalesAntesPuente;
<int> arqueologosAntesPuente;


int backtracking(<int> cAntes, int cDespues, <int> aAntes, int aDespues){
	<int> resultado = [];

	if((cAntes.size()>aAntes.size() && aAntes.size()!=0) || ((cDespues > aDespues) && aDespues!=0 )){//Hay mas canibales que arqueologos en algun lado del puente
		return -1
	}
	
	if(cAntes.size()+aAntes.size()==0){//pasaron todas las personas
		return 0
	}

	if (cAntes.size()>=2){ //es posible pasar dos canibales
		
		if(cDespues+2>aDespues && && aDespues!=0){ //pasar dos canibales genera problemas
			resultado.add(-1);
		}
		else{
			resultado.add( cAntes.max() + cAntes.min() + backtracking( cAntes.remove(cAntes.max()), cDespues+1,aAntes,aDespues) );				
		}
	}

	if(aAntes.size()>=2){//es posible pasar dos arqueologos

		if(cAntes.size()>aAntes.size()-2 || aAntes.size()-2 != 0){
			resultado.add(-1);
		}
		else{
			resultado.add( aAntes.max() + aAntes.min() + backtracking(cAntes,cDespues,aAntes.remove(aAntes.max()) , aDespues + 1)));
		}
	}

	if(aAntes.size()>=1 && cAntes.size()>=1 ){//es posible pasar uno y uno

		if(cDespues+1>aDespues && aDespues!=0){//vuelve el arqueologo
			resultado.add(-1);
		}

		else{
			resultado.add( cAntes.max() + aAntes.min() + backtracking( cAntes.remove(cAntes.max()),cDespues+1,aAntes,aDespues))
		}

		if(cAntes.size()>aAntes.size()-1 && aAntes.size()-1!=0){//vuelve el canibal
			resultado.add(-1);
		}

		else{
			resultado.add( aAntes.max() + cAntes.min() + backtracking(cAntes,cDespues,aAntes.remove( aAntes.max() ),aDespues+1)))
		}
	}

	/*
		FALTA ELIMINAR TODAS LOS ELEMENTOS DE RESULTADO QUE SON -1
	*/

	if(resultado.size()==0){
		return -1;
	}
}




int main(){

}