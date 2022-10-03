#include <stdio.h>
#include <stdlib.h>
#include "../image_ppm.h"

int main(int argc, char* argv[])
{
    char cNomImgLue[250], NomImgY[250], NomImgCr[250], NomImgCb[250];
    int nH, nW, nTaille, nTaille3;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.ppm ImageOut\n"); 
       exit (1) ;
     }
    
    sscanf (argv[1],"%s",cNomImgLue);
    sscanf (argv[2],"%s",NomImgY);
    sscanf (argv[2],"%s",NomImgCb);
    sscanf (argv[2],"%s",NomImgCr);

    strcat(NomImgY , "Y.pgm");
    strcat(NomImgCb , "Cb.pgm");
    strcat(NomImgCr , "Cr.pgm");
    OCTET *ImgIn, *ImgOutY, *ImgOutCb, *ImgOutCr;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
   nTaille3=nTaille*3;
   printf("hauteur: %ipx , largeur: %ipx , total: %ipx\n",nH,nW,nTaille);
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nTaille);
   allocation_tableau(ImgOutY, OCTET, nTaille);
   allocation_tableau(ImgOutCb, OCTET, nTaille);
   allocation_tableau(ImgOutCr, OCTET, nTaille);
   
  for (int i=0; i < nTaille3; i+=3)
  {
      ImgOutY[i/3]  = (0.299*ImgIn[i]) + (0.587*ImgIn[i+1]) + (0.114*ImgIn[i+2]) ;
      ImgOutCb[i/3] = (-0.1687*ImgIn[i]) + (-0.3313*ImgIn[i+1]) + (0.5*ImgIn[i+2]) + 128 ;
      ImgOutCr[i/3] = (0.5*ImgIn[i]) - (0.4187*ImgIn[i+1]) - (0.0813*ImgIn[i+2]) + 128 ;

    // int Y, Cb, Cr;
    //   Y = (int) ( (0.299*ImgIn[i]) + (0.587*ImgIn[i+1]) + (0.114*ImgIn[i+2]) );
    //   if (Y < 0) ImgOutY[i/3] = 0;
    //   else if (Y > 255) ImgOutY[i/3] = 255;
    //   else ImgOutY[i/3] = Y;

    //   Cb = (int) ( (-0.1687*ImgIn[i]) + (-0.3313*ImgIn[i+1]) + (0.5*ImgIn[i+2]) + 128 );
    //   if (Cb < 0) ImgOutCb[i/3] = 0;
    //   else if (Cb > 255) ImgOutCb[i/3] = 255;
    //   else ImgOutCb[i/3] = Cb;

    //   Cr = (int) ( (0.5*ImgIn[i]) + (-0.4187*ImgIn[i+1]) + (-0.0813*ImgIn[i+2]) + 128 );
    //   if (Cr < 0) ImgOutCr[i/3] = 0;
    //   else if (Cr > 255) ImgOutCr[i/3] = 255;
    //   else ImgOutCr[i/3] = Cr;
  }
    
    ecrire_image_pgm(NomImgY, ImgOutY,  nH, nW);
    ecrire_image_pgm(NomImgCb, ImgOutCb,  nH, nW);
    ecrire_image_pgm(NomImgCr, ImgOutCr,  nH, nW);
    free(ImgIn);
    return 1;
    
}