import numpy as np
import os, sys, io
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

def main(output):
	df = "resultadosRectaPPNec.csv"
	resT = output+"tiempo"
	ej = 1
	#creo el dataset
	tiempo = pd.read_csv(df, sep='&')
	#creo una nueva columna, que va a ser cantidad de nodos(eje x)
	tiempo['i+j'] = tiempo['i ']+tiempo['j ']
	#lo indexo por cantidad de nodos
	tiempo.set_index(tiempo['i+j'],inplace = True)
	#me quedo solo con el punto que quiero
	tiempopt = tiempo[tiempo['pto '] == ej]
	#creo una columna con la funcion basica de la cota teorica
	tiempopt['cota Teorica'] = tiempopt['i ']+tiempopt['j ']
	col = len(tiempopt.columns)
	#se la asigno a un dataset distinto
	cotaTeo = tiempopt['cota Teorica']
	#si la cota tiene una funcion mas complicada aca la pones
	cotaTeo = cotaTeo.apply(np.math.factorial)
	#aca me quedo solo con los tiempos
	solotiempo = tiempopt[list(tiempopt.columns[5:col-2])]
	#me quedo con el promedio, seguro que se podia hacer cosas mas copadas
	promedios = solotiempo.mean(axis=1)
	#ploteo logaritmo, si no comentar y list
	#plt.yscale('log')
	cotaTeo.plot(label="cota Teorica")	
	promedios.plot(label = "Tiempo Promedio")
	plt.ylabel("tiempo de ejecucion(ns)")
	plt.xlabel("cantidad de nodos")
	plt.legend()
	plt.savefig(resT)
	plt.show()

if __name__ == '__main__':
	main(output = sys.argv[-1])
