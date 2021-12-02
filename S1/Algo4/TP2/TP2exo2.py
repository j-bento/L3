import time

def lecture_sudoku(nom):
    G=[]
    with open('sudokus/'+nom,"r") as f:
        n=int(f.readline().replace("\n",""))
        for line in f:
            for nbr in line.split():
                G.append(int(nbr))
    return (G,n)

def ecriture_sudoku(G,n,nom):
    f=open('sudokus/'+nom,"w")
    f.write(str(n)+'\n')
    for i in range(n**4):
        f.write(str(G[i])+' ')
        if(i%(n*n)==8):
            f.write('\n')

def affiche_sudoku(G,n):
    for i in range(n**4):
        if G[i]==0:
            print('_',end=" ")
        else:
            print(G[i],end=" ")
        if(i%(n*n)==8):
            print()


def zone(n,u):
    #debut: va chercher le début de la zone à partir de laquelle on
    #recupere tous les indices de la zone
    debut=u
    l=[]
    while (debut-1)%n<debut%n:#verif horizontale: tant que le modulo est plus petit, on n'a pas changé de zone
        debut-=1    
    while (debut-n*n)%(n**3)<(debut)%(n**3):#verif verticale: même chose que pour horizontale mais en hauteur
        debut-=(n*n)
    #on est maintenant à l'extrémité haut-gauche de la zone
    #on remplit simplement la liste des elts de la zone à partir du début
    for i in range(n):
        for j in range(n):
            l.append(debut+j+(i*n*n))
    return l

# def valide(G,n,u,x):#u: indice où on veut placer x
#     for i in zone(n,u):#vérif dans la zone
#         if G[i]==x: #and not i==u:#on regarde si
#             return False
#     for i in range(u-u%(n**2),(u-u%(n**2))+n**2):#vérif horizontale
#         if G[i]==x:
#             return False
#     for i in range(u%(n**2),n**4,n**2):#vérif verticale
#         if G[i]==x:
#             return False
#     return True

def valide(G,n,u,x):#version du cours
        (i,j)=(u//(n**2),u%(n**2))
        for k in range(n**2):
            #   vertical                      horizontal
            if (k!=i and G[k*(n**2)+j]==x) or (k!=j and G[i*(n**2)+k]==x):
                return False
        for k in zone(n,u):
            if G[k]==x and k!=u:
                return False
        return True

# def all_valide(G,n):
#     return all([valide(G,n,i,G[i]) for i in range(n**4)])

def sudoku(G,n,u):
    while u<n**4 and G[u]!=0:
        u+=1
    if u==n**4:
        ecriture_sudoku(G,n,'grille_completée')
        return True
    for x in range(1,n**2+1):#on teste les n valeurs possibles sur 1 indice
        if valide(G,n,u,x):
            G[u]=x
            if sudoku(G,n,u+1):
                return True
    G[u]=0
    return False


affiche_sudoku([i for i in range(81)],3)#grille des indices

grille=lecture_sudoku("sudoku-3-moyen-1.txt")
affiche_sudoku(grille[0],grille[1])

t0= time.time()
if sudoku(grille[0],grille[1],0):
    t1 = time.time() - t0
    print("Temps: ", t1,"seconde(s)")   
    grille=lecture_sudoku("grille_completée")
    affiche_sudoku(grille[0],grille[1])
#pour sudoku-3-moyen-9.txt, ~ 1 seconde
#devient trop long à partir de sudoku-3-difficile-1.txt
#TODO améliorer la complexité