#include <tuple>
#include <cmath>
#include "range.hpp"
#include <utility>
#include <string>
#include <iostream>
#include "sys.h"
#include "builtins.h"
#include <vector>
#include <algorithm>
template <typename T1>
auto terny(T1 n) {
auto output = std::string {""};
std::vector<decltype(0)> balanzaA {0};
std::vector<decltype(0)> balanzaB {0};
auto count = 0;
while (n > 0) {
auto rem = n % 3;
auto n = py14::to_int(n / 3);
if(rem == 1) {
balanzaA.push_back(std::pow(3, count));
} else {
if(rem == 2) {
n += 1;
balanzaB.push_back(std::pow(3, count));
}
}
count += 1;
}
return std::make_tuple(balanzaA, balanzaB);
}
auto n = 15;
auto tam = std::pow(n, n);
for(auto i : rangepp::range(1, std::pow(10, 15))) {
std::tie(balanzaA, balanzaB) = terny(i);
}