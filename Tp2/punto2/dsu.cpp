#include "dsu.h"
#include <vector>
#include<iostream> 

void dsu::init(unsigned int n){
	cout<<"entre al init"<<endl;
	vector<int> altura(n, 0);
	vector<int> padre(n, 0);
	for(int i=0; i<n ;i++){
		altura[i]=1;
		padre[i]=i;
	}
}



int dsu::find(unsigned int x){
cout<<"entre al find"<< x << endl;
cout<< "el padre de x es" << padre[x]<<endl;
	if(padre[x]!=x){
		cout<< "entre al if del find"<<endl;
		padre[x]=find(padre[x]);
	}
	return padre[x];
}

void dsu::unir(unsigned int x, unsigned int y){
	x=find(x);
	y=find(y);
	if(altura[x]<altura[y]){
		padre[x]=y;
	}
	else{
		padre[y]=x;
	}
	if(altura[x]==altura[y]){
		altura[x]+=1;
	}

}

