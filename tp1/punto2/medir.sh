#! /bin/bash

#rm ej2 ej2_best ej2_medium ej2_wurst mediciones.txt medi_best.txt medi_medium.txt medi_wurst.txt
rm ej2 ej2_best ej2_medium  medi_best.txt medi_medium.txt
g++ ej2_best.cpp -fstack-protector-all -g -std=c++11 -O3 -Ofast -o ej2_best
g++ ej2_medium.cpp -fstack-protector-all -g -std=c++11 -O3 -Ofast -o ej2_medium
g++ ej2_wurst.cpp -fstack-protector-all -g -std=c++11 -O3 -Ofast -o ej2_wurst
./ej2_best >medi_best.txt
./ej2_medium > medi_medium.txt
#./ej2_wurst >medi_wurst.txt
