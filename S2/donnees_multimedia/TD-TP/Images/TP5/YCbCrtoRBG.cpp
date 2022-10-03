#include <stdio.h>
#include <stdlib.h>
#include "../image_ppm.h"

int main(int argc, char* argv[])
{
    char cNomImgLueY[250], cNomImgLueCb[250], cNomImgLueCr[250], cNomImgEcrite[250];
    int nH, nW, nTaille, nTaille3;
  
  if (argc != 5) 
     {
       printf("Usage: ImageInY.pgm ImageInCb.pgm ImageInCr.pgm ImageOut.pgm\n"); 
       exit(1) ;
     }
    
    sscanf (argv[1],"%s",cNomImgLueY);
    sscanf (argv[2],"%s",cNomImgLueCb);
    sscanf (argv[3],"%s",cNomImgLueCr);
    sscanf (argv[4],"%s",cNomImgEcrite);

    OCTET *ImgInY, *ImgInCb, *ImgInCr, *ImgOut;
   // on part du principe que les 3 images ont la même dimension
   lire_nb_lignes_colonnes_image_pgm(cNomImgLueY, &nH, &nW);
   nTaille = nH * nW;
   nTaille3 = nTaille * 3;
   printf("hauteur: %ipx , largeur: %ipx , total: %ipx\n",nH,nW,nTaille);
   allocation_tableau(ImgInY, OCTET, nTaille);
   allocation_tableau(ImgInCb, OCTET, nTaille);
   allocation_tableau(ImgInCr, OCTET, nTaille);

   lire_image_pgm(cNomImgLueY, ImgInY, nTaille);
   lire_image_pgm(cNomImgLueCb, ImgInCb, nTaille);
   lire_image_pgm(cNomImgLueCr, ImgInCr, nTaille);

   allocation_tableau(ImgOut, OCTET, nTaille3);
   


  for (int i=0; i < nTaille3; i+=3)
  {
      int R, G, B ;
      R = ImgInY[i/3] + 1.402 * (ImgInCr[i/3] - 128);
      if (R < 0) ImgOut[i] = 0;
      else if (R > 255) ImgOut[i] = 255;
      else ImgOut[i] = R;

      G = ImgInY[i/3] - 0.34414 * (ImgInCb[i/3] - 128) - 0.714414 * (ImgInCr[i/3] -128);
      if (G < 0) ImgOut[i+2] = 0;
      else if (G > 255) ImgOut[i+2] = 255;
      else ImgOut[i+2] = G;

      B = ImgInY[i/3] + 1.402 * (ImgInCb[i/3] - 128);
      if (B < 0) ImgOut[i+1] = 0;
      else if (B > 255) ImgOut[i+1] = 255;
      else ImgOut[i+1] = B;

  }  
    
    ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);

    free(ImgInY); free(ImgInCb); free(ImgInCr);
    return 1;
    
}