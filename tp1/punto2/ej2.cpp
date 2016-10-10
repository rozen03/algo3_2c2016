#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream> // std::ostringstream
#include <stdlib.h>
#include <string>
using namespace std;
uint64_t rdtsc() {
  unsigned int lo, hi;
  __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
  return ((uint64_t)hi << 32) | lo;
}

void imprimirBalanza(list<unsigned long> balanza) {
  while (!balanza.empty()) {
    std::cout << balanza.front();
    balanza.pop_front();
    if (!balanza.empty()) {
      std::cout << ' ';
    }
  }
  cout << endl;
}

void terny(long n) {
  unsigned long count = 1;
  int countador_A = 0;
  int countador_B = 0;
  list<unsigned long> balanzaA, balanzaB;
  while (n > 0) {
    int rem = n % 3;
    n = n / 3;
    if (rem == 1) {
      balanzaA.push_back(count);
      countador_A++;
    } else {
      if (rem == 2) {
        countador_B++;
        n += 1;
        balanzaB.push_back(count);
      }
    }
    count *= 3;
  }
  imprimirBalanza(balanzaA);
  imprimirBalanza(balanzaB);
}
int main() {
  int n;
  std::ostringstream oss;
  cin >> n;
  terny(n);
  cout << oss.str() << endl;
}
