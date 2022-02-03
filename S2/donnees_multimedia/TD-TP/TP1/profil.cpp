#include <stdio.h>
#include <stdlib.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
    char cNomImgLue[250];
    char nomFich[10], type[10];
    strcpy(nomFich,"fich.dat");
    int nH, nW, nTaille, indice;
  
  if (argc != 4) 
     {
       printf("Usage: ImageIn.pgm ligne/colonne indice\n"); 
       exit (1) ;
     }
    
    sscanf (argv[1],"%s",cNomImgLue);
    sscanf (argv[2],"%s",type);
    sscanf (argv[3],"%i",&indice);

   OCTET *ImgIn;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
   printf("hauteur: %ipx , largeur: %ipx , total: %ipx\n",nH,nW,nTaille);
   
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nTaille);
   printf("val ind: %i, val ind+nH*150: %i\n",ImgIn[indice],ImgIn[indice+nH*150]);
   int * tabVals;// = (int *) calloc( 256, sizeof(int) );//initialise tableau

  if (strcmp(type,"colonne")==0){
      tabVals = (int *) calloc( nH, sizeof(int) );//initialise tableau de nH entiers à 0 pour chaque elt 
      for(int i=0;i<nH;i++){
          tabVals[i]=ImgIn[indice+nH*i];
      }
  }
  else if(strcmp(type,"ligne")==0){
      tabVals = (int *) calloc( nW, sizeof(int) );//initialise tableau de nW entiers à 0 pour chaque elt 
      for(int i=0;i<nW;i++){
          tabVals[i]=ImgIn[(indice%nW)+i];
      }
  }
  else{
      printf("Type invalide\n");
      exit(1);
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
	 fprintf(fich,"# indice  niveau de gris %s\r",type) ;

    if (strcmp(type,"colonne")==0){
        for (int i=0; i < nH; i++)
        { 
            fprintf(fich,"%i %i\r",i,tabVals[i]); //indice, niveau de gris du pixel pour chaque pixel
        }
    }
    else{
        for (int i=0; i < nW; i++)
        { 
            fprintf(fich,"%i %i\r",i,tabVals[i]); //indice, niveau de gris du pixel pour chaque pixel
        }
    }
    fclose(fich);
    free(tabVals);
    // plot "histo.dat" with lines
    return 1;
    }
}