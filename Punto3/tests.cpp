#include "ej3.cpp" //ver q onda
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<chrono>

#define ya chrono::high_resolution_clock::now

using namespace std;

int crearCasos(){
srand(time(NULL));

std::ofstream test10obj ("test10obj.txt");

test10obj << "1 20 \n";
test10obj << "20 \n";
int d=0;
for ( int i = 0; i < 20; i++) {
  if (d<10){
    int C=rand()%10+1;
    int p=rand()%100+1;
    int v=rand()%10000000+1;
    d=d+C;
    test10obj<< C<< " "<< p<< " "<<v << endl;
  }
}
test10obj.close();

//main(1,"test10obj.txt");

//sol10obj.close();



std::ofstream test20obj ("test20obj.txt");
test20obj << "1 20 \n";
test20obj << "20 \n";
d=0;
for ( int i = 0; i < 20; i++) {
  if (d<20){
    int C=rand()%20+1;
    int p=rand()%100+1;
    int v=rand()%10000000+1;
    d=d+C;
    test20obj<< C<< " "<< p<< " "<<v << endl;
  }
}
test20obj.close();

std::ofstream test30obj ("test30obj.txt");
test30obj << "1 20 \n";
test30obj << "20 \n";
d=0;
for ( int i = 0; i < 20; i++) {
  if (d<30){
    int C=rand()%30+1;
    int p=rand()%100+1;
    int v=rand()%10000000+1;
    d=d+C;
    test30obj<< C<< " "<< p<< " "<<v << endl;
  }
}

test30obj.close();

std::ofstream test40obj ("test40obj.txt");
test40obj << "1 20 \n";
test40obj << "20 \n";
d=0;
for ( int i = 0; i < 20; i++) {
  if (d<40){
    int C=rand()%40+1;
    int p=rand()%100+1;
    int v=rand()%10000000+1;
    d=d+C;
    test40obj<< C<< " "<< p<< " "<<v << endl;
  }
}

test40obj.close();

std::ofstream test50obj ("test50obj.txt");
test50obj << "1 20 \n";
test50obj << "20 \n";
d=0;
for ( int i = 0; i < 20; i++) {
  if (d<50){
    int C=rand()%50+1;
    int p=rand()%100+1;
    int v=rand()%10000000+1;
    d=d+C;
    test50obj<< C<< " "<< p<< " "<<v << endl;
  }
test50obj.close();
}

return 0;
}
