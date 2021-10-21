import time, re

def clause(s):
    #enlève les doubles espaces ou n-espaces et les réduit à 1
    s=re.sub("  +", " ", s)
    S=s.split(" ")
    #si il y a un espace au début il sera enlevé
    if "" in S:
        S.remove("")
    S=S[:-1]
    S=[int(i) for i in S]
    return S 

def parseur(nom):
    res=[0,0]
    l=[]
    with open('cnf/'+nom,'r') as f:
        for ligne in f:
            if ligne[0]=="c":
                pass
            elif ligne[0]=="p":
                res[1]=int(ligne.split(" ")[2])
                #res[1]=int(res[1].replace("\n",""))
            else:
               l.append(clause(ligne))
    res[0]=l
    return res

def est_valide(F,A):
    for clause in F:
        for litt in clause:
            # if ((litt>0) and (A[abs(litt)-1]>0)) or ((litt<0) and (A[abs(litt)-1]<0)):
            if litt*A[abs(litt)-1]>0: #plus simple...
                #print("ok")
                break
            else:
                #print("pas ok")
                if litt==clause[len(clause)-1]:
                    return False
    return True

def aff_suivante(A):
    n=len(A)
    if A.count(1)==n:
        return None
    i=0
    while i<n and A[i]==1:
        A[i]=-1
        i+=1
    A[i]=1
    return A

def sat_exhau(F,n):
    A=[-1]*n
    while not est_valide(F,A):
        A=aff_suivante(A) #modifie A en testant
        if A is None:
            return None
    return A

def elimination(F,n,B):
    pass
# AA=[-1,-1,-1,-1]
# for i in range(16):
#     AA=aff_suivante(AA)
#     print(AA)

# test=[[1,2],[-1,2],[1,-2],[-1,-2]]
# valTestA=[-1,1,1]
# print(aff_suivante(valTestA))
# print(clause("1 2 -3 0 \n"))
# print(FC)
# print(est_valide(FC[0],valTestA))

#pour les insat
FC=parseur("random-17-unsat.cnf")
t0= time.time()
print(sat_exhau(FC[0],FC[1]))
t1 = time.time() - t0
print("Temps: ", t1,"seconde(s)")

#pour les sat
FC=parseur("random-25-sat.cnf")
t0= time.time()
print(sat_exhau(FC[0],FC[1]))
t1 = time.time() - t0
print("Temps: ", t1,"seconde(s)")