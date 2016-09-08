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
std::list<int> arqueologosAntesPuente ;



int backtracking(std::list<int> cAntes, int cDespues, std::list<int> aAntes, int aDespues){

    std::list<int> resultado;
    int aux;
    int masLento;
    if(cAntes.size()+aAntes.size()==2){//tiene que pasar la última parjea
        int res;
        if(canibalesAntesPuente.size()==2){
             res = canibalesAntesPuente.back();
        }
        else if(arqueologosAntesPuente.size()==2){
            res = arqueologosAntesPuente.back();
        }
        else{
            res = max(arqueologosAntesPuente.back(), canibalesAntesPuente.back());
        }
        return res;
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
        
        if(cAntes.size()>aAntes.size()-2 && aAntes.size()-2 != 0){
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



int max(int a,int b){
    if (a>=b){
        return a;
    }
    else{
        return b;
    }
}

int solucion(list<int>& arq, list<int>& can){
	int res;
	if(canibalesAntesPuente.size()=> 3 && arqueologosAntesPuente.size()>=1){
        res = -1;
    } 
    else if(canibalesAntesPuente.size()+ arqueologosAntesPuente.size() == 1){
        if(canibalesAntesPuente.size()==1){
            res = canibalesAntesPuente.front();
        }
        else{
            res = arqueologosAntesPuente.front();
        }

    }
    else{
        res = backtracking(canibalesAntesPuente,0,arqueologosAntesPuente,0); 
    }
}

int main(){
    int n;
    int m;
    cin >> n >> m;

    int aux;

    for (int i = 0; i < n; ++i){
        cin >> aux;
        arqueologosAntesPuente.push_back(aux);
        }
    for (int i = 0; i < m; ++i){
        cin >> aux;
        canibalesAntesPuente.push_back(aux);
        }
        
    canibalesAntesPuente = {4};
    arqueologosAntesPuente = {5};
    canibalesAntesPuente.sort();
    arqueologosAntesPuente.sort();

	cout<< solucion(arqueologosAntesPuente, canibalesAntesPuente);

    return 0;

}
