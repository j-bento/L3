import time, re

def clause(s):
    return [int(i) for i in s.split()][:-1]

def parseur(nom):
    res=[0,0]
    l=[]
    with open('cnf/'+nom,"r") as f:
        for ligne in f:
            if ligne[0]=="p":
                res[1]=int(ligne.split(" ")[-2])
            elif ligne[0]!="c":
               l.append(clause(ligne))
    res[0]=l
    return res

def est_valide(F,A):
    for clause in F:
        for litt in clause:
            # if ((litt>0) and (A[abs(litt)-1]>0)) or ((litt<0) and (A[abs(litt)-1]<0)):
            if litt*A[abs(litt)-1]>0: #plus simple...
                break
            elif litt==clause[len(clause)-1]:
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

def elimination(F,n,b):#but: éliminer la var Xn
    #formule résultat après l'élimination
    Fres=[]
    for C in F:
        Cres=[]
        sat=False
        for litt in C:
            if abs(litt)==n:
                if litt*b>0:
                    sat=True
            else:
                Cres.append(litt)
        if not sat:
            Fres.append(Cres)
    return Fres       

def sat_backtrack(F, n):
    if len(F)==0:#cas où F est vide
        return [1]*n
    if [] in F:#cas où F contient une clause vide
        return None
    for b in range(-1,2,2):#on prend b=-1 puis b=1
        Fres=elimination(F,n,b)
        A=sat_backtrack(Fres,n-1)
        if A is not None:
            if A!=None:
                return A.append(b)
    return None
    

# AA=[-1,-1,-1,-1]
# for i in range(16):
#     AA=aff_suivante(AA)
#     print(AA)

# test=[[1,2],[3,4],[5,6]]
# print(sat_exhau(test,6),sat_backtrack(test,6))

# valTestA=[-1,1,1]
# print(aff_suivante(valTestA))
# print(clause("1 2 -3 0 \n"))
# print(FC)
# print(est_valide(FC[0],valTestA))

#pour les insat
# FC=parseur("random-17-unsat.cnf")
# t0= time.time()
# print(sat_exhau(FC[0],FC[1]))
# t1 = time.time() - t0
# print("Temps: ", t1,"seconde(s)")

# pour les sat
FC=parseur("random-25-sat.cnf")
t0= time.time()
print(sat_backtrack(FC[0],FC[1]))
t1 = time.time() - t0
print("Temps: ", t1,"seconde(s)")