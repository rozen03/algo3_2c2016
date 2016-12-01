#!/usr/bin/python3
# -*- coding: utf-8 -*-
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
#puntos = {1:{},2:{},3:{},4:{}}
puntos = {1:{},2:{},3:{},4:{},5:{},6:{}}
trash = f.readline()
valores =[]
for i in f:
    #cosas= list(map(int,i.split("&")))
    cosas= list(map(str.strip,i.split("&")))
    pto=int(cosas[0])

    if not  0<pto<5:
        print(pto)
        continue

    nodos = int(cosas[1]) + int(cosas[2])
    puntos[pto][nodos]=cosas[5]
    valores.append(nodos)
valores = set(valores)
out=[]
for i in valores:
    #print(i,end=":   ")
    a = [exodia(lista,i) for lista in puntos.values()]
    a=list(map(str,a))
    out.append((i,a))
out= sorted(out, key=lambda a: a[0])
for a in out:
    print(a[0],"\t\t",str.join("\t,\t",a[1]))
    #print(str.join("\t\t",a))
f.close()
