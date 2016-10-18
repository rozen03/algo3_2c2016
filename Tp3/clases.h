#ifndef __NODO__
#define __NODO__


using namespace std;

class Nodo{
public:
	
	

private:
};


class Mochila{
public:
	Mochila(unsigned int n);
	unsigned int DameCapacidad();
	int DamePeso();
	bool estaLLena();
	void usarMochila(int n); 	
	
private:
	unsigned int capacidad;
	int peso;
};



