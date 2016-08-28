#include <list>
#include <iostream>
#include <vector>

class Tesoro{
public:
	Tesoro(int p, int t, int v);
	std::string Imprimir();
	int Peso();
	int Valor();
	int Tipo();
private:
	int peso;
	int tipo;
	int valor;
};

class Mochila{
public:
	Mochila();
	Mochila(int p);
	void Agregar(Tesoro o);
	std::string Imprimir();
	int Capacidad();
private:
	int cap;
	std::vector<Tesoro> tes;
};