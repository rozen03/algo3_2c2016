#!/bin/bash
reset

#rm ej3b
#rm ej3
#g++ ej3b.cpp -fstack-protector-all -g -std=c++11 -O3 -Ofast -fpermissive -o ej3b
#g++ ej3.cpp -fstack-protector-all -g -std=c++11 -O3 -Ofast -fpermissive -o ej3
#g++ -c ej3.cpp -fstack-protector-all -g -std=c++11 -O3 -Ofast -fpermissive
g++ -c ej3.cpp -fstack-protector-all -g -std=c++11 -O3 -Ofast -fpermissive
g++ -c ej3b.cpp -fstack-protector-all -g -std=c++11 -O3 -Ofast -fpermissive
g++ -c ../clases.cpp -fstack-protector-all -g -std=c++11 -O3 -Ofast -fpermissive
g++ -c ej3_common.cpp -fstack-protector-all -g -std=c++11 -O3 -Ofast -fpermissive
g++ comp.cpp ej3.o ej3b.o ej3_common.o clases.o -fstack-protector-all -g -std=c++11 -O3 -Ofast -fpermissive -o comp
