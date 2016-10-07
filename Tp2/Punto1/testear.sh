#! /bin/bash

rm test
#g++ ej1.cpp -fstack-protector-all -g -std=c++11 -O3 -Ofast -o ej1
g++ test.cpp -g -std=c++11  -o test
cat test.txt | ./test
