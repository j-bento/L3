import time

def lecture_sudoku(nom):
    G=[]
    with open('sudokus/'+nom,"r") as f:
        n=int(f.readline().replace("\n",""))
        for line in f:
            G.append([int(i) for i in line.split()])
    return (G,n)

def ecriture_sudoku(G,n,nom):
    f=open('sudokus/'+nom,"w")
    f.write(str(n)+'\n')
    for i in range(n*n):
        for nbr in G[i]:
            f.write(str(nbr)+' ')
        f.write('\n')

def affiche_sudoku(G,n):
    for i in G:
        for nbr in i:
            if nbr==0:
                print('_',end=" ")
            else:
                print(nbr,end=" ")
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

# grille=lecture_sudoku("sudoku-3-difficile-5.txt")
# sudoku_indices=[[j+i*9 for j in range(9)] for i in range(9)]
# affiche_sudoku(sudoku_indices,3)
# print(zone(3,5))
# ecriture_sudoku(grille[0],grille[1],input("Entrez un nom de fichier:\n"))
