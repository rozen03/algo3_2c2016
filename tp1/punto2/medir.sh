#! /bin/bash

rm ej2 mediciones.txt
g++ ej2.cpp -fstack-protector-all -g -std=c++11 -O3 -Ofast -o ej2
./ej2 >mediciones.txt
