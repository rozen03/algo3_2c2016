#!/bin/bash
reset
rm test
g++ test.cpp -fstack-protector-all -g -std=c++11 -O3 -Ofast -o test
