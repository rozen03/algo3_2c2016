#include "dsu.h"
#include <vector>


void init(int n){
	for(i=0; i<n ;i++){
		alturas[i]=1;
		padres[i]=i;
	}
}


	
int find(int x){
	int res;
	
	while(padres[x] != x){
		x= padres[x];
		res = find(padres[x]);
	}
  	return res;
}

void unir(int x, int y){
	


}
