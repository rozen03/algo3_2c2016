#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream> // std::ostringstream
#include <stdlib.h>
#include <string>
#include <tuple>
#include <vector>
using namespace std;
uint64_t rdtsc() {
  unsigned int lo, hi;
  __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
  return ((uint64_t)hi << 32) | lo;
}

void terny(long n) {
  // std::vector<unsigned long> balanzaA{0};
  // std::vector<unsigned long> balanzaB{0};
  unsigned long count = 1;
  int countador_A = 0;
  int countador_B = 0;
  std::ostringstream oss_A;
  std::ostringstream oss_B;
  while (n > 0) {
    int rem = n % 3;
    n = n / 3;
    if (rem == 1) {

      oss_A << count << " ";
      countador_A++;
    } else {
      if (rem == 2) {
        countador_B++;
        n += 1;
        oss_B << count << " ";
      }
    }
    count *= 3;
  }
}
int main() {
  int n = 15;
  unsigned long tam = std::pow(10, 15);
  int repeticiones = 30000;
  std::ostringstream oss;
  for (unsigned long i = 1; i < tam; i = 1 + round(i + i / 100)) {
    uint64_t begin, end, elapsed_secs, elapsed_final;
    elapsed_secs = 0;
    for (int j = 0; j < repeticiones; j++) {
      begin = rdtsc();
      terny(i);
      end = rdtsc();
      elapsed_secs += end - begin;
    }
    // std::cout << i << std::endl;
    elapsed_final = elapsed_secs / repeticiones;
    oss << i << "    " << elapsed_final << endl;
    // std::cout << i << endl;
  }
  cout << oss.str() << endl;
}
