/*A partir de l’image seuillée la plus intéressante, écrire le programme erosion.cpp, qui
va permettre de supprimer les points objets isolés. Compiler ce programme et l’exécuter
en utilisant l’image binaire obtenue précédemment avec le seuil le plus intéressant. Pour
l’exécution, 3 arguments sont nécessaires, à savoir, le nom du programme, le nom de
l’image d’entrée et le nom de l’image de sortie.*/

#include <stdio.h>
#include "image_ppm.h"
#include <algorithm>
using namespace std;

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a >= _b ? _a : _b; })
    
#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a >= _b ? _b : _a; })

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  //int S
  
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm Seuil \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;//chemin image entree

  sscanf (argv[2],"%s",cNomImgEcrite) ;//chemin image de sortie

  OCTET *ImgIn,*ImgOut;
   
 lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);
   //erosion
   //pour un pixel noir , il suffit d'un voisin blanc pour qu'il devienne blanc
   //pour un pixel blanc , il faut que tous les voisins soient noirs
   //dilatation
   // un pixel dont l'entourage est noir , il devient noir

   for (int i=0; i < nH; i++){
    for (int j=0; j < nW; j++)
     {
       //on suppose le pixel courant
       OCTET minPixel=0;

       for(int a=-1;a<=1;a++){
	 for(int b=-1;b<=1;b++){
	   //check des boundaries : faut pas dépasser la taille de l'image
	   if( (i+a)<0 || (i+a)>= nH || (j+b)<0 || (j+b)>nW)
	     continue;
	   //je veux avoir la valeur maximale des pixels dans la zone du pixel courant
	   minPixel=max(minPixel,ImgIn[(i+a)*nW+(j+b)]);
	   
	 }
       }
       ImgOut[i*nW+j]=minPixel;

     }
	  
 } 


   ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
   free(ImgIn);
   return 1;

}
