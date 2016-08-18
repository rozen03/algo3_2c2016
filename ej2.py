#!/usr/bin/env python2
# -*- coding: utf-8 -*-


def terny(n):
    output="";
    balanzaA = []
    balanzaB = []
    count=0
    while (n>0):

        rem = n%3
        n = n/3
        if (rem == 2):
            rem = -1
            n+=1
        sol =('0' if rem==0 else ('+' if rem==1 else '-'))
        output = sol + output;
        if sol =='+':
        	balanzaA.append( 3**count)
        elif sol =='-':
        	balanzaB.append( 3**count)
        count+=1
    print ("Balanza A:",balanzaA)
    print ("Balanza B:",balanzaB)
    return output

res =terny(11)
