#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
from functools import reduce


	#Aviso: le falta una vuelta a la parte de combinar resultados y calcular el minimo
	
canibalesAntesPuente = [1,2]

arqueologosAntesPuente = [1,2,3]
t=0
def recursivo(cAntes,cDespues,aAntes,aDespues):
	resultados = []
	if((len(cAntes)>len(aAntes) and len(aAntes)!=0) or (len(cDespues)>len(aDespues) and len(aAntes)!=0)): #es imposible.
		return -1#devolver -1 o algo
	if(len(cAntes+aAntes)==0):#estoy en una hoja
		return 0
		
	if(len(cAntes)>=2):#puedo llevar 2 canibales
		if(len(cDespues)+2>len(aDespues) and len(aDespues)!=0):#genero un problema despues del puente
			resultados= resultados + [-1]
		else: #esto aca salta error porque si
			resultados + [(max(cAntes)+min(cAntes) + recursivo(cAntes.remove(max(cAntes)),cDespues+[max(cAntes)],aAntes,aDespues))]
	if(len(aAntes)>=2):#puedo llevar 2 arqueologos
		if(len(cAntes)>len(aAntes)-2 and len(aAntes)!=0):
			resultados = resultados + [-1]
		else:
			resultados + [max(aAntes)+min(aAntes) + recursivo(cAntes,cDespues,aAntes.remove(max(aAntes)),aDespues+[max(aAntes)])]
			
	if(len(aAntes)>=1 and len(aDespues)>=1):#puedo llevar uno de cada uno
		if(len(cDespues)+1>len(aDespues) and len(aDespues) !=0):
			resultados = resultados + [-1]
		else:
			resultados + [max(cAntes)+min(aAntes) + recursivo(cAntes.remove(max(cAntes)),cDespues + [max(cAntes)], aAntes, aDespues)] 
		
		if(len(cAntes)>len(aAntes)-1 and len(aAntes) !=0):
			resultados = resultados + [-1]
		else:
			resultados + [max(aAntes) + min(cAntes) + recursivo(cAntes,cDespues, aAntes.remove(max(cAntes)), aDespues+[max(cAntes)])]

	i=0
	while(i<len(resultados)):#elimino todas las ramas que no llevan a nada
		if resultados[i]==0:
			del resultados[i]
		else:
			i= i+1
	if (resultados == []):
		return -1
	else:
		return min(resultados)

#main

if((len(canibalesAntesPuente)== len(arqueologosAntesPuente)) and (len(canibalesAntesPuente) >= 3)):
	print -1
	
elif( len(canibalesAntesPuente+arqueologosAntesPuente)== 1):
	print min(canibalesAntesPuente+arqueologosAntesPuente) #si hay un solo integrante devolves la velocidad
else:
	panico0 = []
	panico1 = []
	print recursivo(canibalesAntesPuente,panico0,arqueologosAntesPuente,panico1)




#~ def puente(c,a):
	#~ 
	#~ 
	#~ if (len(a+c)==1): #hay un solo integrante. Pasa y listo
		#~ return sum(a+c)
	#~ elif (len(a)==0 or len(c)==0 or len(c)==1): 
		#~ return sum(c+a)+min(c+a)*(len(c+a) -3)
	#~ elif (len(c)> len(a) or (len(c)==3 and len(a)==3) ):#son todos los casos que no se puede. el primer caso es trivial, el segundo hay que demostrarlo.
		#~ return -1
	#~ elif (len(a)==2): #por descarte len(c)==2
		#~ if ( min(c+a) in a):
			#~ return sum(c+a)+min(c+a)
		#~ else:
			#~ return sum(c+a)+min(a)
	#~ elif (len(a)==3): #por descarte len(c)==2
		#~ if( min(c+a) in a):
			#~ return sum(c+a)+min(c+a)*2
		#~ else:
			#~ return sum(c+a)+min(c)+min(a)
	#~ elif (len(a)==4):#por descarte len(c)==2
		#~ return sum(c+a)+min(c+a)*(len(c+a) -3)

		

	
	
	
	
	
