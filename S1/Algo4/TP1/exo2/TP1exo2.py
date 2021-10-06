from random import * # chargement de toute la bibliothèque
from matplotlib import pyplot as plt # chargement d ' un des modules de matplotlib


def eltMajDet(T): # il y a forcément un elt majoritaire
    for i in T:
        cpt=0
        for j in T:
            if i==j:
                cpt+=1
        if cpt>=int(len(T)/2):
            return i

# def eltMajDet(T): #renvoie l'indice ayant le + d'occurrences, pas bon
#     d={}
#     for i in T:
#         if not(i in d):
#             d[i]=1
#         else:
#             d[i]+=1
#     v=list(d.values())
#     k=list(d.keys())
#     return k[v.index(max(v))]

def eltMajProba(T):
    while(True):
        elt=choice(T)
        cpt=0
        for i in T:
            if elt==i:
                cpt+=1
        if cpt>=int(len(T)/2):
            return i

def tabAlea(n,a,b,k):
    m=randint(a,b)
    T=[]
    while len(T)<(n-k):
        r=randint(a,b)
        if not(r==m):
            T.append(r)
    T+=[m]*k
    shuffle(T)
    return T

def tabDeb(n,a,b,k):
    m=randint(a,b)
    T=[]
    while len(T)<(n-k):
        r=randint(a,b)
        if not(r==m):
            T.append(r)
    T=[m]*(k-1)+T
    shuffle(T)
    T=[m]+T
    return T

def tabFin(n,a,b,k):
    m=randint(a,b)
    T=[]
    while len(T)<(n-k):
        r=randint(a,b)
        if not(r==m):
            T.append(r)
    T+=[m]*k
    return T

tabTest=[2,3,2,3,2,1,1,1,1]
print("élément majeur:",eltMajDet(tabTest))
print("élément majeur test 2:",eltMajProba(tabTest))
print("tab random:",tabAlea(10,0,10,5))
print("tab randomDeb:",tabDeb(10,0,10,5))
print("tab randomFin:",tabFin(10,0,10,5))
