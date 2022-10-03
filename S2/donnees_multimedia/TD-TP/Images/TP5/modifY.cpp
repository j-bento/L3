#include <stdio.h>
#include <stdlib.h>
#include "../image_ppm.h"

int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int k, nH, nW, nTaille;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm k\n"); 
       exit(1) ;
     }

    sscanf (argv[1],"%s",cNomImgLue);
    sscanf (argv[2],"%i",&k);
   
   if (k < -128 || k > 128){
       printf("Valeur de k invalide\n");
       exit(1);
   }

    strcpy(cNomImgEcrite, cNomImgLue);
    // for (int i=strlen(cNomImgEcrite)-3; i < strlen(cNomImgEcrite); i++) free(cNomImgEcrite[i]);
    cNomImgEcrite[strlen(cNomImgEcrite)-4]='\0';
    strcat(cNomImgEcrite,"modif.pgm");

    OCTET *ImgIn, *ImgOut;
   // on part du principe que les 3 images ont la même dimension
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;

   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nTaille);
   allocation_tableau(ImgOut, OCTET, nTaille);

int Y;
  for (int i=0; i < nTaille; i++)
  {
      Y = ImgIn[i] + k;
      if (Y < 0) ImgOut[i] = 0;
      else if (Y > 255) ImgOut[i] = 255;
      else ImgOut[i] = Y;
  }  
    ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
    printf("Nouveau fichier %s créé\n",cNomImgEcrite);

    free(ImgIn); free(ImgOut);
    return 1;
    
}