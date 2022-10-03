#include <stdio.h>
#include <stdlib.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
    char cNomImgLue[250];
    char cNomImgEcrite[250];
;
    int nH, nW, nTaille, nTaille3;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.ppm ImageOut.ppm\n"); 
       exit (1) ;
     }
    
    sscanf (argv[1],"%s",cNomImgLue);
    sscanf (argv[2],"%s",cNomImgEcrite);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
   nTaille3 = nTaille * 3;
   OCTET *ImgR, *ImgV, *ImgB;
   allocation_tableau(ImgR, OCTET, nTaille);
   allocation_tableau(ImgV, OCTET, nTaille);
   allocation_tableau(ImgB, OCTET, nTaille);
   planR(ImgR,ImgIn,nTaille3);
   planV(ImgV,ImgIn,nTaille3);
   planB(ImgB,ImgIn,nTaille3);
   printf("hauteur: %ipx , largeur: %ipx , total: %ipx\n",nH,nW,nTaille);
   
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nTaille);
   allocation_tableau(ImgOut, OCTET, nTaille3);
   

   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   return 1;
}