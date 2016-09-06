#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream> // std::ostringstream
#include <stdlib.h>
#include <string>
#include <tuple>
#include <vector>
#include <list>

using namespace std;



std::list<int> canibalesAntesPuente ;
std::list<int> arqueologosAntesPuente = {1,7,9};


int backtracking(std::list<int> cAntes, int cDespues, std::list<int> aAntes, int aDespues){

    std::list<int> resultado;
	int aux;
	int masLento;
    if((cAntes.size()>aAntes.size() && aAntes.size()!=0) || ((cDespues > aDespues) && aDespues!=0 )){//Hay mas canibales que arqueologos en algun lado del puente
        return -1;
    }

    if(cAntes.size()+aAntes.size()==0){//pasaron todas las personas
        return 0;
    }

    if (cAntes.size()>=2){ //es posible pasar dos canibales
        
        if(cDespues+2>aDespues && aDespues!=0){ //pasar dos canibales genera problemas
            resultado.push_front(-1);
        }
        else{
        	aux = cAntes.back() + cAntes.front();
        	masLento = cAntes.back();
        	cAntes.pop_back();
            resultado.push_front( aux  + backtracking(cAntes, cDespues+1, aAntes , aDespues));
            cAntes.push_back(masLento);
        }
    }

    if( aAntes.size() >= 2 ){//es posible pasar dos arqueologos

        if(cAntes.size()>aAntes.size()-2 || aAntes.size()-2 != 0){
            resultado.push_front(-1);
        }
        else{
        	aux = aAntes.back() + aAntes.front();
        	masLento = aAntes.back();
        	aAntes.pop_back();
            resultado.push_front( aux  + backtracking(cAntes,cDespues,aAntes , aDespues + 1));
        	aAntes.push_back(masLento);
        }
    }

    if(aAntes.size()>=1 && cAntes.size()>=1 ){//es posible pasar uno y uno

        if(cDespues+1>aDespues && aDespues!=0){//vuelve el arqueologo
            resultado.push_front(-1);
        }

        else{
        	aux = cAntes.back() + aAntes.front();
        	masLento = cAntes.back();
        	cAntes.pop_back();
            resultado.push_front(  aux + backtracking( cAntes,cDespues+1,aAntes,aDespues));
        	cAntes.push_back(masLento);
        }

        if(cAntes.size()>aAntes.size()-1 && aAntes.size()-1!=0){//vuelve el canibal
            resultado.push_front(-1);
        }

        else{
        	aux = aAntes.back() + cAntes.front();
        	masLento = aAntes.back();
        	aAntes.pop_back();
            resultado.push_front( aux + backtracking(cAntes,cDespues,aAntes,aDespues+1));
        	aAntes.push_back(masLento);
        }
    }

    resultado.remove(-1);//elimina todos los resultados invalidos

    if(resultado.size()==0){
        return -1;
    }
    else{
    	resultado.sort();
    	return resultado.front();
    }


}




int main(){
		canibalesAntesPuente.sort();
		arqueologosAntesPuente.sort();

		if(canibalesAntesPuente.size()==arqueologosAntesPuente.size() && arqueologosAntesPuente.size()>=3){
			cout<< -1<< endl;
		} 
		else if(canibalesAntesPuente.size()+ arqueologosAntesPuente.size() == 1){
			if(canibalesAntesPuente.size()==1){
				cout << canibalesAntesPuente.front() << endl;
			}
			else{
				cout << arqueologosAntesPuente.front()<< endl;
			}
			//imprimir el unico elemento de las dos listas
		}  
		else{
			cout << backtracking(canibalesAntesPuente,0,arqueologosAntesPuente,0) << endl; 
		}

		return 0;

}
