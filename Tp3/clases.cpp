#include "clases.h"
using namespace std;

// funciones nodo

int Nodo::DameIndice() { return indice; }

Nodo::Nodo(int p, int i, int x, int y)
    : indice(i), pociones(p), X(x), Y(y), Recorri(false){};

Nodo::Nodo( Nodo n, int i){
	indice = i;
	pociones = n.DamePociones();
	X = n.CordenadaX();
	Y = n.CordenadaY();
	Recorri = n.Recorrido();
}

double Nodo::Distancia(Nodo &f) {
  int x = X - f.X;
  int y = Y - f.Y;
  if(x==0 && y==0){
	  return 0.0; //tuve que hacer esto por que parece que  sqrt(0) da NaN y me explota todo
  }
  auto pre = pow(x, 2) + pow(y, 2);
  pre= sqrt(pre);
  if(!isnormal(pre)){
	  return 0.0;
  }else{
	  return pre;
  }
}
void Nodo::asignarCantidadPociones(int p){
    pociones = p;
}
int Nodo::DamePociones() { return pociones; }

bool Nodo::Recorrido() { return Recorri; }

void Nodo::Recorrer(bool b) { Recorri = b; }

bool Nodo::EsGim() { return (pociones != 3); }

int Nodo::CordenadaX() { return X; }

int Nodo::CordenadaY() { return Y; }
// funciones mochila

void Mochila::CambiarCapacidad(int n) { capacidad = n; }

Mochila::Mochila(unsigned int n) : capacidad(n), peso(0){};
Mochila::Mochila() : capacidad(0), peso(0){};

int Mochila::DameCapacidad() { return capacidad; }

int Mochila::DamePeso() { return peso; }

bool Mochila::estaLLena() { return peso == capacidad; }

void Mochila::usarMochila(int n) {
  if (peso + n > capacidad) {
    peso = capacidad;
  } else {
    peso += n;
  }
}

void Mochila::Restaurar(int n){ peso = n; }

// da informacion sobre un vector de nodos
void ImprimirNod(vnod &gim) {
  for (unsigned int i = 0; i < gim.size(); i++) {
    cout << "(" << gim[i].CordenadaX() << "," << gim[i].CordenadaY() << ") {"<<gim[i].DameIndice()<<"} ";
	if(gim[i].Recorrido()){
		cout<<"Recorrido ";
	}
	else{
		cout<<"No Recorrido ";
	}
    if (gim[i].EsGim())
      cout << "[" << -gim[i].DamePociones() << "] ";
  }
  cout << endl;
}

// Lectura de Datos

void Lectura(vnod &gimnasios, vnod &pokeParadas, Mochila &moch) {
  int n, m, k;
  int maxPos = 0;
  int totPos = 0;
  cin >> n >> m >> k;
  moch.CambiarCapacidad(k);
  for (int i = 1; i <= n; i++) {
    int x, y, p;
    cin >> x >> y >> p;
    totPos += p;
    if (maxPos < p)
      maxPos = p;
    Nodo nuevo = Nodo(-p, i, x, y);
    gimnasios.push_back(nuevo);
  }
  if (maxPos > k || m * 3 < totPos) {
    cout << -1 << endl;
    return;
  }
  for (int i = n + 1; i <= n + m; i++) {
    int x, y;
    cin >> x >> y;
    Nodo nuevo = Nodo(3, i, x, y);
    pokeParadas.push_back(nuevo);
  }
}
