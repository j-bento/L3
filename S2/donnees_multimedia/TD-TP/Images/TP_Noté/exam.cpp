#include "../fonctions_image.h"
#include "../image_ppm.h"

int main(int argc, char **argv){
    char cNomImgLue[250], cNomImgEcrite[250];
    int k, nH, nW, nTaille;
  
    if (argc != 3) 
    {
       printf("Usage: ImageIn.pgm k\n"); 
       exit(1) ;
    }

    sscanf (argv[1],"%s",cNomImgLue);
    sscanf (argv[2],"%i",&k);
    
    if (k < -128 || k > 128){
       printf("Valeur de k invalide\n");
       exit(1);
    }
    OCTET *ImgIn, *ImgOut;
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;

    Ymodif(ImgIn,ImgOut,cNomImgLue, nH,nW,k);

    return 0;
}