#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
from functools import reduce


	#Aviso: le falta una vuelta a la parte de combinar resultados y calcular el minimo
	
canibalesAntesPuente
canibalesDespuesPuente
arqueologosAntesPuente
arqueologosDespuesPuente
t=0
dosCanibales
dosArqueologos
vuelveCanibal
vuelveArqueologo

def recursivo(cAntes,cDespues,aAntes,aDespues):
	if((len(cAntes)>len(aAntes) and len(aAntes)!=0) or (len(cDespues)>len(aDespues) and len(aAntes)!=0)): #es imposible.
		return -1#devolver -1 o algo
	if(len(cAntes+aAntes)==0):#estoy en una hoja
		return 0
		
	if(len(cAntes)>=2):#puedo llevar 2 canibales
		if(len(cDespues)+2>len(aDespues) and len(aDespues)!=0):#genero un problema despues del puente
			dosCanibales=-1
		else:
		
			dosCanibales=max(cAntes)+min(cAntes) + recursivo(cAntes-max(cAntes),cDespues+max(cAntes),aAntes,aDespues)
			
	if(len(aAntes)>=2):#puedo llevar 2 arqueologos
		if(len(cAntes)>len(aAntes)-2 and len(aAntes)!=0):
			dosArqueologos=-1
		else:
			dosArqueologos=max(aAntes)+min(aAntes) + recursivo(cAntes,cDespues,aAntes-max(aAntes),aDespues+max(aAntes))
			
	if(len(aAntes)>=1 and len(aDespues)>=1):#puedo llevar uno de cada uno
		if(len(cDespues)+1>len(aDespues) and len(aDespues) !=0):
			vuelveArqueologo=-1
		else:
			vuelveArqueologo = max(cAntes)+min(aAntes) + recursivo(cAntes-max(cAntes),cDespues + max(cAntes), aAntes, aDespues) 
		
		if(len(cAntes)>len(aAntes-1) and len(aAntes) !=0):
			vuelveCanibal =-1
		else:
			vuelveCanibal = max(aAntes) + min(cAntes) + recursivo(cAntes,cDespues, aAntes-max(cAntes), aDespues+max(cAntes))


vuelveArqueologo
vuelveCanibal

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

		

	
	
	
	
	
