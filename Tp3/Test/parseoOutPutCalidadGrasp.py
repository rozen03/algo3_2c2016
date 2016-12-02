#!/usr/bin/python3
# -*- coding: utf-8 -*-
def switchear(cosa):
    if(cosa=="a"):
        return "b"
    else:
        return "a"
import argparse
parser = argparse.ArgumentParser()
parser.add_argument('Archivo', metavar="Archivo", type=str)
#print(parser.parse_args().Archivo)
def exodia(lista,i):
    try:
        return lista[i]
    except:
        return "0"
try:
    f = open(parser.parse_args().Archivo)
except:
    print("No se pudo abrir "+ parser.parse_args().Archivo)
    quit()
trash = f.readline()
cosa ="b"


nodos={"a":[],"b":[]}

for i in f:
    cosa = switchear(cosa)
    linea =[i for i in map(str.strip,i.split("&")) if i ]
    cantidadDeNodos = len(linea[1].split(" "))
    #nodos[cosa][cantidadDeNodos] = []
    res = [i for i in linea if " " not in i]
    for i in res:
        nodos[cosa].append(str(cantidadDeNodos)+"\t,\t"+i)

for i in range(min(len(nodos["a"]),len(nodos["b"]))):
    print(nodos["a"][i]+"\t,\t"+nodos["b"][i])
    #promedio = sum(res)/len(res)
    #print(res)
    #print(cosa, nodos, nodos, sep="\t,\t")

#for i in nodos["a"].keys():
#    for j in range(len(nodos["a"][i])):
#        print(nodos["a"][i][j],nodos["b"][i][j])
#print(nodos)
