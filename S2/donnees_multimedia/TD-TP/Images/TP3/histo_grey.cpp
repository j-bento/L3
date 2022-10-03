#include <stdio.h>
#include <stdlib.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
    char cNomImgLue[250];
    char nomFich[250];
    // strcpy(nomFich,"histo.dat");
    int nH, nW, nTaille;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm HistoOut.dat\n"); 
       exit (1) ;
     }
    
    sscanf (argv[1],"%s",cNomImgLue);
    sscanf (argv[2],"%s",nomFich);

   OCTET *ImgIn;//, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
   printf("hauteur: %dpx , largeur: %dpx , total: %dpx\n",nH,nW,nTaille);
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nTaille);
   
  int * tabVals = (int *) calloc( nH, sizeof(int) );//initialise tableau de nH entiers à 0 pour chaque elt 

  for (int i=0;i<nTaille;i++){
    tabVals[ImgIn[i]]++; //compte du nombre de pixels par niveau de gris
  }

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

    for (int i=0; i < nH; i++)
    { 
        fprintf(fich,"%i %i\r",i,tabVals[i]); //intensité, nombre de pixels ayant cette intensité
    }
    fclose(fich);
    free(tabVals);
    // plot "histo.dat" with lines
    return 1;
    }
}