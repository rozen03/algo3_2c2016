#! /bin/bash

rm test
g++ test.cpp -fstack-protector-all -g -std=c++11 -O3 -Ofast -o test
#g++ test.cpp -g -std=c++11  -o test
#cat test.txt |
./test >mediciones.txt
