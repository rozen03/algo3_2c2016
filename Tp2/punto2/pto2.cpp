#include "dsu"
#include "estructuras.h"

int kruskal(priority_queue<Eje *> ejes, int n){
	unsigned int res=0;
	init(n);
	for(i=0; i< ejes.size(); i++){
		eje e= ejes[i];
		//ver como se llamas los nodos extremos del eje podrian ser inicio y fin?!
		if(find(e.n1()) != find(e.n2())){
			res=+e.peso();
			union(e.n1, e.n2);
		}
	return res;
	}

}


int solu(vector<nodo> nodos){
	int n= nodos.size();
	priority_queue<Eje *> aristas;
	for (int i=0; i<n; i++ ) {
		nodo nod=nodos[i];
		for(int j=0; j< nod.ejes.size(); i++){
			aristas.push(nod.ejes[j]);
		}
	}
	inr res= kruskal(aristas,n);
	return res;
}
