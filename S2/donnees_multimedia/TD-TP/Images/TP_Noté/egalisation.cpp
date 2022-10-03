#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    char nomFich[10];
    strcpy(nomFich,"histo.dat");
    int nH, nW, nTaille;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm\n"); 
       exit (1) ;
     }
    
    sscanf (argv[1],"%s",cNomImgLue);
    sscanf (argv[2],"%s",cNomImgEcrite);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
   printf("hauteur: %ipx , largeur: %ipx , total: %ipx\n",nH,nW,nTaille);
   allocation_tableau(ImgIn, OCTET, nTaille);
   allocation_tableau(ImgOut, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nTaille);

  float * ddp = (float *) calloc( nH, sizeof(float) );
  float * F = (float *) calloc( nH, sizeof(float) ); 

  for (int i=0;i<nTaille;i++){
    ddp[ImgIn[i]]++; //compte du nombre de pixels par niveau de gris
  }

  float sum=0;
  for (int i=0; i < nH; i++){
    ddp[i]/=nTaille;
    sum+=ddp[i];
  }
  for (int i=1; i < nH; i++){
    F[i]=F[i-1]+ddp[i];
  }
  for (int i=0; i < nTaille; i++){
    ImgOut[i]=(int) round(F[ImgIn[i]]*255);
  }

    ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn);free(ImgOut);
    
    // plot "histo.dat" with lines
    return 1;
}