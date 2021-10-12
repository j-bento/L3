from random import * # chargement de toute la bibliothèque
from matplotlib import pyplot as plt # chargement d ' un des modules de matplotlib
import time

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

# n1=1000
# n2=10000
# tabRandom1=tabAlea(n1,0,n1,randint(n1/2,n1))
# tabRandomDeb1=tabDeb(n1,0,n1,randint(n1/2,n1))
# tabRandomFin1=tabFin(n1,0,n1,randint(n1/2,n1))

# tabRandom2=tabAlea(n2,0,n2,randint(n2/2,n2))
# tabRandomDeb2=tabDeb(n2,0,n2,randint(n2/2,n2))
# tabRandomFin2=tabFin(n2,0,n2,randint(n2/2,n2))

# t0= time.time()
# eltMajDet(tabRandom2)
# eltMajDet(tabRandomDeb2)
# eltMajDet(tabRandomFin2)
# t1 = time.time() - t0
# print("Temps: ", t1,"seconde(s)")

# t0= time.time()
# eltMajProba(tabRandom2)
# eltMajProba(tabRandomDeb2)
# eltMajProba(tabRandomFin2)
# t1 = time.time() - t0
# print("Temps: ", t1,"seconde(s)")
#deterministe meilleur pour tabRandom, tabRandomDeb
#probabiliste meilleur pour tabRandomFin

# %time eltMajDet(tabRandom1) #ne marche pas :/
# %time eltMajProba(tabRandom1)
# print(tabRandom1)
# print("élément majeur:",eltMajDet(tabTest))
# print("élément majeur test 2:",eltMajProba(tabTest))
# print("tab random:",tabAlea(10,0,10,5))
# print("tab randomDeb:",tabDeb(10,0,10,5))
# print("tab randomFin:",tabFin(10,0,10,5))

def contientMajProba(T,m):
    for i in range(m):
        indAlea=randint(0,len(T)-1)
        #print("nombre aléatoire:",T[indAlea])
        j=0;cpt=0
        while cpt<len(T)/2 and j<len(T):
            if T[j]==T[indAlea]:
                cpt+=1
            j+=1
        if cpt>=len(T)/2:
            return True
    return False

def testContient(n,a,b,k,m,N):
    tabTest=tabAlea(n,a,b,k)#tableau avec elt maj apparaissant k fois avec des elts entre a et b
    cpt=0 #nombre de réussites
    for i in range(N): #on reproduit N fois l'expérience
        if contientMajProba(tabTest,m):
            cpt+=1 #comptage du nombre de réussites
    return cpt
L1=[]
for k in range(500,1001,50):
    L1.append(testContient(1000,0,100,k,1,1000))
# plus k augmente, plus on trouve d'éléments majeurs (logique)
# (jusqu'à 100% lorsque k=n)
L2=[]
for m in range(1,11):
    L2.append(testContient(1000,0,100,500,m,1000))
# devient très efficace quand on augmente m
# mais atteint peu souvent 100% de réussite
print(L1,L2)
# plt.plot(L1); plt.plot(L2)
# plt.show()
# tabTest=tabAlea(10,0,10,5)
# print(tabTest)
# print(contientMajProba(tabTest,3))