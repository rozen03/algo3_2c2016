all:
	g++ -c ../Punto3/ej3.cpp -fstack-protector-all -g -std=c++11 -O3 -Ofast -fpermissive
	g++ -c ../Punto3/ej3b.cpp -fstack-protector-all -g -std=c++11 -O3 -Ofast -fpermissive
	g++ -c ../clases.cpp -fstack-protector-all -g -std=c++11 -O3 -Ofast -fpermissive
	g++ -c ../Punto3/ej3_common.cpp -fstack-protector-all -g -std=c++11 -O3 -Ofast -fpermissive
	#g++ comp.cpp ej3.o ej3b.o ej3_common.o clases.o -fstack-protector-all -g -std=c++11 -O3 -Ofast -fpermissive -o comp
	g++ test.cpp *.o -fstack-protector-all -g -std=c++11 -O3 -Ofast -fpermissive -o test

clean:
	rm *.o test
