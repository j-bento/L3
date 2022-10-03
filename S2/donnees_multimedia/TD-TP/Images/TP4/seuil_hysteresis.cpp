#include <stdio.h>
#include "image_ppm.h"
 #define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, SB, SH, minPixel;
  
  if (argc != 5) 
     {
       printf("Usage: ImageIn.pgm ImageOut.pgm Seuil1 Seuil2\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);
   sscanf (argv[3],"%d",&SB);
   sscanf (argv[4],"%d",&SH);

   OCTET *ImgIn,*ImgInterm, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgInterm, OCTET, nTaille);
   allocation_tableau(ImgOut, OCTET, nTaille);
	
// seuillage par hysteresis 
// partie 1: seuillage
for (int i=0; i < nTaille; i++)
{
    if ( ImgIn[i] < SB) ImgInterm[i]=0;
    else
    {
        if ( ImgIn[i] < SH) {}//ImgOut[i]=128; 
        else ImgInterm[i]=255;
    }
}
// partie 2 : erosion
for (int i=0; i < nH; i++)
{
    for (int j=0; j < nW; j++)
    {
        if ( ImgInterm[i] <= SH)
        {
            for(int a=-1;a<=1;a++)
            {
                for(int b=-1;b<=1;b++)
                {
                //check des boundaries : faut pas dépasser la taille de l'image
                if( (i+a)<0 || (i+a)>= nH || (j+b)<0 || (j+b)>nW)
                    continue;
                //je veux avoir la valeur maximale des pixels dans la zone du pixel courant
                minPixel=max(minPixel,ImgInterm[(i+a)*nW+(j+b)]);
                }
            }
        ImgOut[i*nW+j]=minPixel;
        }
    }
}

// seuil : entre 15 et 30


   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);
   free(ImgInterm);
   return 1;
}