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



std::list<int> canibalesAntesPuente;
std::list<int> arqueologosAntesPuente;


int backtracking(std::list<int> cAntes, int cDespues, std::list<int> aAntes, int aDespues){
    std::list<int> resultado = [];

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
            resultado.push_front( cAntes.back() + cAntes.front() + backtracking(cAntes.pop_back(), cDespues+1, aAntes , aDespues));
        }
    }

    if( aAntes.size() >= 2 ){//es posible pasar dos arqueologos

        if(cAntes.size()>aAntes.size()-2 || aAntes.size()-2 != 0){
            resultado.push_front(-1);
        }
        else{
            resultado.push_front( aAntes.back() + aAntes.front() + backtracking(cAntes,cDespues,aAntes.pop_back() , aDespues + 1));
        }
    }

    if(aAntes.size()>=1 && cAntes.size()>=1 ){//es posible pasar uno y uno

        if(cDespues+1>aDespues && aDespues!=0){//vuelve el arqueologo
            resultado.push_front(-1);
        }

        else{
            resultado.push_front( cAntes.back() + aAntes.front() + backtracking( cAntes.pop_back(),cDespues+1,aAntes,aDespues));
        }

        if(cAntes.size()>aAntes.size()-1 && aAntes.size()-1!=0){//vuelve el canibal
            resultado.push_front(-1);
        }

        else{
            resultado.push_front( aAntes.back() + cAntes.front() + backtracking(cAntes,cDespues,aAntes.pop_back() ,aDespues+1);
        }
    }

    resultado.remove(-1);//elimina todos los resultados invalidos

    if(resultado.size()==0){
        return -1;
    }
    else{
        return resultado.min();
    }


}




int main(){
		canibalesAntesPuente.sort();
		arqueologosAntesPuente.sort();

		if(canibalesAntesPuente.size()==arqueologosAntesPuente.size() && arqueologosAntesPuente.size()>=3){
			printf("%d\n", -1 );
		} 
		else if(canibalesAntesPuente.size()+ arqueologosAntesPuente.size() == 1){
			if(canibalesAntesPuente.size()==1){
				printf("%d\n",canibalesAntesPuente.front());
			}
			else{
				printf("%d\n",arqueologosAntesPuente.front());
			}
			//imprimir el unico elemento de las dos listas
		}  
		else{
			printf("%d\n", backtracking(canibalesAntesPuente,0,arqueologosAntesPuente,0)); 
		}

		return 0;

}
