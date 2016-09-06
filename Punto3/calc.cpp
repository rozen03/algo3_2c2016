#include<cmath>
#include "ej3.h"

using namespace std;


vector<vector<int> > listaAdyDiv(int n){
	//vector<int> ps;
	vector<vector<int> > list(n+1);
	for(int i = 1; i <= n; i++){
		for(int j = i; j > 0; j--){
			
			if(i % j == 0)list[i].push_back(j);
			
		}

	}
	for(unsigned int i= 0 ; i<list.size(); i++){
		
		for(unsigned int l = 0; l < list[i].size(); l++){ 
		cout<<list[i][l]<<", ";
		cout<<endl;
	}
}}	


vector<int> Compuestox2(int n, vector<int>& list){//pasas solo los divisores de n por que es compuesto por 2
	vector<vector<int> > todasres;
	for(unsigned int i = 0; i <= list.size() / 2 + 1; i++){
		vector<int> res(2);
		cout<<"list en i tiene "<<list[i]<<endl;
		res[0] =list[i];
		res[1] = n / res[0];
		cout<<"Res parcial tiene ("<<res[0]<<", "<<res[1]<<")"<<endl;
		todasres.push_back(res);
	}
	vector<int> sol = todasres[0];
	for(unsigned int j = 0; j< todasres.size(); j++){
		if(todasres[j][1] != 1){//no quiero una solucion trivial, a no ser que n sea primo
			sol = todasres[j];
		}
	}
	return sol;
}

vector<int> Compuestox3(int n, vector<vector<int> >& list){
	vector<vector<int> > todasres;
	vector<int> divn = list[n-1];
	for(unsigned int i = 0; i<divn.size(); i++){
		vector<int> respar(3);
		int med = n / i;
		vector<int> comp2 = Compuestox2(med, list[med-1]);
		respar.push_back(i);
		respar.push_back(comp2[0]);
		respar.push_back(comp2[1]);
		todasres.push_back(respar);
	}
	vector<vector<int> > algunasres;
	algunasres.push_back(todasres[0]);
	for(unsigned int j = 0; j <todasres.size();j++){
		if(todasres[j][1] != 1) algunasres.push_back(todasres[j]);
	}
	vector<int> sol = algunasres[0];
	for(unsigned int i = 0; i<algunasres.size(); i++){
		if(algunasres[i][2] != 1){
			sol = algunasres[i];
			break;
		}
	}
	return sol;
}

int main(int argc, char const *argv[]){
	vector<vector<int> > list;
	list = listaAdyDiv( 20);
	cout<<"termino lista, la lista en la posicion 19 tiene"<<endl;
	for(unsigned int i = 0; i< list[19].size(); i++){
		cout<<list[19][i]<<", ";
	}cout<<endl;
	vector<int> s = Compuestox2(20, list[19]);
	
	
	cout<<"termino compuesto, el tamaño es "<<s.size()<<endl;
	for(unsigned int i = 0; i< s.size(); i++){
		cout<< s[i]<< ", ";
	}
	cout<<endl;
}
