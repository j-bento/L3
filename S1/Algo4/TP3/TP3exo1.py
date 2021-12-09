from dessins import *
from math import sqrt
from random import randint,random,uniform
def distance(A,B):
    x1,y1=(A[0],A[1])
    x2,y2=(B[0],B[1])
    return sqrt((x2-x1)**2+(y2-y1)**2)

A, B, C = (121,77), (48,70), (12,72)
# print(distance(A,B), distance(A,C), distance(B,C))

def aretes(P):
    res=[]
    for i in range(len(P)):
        for j in range(i+1,len(P)):
            res.append((i,j,distance(P[i],P[j])))
    return res
P = [(6,20),(67,18),(96,4),(32,45)]
# print(aretes(P))

def pointsAleatoires(n, xmax, ymax):
    return [(uniform(0,xmax),uniform(0,ymax)) for _ in range(n)]

# print(pointsAleatoires(3,10,20))
# dessinPoints(pointsAleatoires(30,10,20))