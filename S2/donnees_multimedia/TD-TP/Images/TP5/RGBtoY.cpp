#include <stdio.h>
#include <stdlib.h>
#include "../image_ppm.h"

int main(int argc, char* argv[])
{
    char cNomImgLue[250];
    char cNomImgEcrite[250];
    int nH, nW, nTaille, nTaille3;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.ppm ImageOut.pgm\n"); 
       exit (1) ;
     }
    
    sscanf (argv[1],"%s",cNomImgLue);
    sscanf (argv[2],"%s",cNomImgEcrite);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
   nTaille3=nTaille*3;
   printf("hauteur: %ipx , largeur: %ipx , total: %ipx\n",nH,nW,nTaille);
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nTaille);
   allocation_tableau(ImgOut, OCTET, nTaille);
   
  for (int i=0; i < nTaille3; i+=3)
  {
    //   ImgOut[i/3]=(ImgIn[i]+ImgIn[i+1]+ImgIn[i+2])/3; //moyenne des R G B
        ImgOut[i/3] = (int) ( (0.299*ImgIn[i]) + (0.587*ImgIn[i+1]) + (0.114*ImgIn[i+2]) );
  }
    ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn);
    return 1;
    
}