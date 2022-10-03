#include <stdio.h>
#include <stdlib.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
    char cNomImgLue[250];
    char nomFich[10];
    strcpy(nomFich,"histo.dat");
    int nH, nW, nTaille;
  
  if (argc != 2) 
     {
       printf("Usage: ImageIn.pgm\n"); 
       exit (1) ;
     }
    
    sscanf (argv[1],"%s",cNomImgLue);

   OCTET *ImgIn;//, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
   printf("hauteur: %ipx , largeur: %ipx , total: %ipx\n",nH,nW,nTaille);
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nTaille);

  float * ddp = (float *) calloc( nH, sizeof(float) ); 
  float * tabVals = (float *) calloc( nH, sizeof(float) );//initialise tableau de nH entiers à 0 pour chaque elt 

  for (int i=0;i<nTaille;i++){
    ddp[ImgIn[i]]++; //compte du nombre de pixels par niveau de gris
  }

  float sum=0;
  for (int i=0; i < nH; i++){
    ddp[i]/=nTaille;
    sum+=ddp[i];
  }
  for (int i=1; i < nH; i++){
    tabVals[i]=tabVals[i-1]+ddp[i];
  }
  printf("somme: %f\n",sum);
   FILE *fich;
   if( (fich = fopen(nomFich, "wb")) == NULL)
      {
	 printf("\nPas d'acces en ecriture sur le fichier %s \n", nomFich);
	 exit(EXIT_FAILURE);
      }
    else
    {
	 fprintf(fich,"# %s\r", nomFich) ;                         /*ecriture entete*/
	 fprintf(fich,"# indice  niveau de gris\r") ;

    for (int i=0; i < 256; i++)
    { 
        fprintf(fich,"%i %f\r",i,tabVals[i]); //intensité, nombre de pixels ayant cette intensité
    }
    fclose(fich);
    free(tabVals);
    
    // plot "histo.dat" with lines
    return 1;
    }
}