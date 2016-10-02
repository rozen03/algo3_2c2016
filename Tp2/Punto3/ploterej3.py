#encoding: utf-8

"""modo de uso: python plots.py dataFile1 dataFile2 ... dataFileN outputFile"""

import numpy as np
import os, sys
import matplotlib.pyplot as pplot

def parse(f):
	"""
	Espera un archivo que en cada línea tenga: n t1 & FRUTA & t2
		n es la cantidad de nodos 
		t1 y t2 son los tiempos promedios sobre el algonoopt y el algoopt
		Ignora lo que venga entre los & (aprovechamos esto para imprimir la solución en algún lado)
	Devuelve una lista con una tripla (n, t1, t2) por cada línea.
	"""
	tiempos = []
	for l in f:
		l = l.strip()
		if l :
			#separmos solución de tiempos
			resto = l.split('&')
			#partimos los tiempos por espacios
			ns = resto[0]
			t1s = resto[1]
			t2s = resto[3]
			ns = ns.split()
			t1s = t1s.split()
			t2s = t2s.split()
			#parseamos el n del caso
			n = int(ns[0])
			#convertimos a int los tiempos
			t1 = int(t1s[0])
			t2 = int(t2s[0])
			tiempos.append((n, t1, t2))
	return tiempos

def main(output, show=False, labels=None):
	labels = [u"Sin interrupciones", u"Con Interrupciones", u"200*N²"] #si no me pasaste labels, ploteo con nombre de archivo
	text = open("Kn.txt")
	#para cada archivo, vamos a plotear sus datos como una serie diferente
	Xs, Ys3, Ys2, Ys1 =[], [], [], []
	#abrimos el archivo de datos con with...: para que no quede abierto innecesariamente
	#lo abrimos para lectura (no pasamos argumentos extra a open)
	tiempos = parse(text)
	text.close()
	#print tiempos
	ns, n2, ts1, ts2 =[], [], [], []
	for (n, t1, t2) in tiempos:
		n2.append(n*n*200)		
		ns.append(n)
		ts1.append(t1)
		ts2.append(t2)

		#guardamos una COPIA de ns y ts para plotear
	Xs.append(list(ns))
	Ys1.append(list(ts1))
	Ys2.append(list(ts2))
	Ys3.append(list(n2))		
	plot = myPlot(Xs, Ys1, Ys2, Ys3, 
		labels=labels,
		xlabel= u"Cantidad de Nodos", 	#rotulamos los ejes
		ylabel=u"TIempo de ejecución (ns)", 	#empezamos los stings con u" para que use unicode y podamos poner ó, ñ...	
		title = u"Tiempo de ejecución Para distintos Kn",		#ponemos título!
		plotter = pplot, 		#usamos el pplot
		ylog = False				
		)
	# plot = plotNBars(Xs, Ys, 
	# 	labels=dataFiles, 
	# 	xlabel= u"Tamaño del lado del tablero",
	# 	ylabel=u"TIempo de ejecución (ns)",
	# 	title = u"Tiempo de ejecución para distintos tamaños de tablero",
	# 	plotter = pplot,
	# 	ylog = True
	# 	)

	plot.savefig(output)
	if show:
		plot.show()

def myPlot(Xs, Ys1, Ys2, Ys3, labels, xlabel, ylabel, title, plotter, ylog=False):
	"""Plotea una curva para cada x, y, tomándolos en orden de Xs e Ys"""
	l2 = labels[1]
	l1 = labels[0]
	l3 = labels[2]
	for (x, y1, y2, y3) in zip(Xs, Ys1, Ys2, Ys3):
		if ylog:
			plotter.yscale('log')
		plotter.plot(x, y2,label = l2, marker ='^', linestyle = '-.') 
		plotter.plot(x, y1,label = l1, marker='o', linestyle = ':')
		plotter.plot(x, y3,label = l3, linestyle = '-')
		plotter.xlabel(xlabel)
		plotter.ylabel(ylabel)
		plotter.title(title)
		plotter.legend(bbox_to_anchor=(0.,0.75,0.5, 1.), loc=3,
           ncol=1, mode="expand", borderaxespad=0.5)
	return plotter

def plotNBars(Xs, Ys, labels, xlabel, ylabel, title, plotter, ylog = False, horizontalLine = None, verticalLine = None):
	"""Como myPlot, pero en vez de curvas, barras."""
	import numpy.numarray as na
	maxData = max(map(len, Xs))
	minVal = min(map(min, Xs))
	xlocations = na.array(range(maxData))
	width = 0.7
	i = 0
	colores = ['b','g','r','c','m','y','k','w','#610b0b']
	bar_width = float(width/len(Xs))
	for (x, y, l) in zip(Xs, Ys, labels):
		plotter.bar(map(lambda t: t+bar_width*i, x), y, bar_width, label= l, color = colores[i], log=ylog)
		i += 1

	plotter.ylabel(ylabel)
	plotter.xlabel(xlabel)
	plotter.title(title)
	if horizontalLine:
		hline = plotter.axhline(linewidth=2, color='r', y = horizontalLine, linestyle='dashed') 
		bars.append(hline)
	if verticalLine:
		plotter.axvline(linewidth=2, color='r', x = verticalLine) 
	plotter.legend()
	plotter.xticks(xlocations+width/2+minVal, xlocations+minVal, fontsize = 12) #, rotation = 30
	
	return plotter


if __name__ == '__main__':
	main( output = sys.argv[-1], show = True)
