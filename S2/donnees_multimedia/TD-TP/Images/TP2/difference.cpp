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
  char cNomImgLue1[250], cNomImgLue2[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  //int S
  
  
  if (argc != 4) 
     {
       printf("Usage: ImageIn1.pgm ImageIn2.pgm ImageOut.pgm \n"); 
       exit (1) ;
     }
   
  sscanf (argv[1],"%s",cNomImgLue1) ;//chemin image 1 entree
  sscanf (argv[2],"%s",cNomImgLue2) ;//chemin image 2 entree
  sscanf (argv[3],"%s",cNomImgEcrite) ;//chemin image de sortie
 
   OCTET *ImgIn1, *ImgIn2,*ImgOut;
   //on suppose img1 et img2 de meme taille
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue1, &nH, &nW);
   nTaille = nH * nW;

   allocation_tableau(ImgIn1, OCTET, nTaille);
   allocation_tableau(ImgIn2, OCTET, nTaille);

   lire_image_pgm(cNomImgLue1, ImgIn1, nH * nW);
   lire_image_pgm(cNomImgLue2, ImgIn2, nH * nW);

   allocation_tableau(ImgOut, OCTET, nTaille);

    //erosion
    for (int i=0; i < nTaille; i++){
        //le pixel appartient au fond ou à l'objet pour le pixel des 2 images
        if  ( (min(ImgIn1[i],ImgIn2[i]) == 255) || (max(ImgIn1[i],ImgIn2[i]) == 0) ){
            ImgOut[i]=255;
        }
        else{
            ImgOut[i]=0;
        }
    }


   ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
   free(ImgIn1);
   free(ImgIn2);
   return 1;

}
