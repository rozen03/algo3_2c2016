import numpy as np
import os, sys, io
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

def main(output):
	
	df ="podasRectaPPNec.csv"
	resP =output+"podas"
	resT = output+"tiempo"
	podas = pd.read_csv(df, sep ='&')
	#creo una nueva columna
	podas['i+j'] = podas['i ']+podas['j ']
	#lo indexo por la columna y lo guardo en podas
	podas.set_index(podas['i+j'], inplace = True)
	#me quedo solo con las columnas que representa las llamadas al BT
	soloBt = pd.DataFrame(data=podas,columns=['SP ','A ','B ','C ','AB ','AC ','BC ', 'ABC '])
	
	soloBt.plot(kind='bar')
	plt.ylabel("cantidad de llamadas al backtracking")
	plt.xlabel("cantidad de nodos")
	plt.savefig(resP)
	plt.show()
	
	#Ahora grafico el tiempo separado a los demas
	dt ="resultadosRectaPPNec.csv"
	tiempo = pd.read_csv(dt, sep ='&')
	tiempo['i+j']=tiempo['i ']+tiempo['j ']
	tiempo.set_index(tiempo['i+j'], inplace = True)
	tiempopt1 = tiempo[tiempo['pto '] ==1]
	col = len(tiempopt1.columns)
	#aca filtro solo los tiempo
	solotiempo =tiempopt1[list(tiempopt1.columns[5:col-1])]
	promedios = solotiempo.mean(axis=1)
	promedios.plot(logy=True)
	plt.ylabel("tiempo de ejecucion(ns)")
	plt.xlabel("cantidad de nodos")
	plt.savefig(resT)
	plt.show()
	
	

if __name__ == '__main__':
	main(output = sys.argv[-1],show = True)
