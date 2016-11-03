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
			t2s = resto[2]
			t3s = resto[3]
			t4s = resto[4]
			t5s = resto[5]
			t6s = resto[6]
			t7s = resto[7]
			t8s = resto[8]			ns = ns.split()
			#t1s = t1s.split()
			#t2s = t2s.split()
			t3s = t3s.split()

			t4s = t4s.split()
			t5s = t5s.split()
			t6s = t6s.split()
			t7s = t7s.split()
			t8s = t8s.split()

			#parseamos el n del caso
			n = int(ns[0])
			#convertimos a int los tiempos
			#t1 = int(t1s[0])
			#t2 = int(t2s[0])
			t3 = int(t3s[0])

			t4 = int(t4s[0])
			t5 = int(t5s[0])
			t6 = int(t6s[0])
			t7 = int(t7s[0])
			t8 = int(t8s[0])
			tiempos.append((n, t1, t2,t3,t4,t5,t6,t7,t8))
	return tiempos

def main(output, show=False, labels=None):
	labels = [ u"N²", u" D = 0",u" D = 0 (Opt)", u"D = 33 ", u"D = 33 (Opt)", u"D = 66 ", u"D = 66 (Opt)", u"D = 100 ", u"D = 100 (Opt)"] #si no me pasaste labels, ploteo con nombre de archivo
	text = open("VariasDensidades2.txt")
	#para cada archivo, vamos a plotear sus datos como una serie diferente
	Xs, Ys9, Ys8, Ys7, Ys6, Ys5, Ys4, Ys3, Ys2, Ys1 =[], [], [], [], [], [], [], [], [], []

	#abrimos el archivo de datos con with...: para que no quede abierto innecesariamente
	#lo abrimos para lectura (no pasamos argumentos extra a open)
	tiempos = parse(text)
	text.close()
	#print tiempos

	ns, n2, ts1, ts2, ts3, ts4, ts5, ts6, ts7, ts8 =[], [], [], [], [], [], [], [], [], [] 
	for (n, t1, t2, t3, t4, t5, t6, t7, t8) in tiempos:
		n2.append((250*n*n)+115000)		

		ns.append(n)
		ts3.append(t3)
	ts4.append(t4)
		ts5.append(t5)
		ts6.append(t6)
		ts7.append(t7)
		ts8.append(t8)
		#guardamos una COPIA de ns y ts para plotear
	Xs.append(list(ns))
	Ys1.append(list(n2))
	Ys2.append(list(ts1))
	Ys3.append(list(ts2))
	Ys4.append(list(ts3))
	Ys5.append(list(ts4))
	Ys6.append(list(ts5))
	Ys7.append(list(ts6))
	Ys8.append(list(ts7))
	Ys9.append(list(ts8))
	plot = myPlot(Xs, Ys1, Ys2, Ys3, Ys4, Ys5, Ys6, Ys7, Ys8, Ys9,

		labels=labels,
		xlabel= u"Cantidad de nodos en el Kn", 	#rotulamos los ejes
		ylabel=u"Tiempo de ejecución (ns)", 	#empezamos los stings con u" para que use unicode y podamos poner ó, ñ...	
		title = u"Tiempo de ejecución para grafos Kn, con el camino más corto es el eje (1,n).",		#ponemos título!
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


def myPlot(Xs, Ys1, Ys2, Ys3, Ys4, Ys5, Ys6, Ys7, Ys8, Ys9 , labels, xlabel, ylabel, title, plotter, ylog=False):
	"""Plotea una curva para cada x, y, tomándolos en orden de Xs e Ys"""
	l0 = labels[0]
	l1 = labels[1]
	l2 = labels[2]
	l3 = labels[3]
	l4 = labels[4]
	l5 = labels[5]
	l6 = labels[6]
	l7 = labels[7]
	l8 = labels[8]
	for (x, y0, y1, y2, y3, y4, y5, y6, y7, y8) in zip(Xs, Ys1, Ys2, Ys3, Ys4, Ys5, Ys6, Ys7, Ys8, Ys9):
		if ylog:
			plotter.yscale('log')
		#plotter.plot(x, y0,label = l0, linestyle = '-')
		plotter.plot(x, y1,label = l1, marker ='^', linestyle = '-.')
		#plotter.plot(x, y2,label = l2, marker ='^', linestyle = '-.') 
		plotter.plot(x, y3,label = l3, marker='o', linestyle = ':') 
		#plotter.plot(x, y4,label = l4, marker='o', linestyle = ':')
		plotter.plot(x, y5,label = l5, marker='1', linestyle = '--')
		#plotter.plot(x, y6,label = l6, marker='1', linestyle = '--')
		plotter.plot(x, y7,label = l7, marker='s', linestyle = '.')
		#plotter.plot(x, y8,label = l8, marker='s', linestyle = '.')

		plotter.xlabel(xlabel)
		plotter.ylabel(ylabel)
		plotter.title(title)
		plotter.legend(bbox_to_anchor=(0.,0.65,0.5, 1.), loc=3,
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
	colores = ['b','r','g','c','m','y','k','w','#610b0b']
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
