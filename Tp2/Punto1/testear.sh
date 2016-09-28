#! /bin/bash

rm ej1
#g++ ej1.cpp -fstack-protector-all -g -std=c++11 -O3 -Ofast -o ej1
g++ ej1.cpp -g  -o ej1
cat test.txt | ./ej1
