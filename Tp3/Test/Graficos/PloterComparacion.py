import numpy as np
import os, sys, io
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

def main(output):
	df = "resultadosRectaPPNec.csv"
	#cuando tengamos valores de la meta tenemos que usar esto
	#dm = "resultadosRectaPPNecmeta.csv"
	resT =output+"Tiempos"
	resPreciso = output+"Preciso"
	resParcial = output+"Parcial"
	#creo el dataset
	data = pd.read_csv(df, sep='&')
	#creo una nuea columna, cant nodos
	data['i+j'] = data['i '] +data['j ']
	tiempo = data
	#indexo por cantNod
	tiempo.set_index(tiempo['i+j'], inplace = True)
	#me quedo solo con los tiempos
	col = len(tiempo.columns)
	solotiempo = tiempo[list(tiempo.columns[5:col-1])]
	#agrego al final pto para filtrar luego
	solotiempo['pto '] = tiempo['pto ']
	print solotiempo	
	#no meto al pt1 por que el grafico va a ser una pija
	pt1 = solotiempo[solotiempo['pto '] == 1]
	pt2 = solotiempo[solotiempo['pto '] == 2]
	pt3 = solotiempo[solotiempo['pto '] == 3]
	pt4 = solotiempo[solotiempo['pto '] == 4]
	#me quedo con promedios despues de sacar el 'pto '
	#pt1.drop(['Unnamed: 15', 'pto '],axis=1, inplace = True)
	#pt2.drop(['Unnamed: 15', 'pto '],axis=1, inplace = True)
	#pt3.drop(['Unnamed: 15', 'pto '],axis=1, inplace = True)
	#pt4.drop(['Unnamed: 15', 'pto '],axis=1, inplace = True)
	prom1 = pt1.mean(axis=1)
	prom2 = pt2.mean(axis=1)
	prom3 = pt3.mean(axis=1)
	prom4 = pt4.mean(axis=1)
	#ploteo el grafico
	#plt.yscale('log')
	prom1.plot(label="Bactracking")
	prom2.plot(label ="Golozo")
	prom3.plot(label ="Busqueda Local")
	prom4.plot(label="GRASP")
	plt.ylabel("tiempo de ejecucion(ns)")
	plt.xlabel("cantidad de nodos")
	plt.legend()
	plt.savefig(resT)
	plt.show()
	
	#ahora quiero hacer dos comparaciones, unos contra la solucion en general
	#y otro sobre las comparaciones parciales, estaria bueno saber cual
	#es el que tiene las mejores respuesas en gral
	tam = len(data.columns)
	data.dropna(axis=0,how='any',subset = [list(data.columns[3:tam])], inplace = True)
	tam=len(data.columns)
	data.drop(list(data.columns[5:tam]),axis=1, inplace = True)
	#ahora data no tienee tiempos
	"""
	la idea es separar en dos dataframes uno que tiene todos los 1 y el otro el que no tiene 1
	
	"""
	print data
	print "bala"
	dataux = pd.concat([data.iloc[[3, 4]]], axis= 0, copy=True)
	print dataux

if __name__ == '__main__':
	main(output = sys.argv[-1])
	
	
