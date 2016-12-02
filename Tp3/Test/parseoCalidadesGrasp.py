#!/usr/bin/python3
# -*- coding: utf-8 -*-
def switchear(cosa):
    if(cosa=="a"):
        return "b"
    else:
        return "a"
import argparse
parser = argparse.ArgumentParser()
nodos={}
results={}
#parser.add_argument('Archivo', metavar="Archivo", type=str)
#print(parser.parse_args().Archivo)
archivos =["resultadosPPNecmeta10.txt","resultadosPPNecmeta30.txt","resultadosPPNecmeta20.txt","resultadosPPNecmeta10U.txt","resultadosPPNecmeta30U.txt","resultadosPPNecmeta20U.txt"]
#archivos =["resultadosRSMmeta10.txt" ,  "resultadosRSMmeta10U.txt" , "resultadosRSMmeta20.txt"  , "resultadosRSMmeta20U.txt",  "resultadosRSMmeta30.txt" , "resultadosRSMmeta30U.txt"]

cantidadFinal=0
for archivo in archivos:
    try:
        f = open(archivo)
    except:
        print("No se pudo abrir "+ archivo)
        quit()
    trash = f.readline()
    cosa ="b"
    line =2
    cantidadDeNodos=1
    for i in f:
        cosa = switchear(cosa)
        linea =[i for i in map(str.strip,i.split("&")) if i ]
        #cantidadDeNodos = len(linea[1].split(" "))
        #if not nodos[cantidadDeNodos]
        try:
            trash =len(nodos[cantidadDeNodos])
        except:
            nodos[cantidadDeNodos] = []
        res = min(int(i) for i in linea if " " not in i)
        nodos[cantidadDeNodos].append((archivo+cosa,res))
        #for i in res:
        #    nodos[cosa].append(str(cantidadDeNodos)+"\t,\t"+i)

        line+=1
        cantidadDeNodos= line//2
        cantidadFinal=cantidadDeNodos
        #for i in range(min(len(nodos["a"]),len(nodos["b"]))):
        #    print(nodos["a"][i]+"\t,\t"+nodos["b"][i])


for i in nodos:
    nodos[i]=sorted(nodos[i], key=lambda bu: bu[1])
    rank=(len(archivos)*2)-1
    #print(nombre,valor)
    for nombre,valor in nodos[i]:
        try:
            trash =results[nombre]
        except:
            results[nombre] = 0
        results[nombre]+=rank
        rank-=1

#print(results)
for i in results:
    print(i,results[i],sep="\t,\t")

#print(nodos)
