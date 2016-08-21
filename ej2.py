#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
#from functools import reduce
def terny(n):
	output="";
	balanzaA = [0]
	balanzaB = [0]
	count=0
	while (n>0):
		rem = n%3
		n = int(n/3)
		if rem==1:
			balanzaA.append( 3**count)
		elif rem==2:
			n+=1     	
			balanzaB.append( 3**count)
		count+=1
	#print ("Balanza A:",balanzaA)
	#print ("Balanza B:",balanzaB)
	return (balanzaA,balanzaB)
n=15
tam = n**n
for i in range(1,10**15):
	(balanzaA,balanzaB) =terny(i)
	#if (i != ((reduce(lambda x,y: x+y,balanzaA) - reduce(lambda x,y: x+y,balanzaB)))):
		#print ("ERROR, NO PUDO HACER"+str(i))
		#quit()
#	sys.stdout.write("\r   "+str(i)+"/"+str(tam))
#	sys.stdout.flush()
#(balanzaA,balanzaB) =terny(int(sys.argv[1]))
#print(reduce(lambda x,y: x+y,balanzaA) - reduce(lambda x,y: x+y,balanzaB))
