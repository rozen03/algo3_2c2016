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



//std::list<int> canibalesAntesPuente ;
//std::list<int> arqueologosAntesPuente ;



int backtracking(std::list<int> cAntes, int cDespues, std::list<int> aAntes, int aDespues){
    std::list<int> resultado;
    int aux;
    int masLento;
    if(cAntes.size()+aAntes.size()==2){//tiene que pasar la última parjea
        int res;
        if(cAntes.size()==2){
             res = cAntes.back();
             cout<< res<<endl;
        }
        else if(aAntes.size()==2){
            res = aAntes.back();
        }
        else{
            res = max(aAntes.back(), cAntes.back());
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

int solucion(list<int>& arqueologosAntesPuente, list<int>& canibalesAntesPuente){
	canibalesAntesPuente.sort();
    arqueologosAntesPuente.sort();
	int res;
	int can =canibalesAntesPuente.size();
	int arq = arqueologosAntesPuente.size();
	if((can >=3  && arq>=1)|| (can>arq && arq != 0)){//2 =2 es un caso que tiene solucion pero 3 3 no, asi que tenemos dos partes de la guarda
        res = -1;
    } 
    else if(can+ arq == 1){
        if(can==1){
            res = canibalesAntesPuente.front();
        }
        else{
            res = arqueologosAntesPuente.front();
        }

    }
    else{
        res = backtracking(canibalesAntesPuente,0,arqueologosAntesPuente,0); 
    }
    return res;
}

void lecturaDatos(string input, list<int>& arq, list<int>& can){
	fstream ip;
	ip.open(input);
	int n;
    int m;
    ip >> n >> m;

    int aux;
	cout<< input<<endl;
    for (int i = 0; i < n; ++i){
        ip >> aux;
        arq.push_back(aux);
        }
    for (int i = 0; i < m; ++i){
        ip >> aux;
        can.push_back(aux);
        }
}

int main(int argc, char *argv[]){
    
    list<int> arq;
    list<int> can;
    string input = argv[1];    
    lecturaDatos(input, arq,can);
	cout<< solucion(arq, can)<<endl;

    return 0;

}

