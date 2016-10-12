#include<cmath>
#include <tuple>
#include <vector>
using namespace std;

//lista de divisores
vector<vector<int> > listaAdyDiv(int n){
	vector<int> ps;
	vector<vector<int> > list(n+1, ps);
	for(int i = 1; i <= n; i++){
		for(int j = i; j > 0; j--){
			if(i % j == 0) list[i].push_back(j);
		}
	}
	return list;
}	

vector<int> Compuestox2(int n, vector<int>& list){//pasas solo los divisores de n por que es compuesto por 2
	vector<vector<int> > todasres;
	for(unsigned int i = 0; i <list.size(); i++){
		vector<int> res(2);
		res[0] =list[i];
		res[1] = n / res[0];
		todasres.push_back(res);
	}
	int medio = todasres.size()/2;
	return todasres[medio];
}

vector<int> Compuestox3(int n, vector<vector<int> >& list){
	vector<vector<int> > todasres;
	vector<int> divn = list[n];
	for(unsigned int i = 0; i<divn.size(); i++){
		vector<int> respar;
		int div = divn[i];
		int med = n / div;
		vector<int> comp2 = Compuestox2(med, list[med]);
		respar.push_back(div);
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
/*
int main(int argc, char const *argv[]){
	vector<vector<int> > list = listaAdyDiv(27);
	vector<int> s = Compuestox2(19, list[19]);
	vector<int> bla = Compuestox3(6, list);
}
*/
