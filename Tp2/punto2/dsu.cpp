#include "dsu.h"
#include <vector>


void init(int n){
	for(i=0; i<n ;i++){
		altura[i]=1;
		padre[i]=i;
	}
}



int find(int x){
	if(padre[x]!=x){
		padre[x]=find(padre[x]);
	}
	return padre[x];
}

void unir(int x, int y){
	x=find(x);
	y=ind(y);
	if(altura[x]<altura[y]){
		padre[x]=y;
	}
	else{
		padre[y]=x;
	}
	if(altura[x]=altura[y]){
		altura[x]+=1;
	}

}
