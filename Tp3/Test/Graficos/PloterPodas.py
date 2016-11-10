import numpy as np
import os, sys, io
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns
import random

def main(output, show=False, labels = None):
	labels = []
	
	df ="podasRectaSinMoch.csv"
	podas = pd.read_csv(df, sep ='&')
	podas['i+j'] = podas['i ']+podas['j ']
	indice = pd.DataFrame(data = podas, columns=['i+j'])
	print podas['i+j']
	soloBt = pd.DataFrame(data=podas,index = indice,columns=['SP ','A ','B ','C ','AB ','AC ','BC ', 'ABC '])
	
	print podas
	print "ola"
	print soloBt
	print "asd"
	print podas
	print "bla"
	soloBt.plot(kind='bar')
	plt.show()	
	plt.hist(podas['i '] + podas['j '])
	plt.show()
	
	

if __name__ == '__main__':
	main(output = sys.argv[-1],show = True)
