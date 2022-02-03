#include <stdio.h>
#include <stdlib.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
    char cNomImgLue[250];
    char nomFich[10];
    strcpy(nomFich,"histo.dat");
    int nH, nW, nTaille, nTaille3;
  
  if (argc != 2) 
     {
       printf("Usage: ImageIn.ppm\n"); 
       exit (1) ;
     }
    
    sscanf (argv[1],"%s",cNomImgLue);

   OCTET *ImgIn;//, *ImgOut;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
   nTaille3=nTaille*3;
   printf("hauteur: %ipx , largeur: %ipx , total: %ipx\n",nH,nW,nTaille);
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nTaille);
   
  int *tabVals= (int *) calloc( (nH), sizeof(int) );//initialise tableau de nH entiers pour R, G et B à 0 pour chaque elt 

//   for (int i=0;i<256;i++){
//     tabVals[i]=(int *) calloc(3,sizeof(int));
//   }
  for (int i=0; i < nTaille3; i+=3)
  {
    tabVals[ImgIn[i]]++; //compte du nombre de pixels par niveau de rouge
    tabVals[ImgIn[i+1]]++; //compte du nombre de pixels par niveau de vert
    tabVals[ImgIn[i+2]]++; //compte du nombre de pixels par niveau de bleu
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
	 fprintf(fich,"# indice , nv rouge , nv vert , nv bleu\r") ;

    for (int i=0; i < nH; i+=3)
    { 
        fprintf(fich,"%i %i %i %i\r",i/3,tabVals[i],tabVals[i+1],tabVals[i+2]); //indice, niveau de rouge,vert,bleu du pixel pour chaque pixel
    }
    fclose(fich);
    free(tabVals);
    // plot "histo.dat" using 1:2 with lines //histo rouge
    // plot "histo.dat" using 1:3 with lines //histo vert
    // plot "histo.dat" using 1:4 with lines //histo bleu
    // en meme temps:
    /*
plot "histo.dat" using 1:2 title "rouge" lc rgb "red" with lines,\
"histo.dat" using 1:3 title "vert" lc rgb "green" with lines,\
"histo.dat" using 1:4 title "bleu" lc rgb "blue" with lines
    */
    return 1;
    }
}