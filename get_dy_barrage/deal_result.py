import numpy as np
import pylab as pl

infile=open("result0619.txt","r+")
line=infile.readline()
x=[]
y=[]
while(line):
	if line[0]!="#":
		x.append(int(line.strip().split("  ")[0]))
		y.append(int(line.strip().split("  ")[1]))
	line=infile.readline()
pl.plot(x,y)
pl.xlabel('Time-point')
pl.ylabel('Barrage-number')
pl.show()