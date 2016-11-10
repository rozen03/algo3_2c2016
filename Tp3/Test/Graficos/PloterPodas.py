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
	print podas
	podasble = podas.filter(['i ','j ','SP ','A ','B ','C ','AB ','AC ','BC ', 'ABC ']);
	print "ola"
	print podasble
	print "asd"
	print podas
	print "bla"
	print podas['i ']
	plt.barplot(x='i '+'j ', y=")
	plt.hist(podas['i '] + podas['j '])
	plt.show()
	
	

if __name__ == '__main__':
	main(output = sys.argv[-1],show = True)
