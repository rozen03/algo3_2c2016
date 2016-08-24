#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
from functools import reduce




def puente(c,a):
	
	
	if (len(a+c)==1): #hay un solo integrante. Pasa y listo
		return sum(a+c)
	elif (len(a)==0 or len(c)==0 or len(c)==1): 
		return sum(c+a)+min(c+a)*(len(c+a) -3)
	elif (len(c)> len(a) or (len(c)==3 and len(a)==3) ):#son todos los casos que no se puede. el primer caso es trivial, el segundo hay que demostrarlo.
		return -1
	elif (len(a)==2): #por descarte len(c)==2
		if ( min(c+a) in a):
			return sum(c+a)+min(c+a)
		else:
			return sum(c+a)+min(a)
	elif (len(a)==3): #por descarte len(c)==2
		if( min(c+a) in a):
			return sum(c+a)+min(c+a)*2
		else:
			return sum(c+a)+min(c)+min(a)
	elif (len(a)==4):#por descarte len(c)==2
		return sum(c+a)+min(c+a)*(len(c+a) -3)

		

a = [3,4]
c = [2,3]

print puente(c,a)
	
	
	
	
	
	
