from random import * # chargement de toute la bibliothèque
from matplotlib import pyplot as plt # chargement d ' un des modules de matplotlib

#randint(a,b): prend des nombres de a à b inclus
#randrange(a,b): prend des nombres de a à b non inclus
def entiersAleatoires(n,a,b):
    liste=[]
    for i in range(n):
        liste.append(randint(a,b))
    return liste

def entiersAleatoires2(n,a,b):
    liste=[]
    for i in range(n):
        liste.append(randrange(a,b))
    return liste

# print(entiersAleatoires(7,0,10))
# print(entiersAleatoires2(7,0,10))
# L1=entiersAleatoires(1000,1,100)
# L2=entiersAleatoires2(1000,1,100)
# plt.hist(L1,bins=100)
# plt.hist(L2,bins=100)

# plt.show() #-> pas uniforme
def flottantsAleatoires(n):
    liste=[]
    for i in range(n):
        liste.append(random())
    return liste

def flottantsAleatoires2(n,a,b):
    liste=[]
    for i in range(n):
        liste.append(uniform(a,b))
    return liste

# print(flottantsAleatoires(7))#génère entre 0 et 1
# print(flottantsAleatoires2(7,0,10))#génère entre a et b
# L2=flottantsAleatoires(1000)
# L1=flottantsAleatoires2(1000,-3,10)
# plt.plot(L1);plt.plot(L2)
# plt.show()

def pointsDisque(n):
    liste=[]
    while len(liste)<n:
        x=uniform(-1,1)
        y=uniform(-1,1)
        if (x**2+y**2)<=1:
            liste.append((x,y))
    return liste

def pointsDisque2(n):
    liste=[]
    while len(liste)<n:
        x=uniform(-1,1)
        y=uniform(-1,1)
        while not((x**2+y**2)<=1):
            y=uniform(-1,1)
        liste.append((x,y))
    return liste

# print(pointsDisque(3))
# print(pointsDisque2(3))
def affichagePoints(L):
    X = [x for x,y in L] # on récupère les abscisses...
    Y = [y for x,y in L] # ... et les ordonnées
    plt.scatter(X, Y, s = 1) # taille des points minimale
    plt.axis('square') # même échelle en abscisse et ordonnée
    plt.show()
# L1=pointsDisque(10000)
# L2=pointsDisque2(10000)
# affichagePoints(L1) #uniforme
# affichagePoints(L2) #pas uniforme, plus de points sur les côtés

def aleatoireModulo(N):
    x=getrandbits(N.bit_length())
    return x%N

def aleatoireRejet(N):
    x=getrandbits(N.bit_length())
    while not(x<N):
        x=getrandbits(N.bit_length())
    return x
# print(aleatoireModulo(17))
# print(aleatoireRejet(40))
L1=[ aleatoireModulo(100) for i in range(10000)]#pas uniforme
L2=[ aleatoireRejet(100) for i in range(10000)]#uniforme
plt.hist(L1,bins=100)
plt.hist(L2,bins=100)
plt.show()