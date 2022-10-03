// fonctions utiles pour les images
#include "image_ppm.h"

typedef unsigned char OCTET;
#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a >= _b ? _a : _b; })
    
#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a >= _b ? _b : _a; })

void histo_grey(OCTET *in, int nW, int nH, char *nom_fich)
{
    int *tabVals = (int *) calloc( nH, sizeof(int) );//initialise tableau de nH entiers à 0 pour chaque elt 
    int nTaille = nH * nW;
    for (int i=0;i<nTaille;i++)
    {
        tabVals[in[i]]++; //compte du nombre de pixels par niveau de gris
    }
    FILE *fich;
    if( (fich = fopen(nom_fich, "wb")) == NULL)
    {
	    printf("\nPas d'acces en ecriture sur le fichier %s \n", nom_fich);
	    exit(EXIT_FAILURE);
    }
    else
    {
        fprintf(fich,"# %s\r", nom_fich) ;                         /*ecriture entete*/
        fprintf(fich,"# indice  niveau de gris\r") ;

        for (int i=0; i < nH; i++)
        { 
            fprintf(fich,"%i %i\r",i,tabVals[i]); //intensité, nombre de pixels ayant cette intensité
        }
        fclose(fich);
        free(tabVals);
    }
}

void histo_couleur(OCTET *in, int nW, int nH, char *nom_fich)
{
    int *tabVals = (int *) calloc( nH, sizeof(int) );//initialise tableau de nH entiers à 0 pour chaque elt 
    int nTaille = nH * nW;
    int nTaille3 = nTaille * 3;
    for (int i=0; i < nTaille3; i+=3)
  {
    tabVals[in[i]]++; //compte du nombre de pixels par niveau de rouge
    tabVals[in[i+1]]++; //compte du nombre de pixels par niveau de vert
    tabVals[in[i+2]]++; //compte du nombre de pixels par niveau de bleu
  }
   FILE *fich;
   if( (fich = fopen(nom_fich, "wb")) == NULL)
      {
	 printf("\nPas d'acces en ecriture sur le fichier %s \n", nom_fich);
	 exit(EXIT_FAILURE);
      }
    else
    {
	 fprintf(fich,"# %s\r", nom_fich) ;                         /*ecriture entete*/
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
    }
}

void profil(OCTET *in, int nW, int nH, char *nom_fich, char *type, int indice)
{
    int *tabVals;
    if (strcmp(type,"colonne")==0){
      tabVals = (int *) calloc( nH, sizeof(int) );//initialise tableau de nH entiers à 0 pour chaque elt 
      for(int i=0;i<nH;i++){
          tabVals[i]=in[indice+nH*i];
      }
  }
  else if(strcmp(type,"ligne")==0){
      tabVals = (int *) calloc( nW, sizeof(int) );//initialise tableau de nW entiers à 0 pour chaque elt 
      for(int i=0;i<nW;i++){
          tabVals[i]=in[(indice%nW)+i];
      }
  }
  else{
      printf("Type invalide\n");
      exit(1);
  }

   FILE *fich;
   if( (fich = fopen(nom_fich, "wb")) == NULL)
      {
	 printf("\nPas d'acces en ecriture sur le fichier %s \n", nom_fich);
	 exit(EXIT_FAILURE);
      }
    else
    {
	 fprintf(fich,"# %s\r", nom_fich) ;                         /*ecriture entete*/
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
    }
}

void seuillage_2_parties_couleur(OCTET *in, OCTET *out, int nW, int nH, int S_R, int S_G, int S_B)
{
    int nTaille = nH * nW;
    int nTaille3 = nTaille * 3;
    int nR, nG, nB;
    for (int i=0; i < nTaille3; i+=3)
     {
       nR = in[i];
       nG = in[i+1];
       nB = in[i+2];
       if (nR < S_R) out[i]=0; else out[i]=255;
       if (nG < S_G) out[i+1]=0; else out[i+1]=255; 
       if (nB < S_B) out[i+2]=0; else out[i+2]=255;
     }
}

void seuillage_2_parties(OCTET *in, OCTET *out, int nW, int nH, int S)
{
    int nTaille = nW * nH;
    for (int i=0; i < nTaille; i++)
    {
        if ( in[i] < S) out[i]=0;
        else out[i]=255;
    }
}

void seuillage_3_parties(OCTET *in, OCTET *out, int nW, int nH, int S1, int S2)
{
    int nTaille = nW * nH;
    for (int i=0; i < nTaille; i++)
    {
        if ( in[i] < S1) out[i]=0;
        else
        {
            if ( in[i] < S2) out[i]=128; 
            else out[i]=255;
        }
    }
}

void seuillage_4_parties(OCTET *in, OCTET *out, int nW, int nH, int S1, int S2, int S3)
{
    int nTaille = nW * nH;
    for (int i=0; i < nTaille; i++)
    {
        if ( in[i] < S1) out[i]=0;
        else
        {
            if ( in[i] < S2) out[i]=85; 
            else 
            {
                if ( in[i] < S3) out[i]=170;
                else out[i]=255;
            }
        }
    }
}
void filtre_flou1(OCTET *in, OCTET *out, int nW, int nH)
{
    int nTaille = nW * nH;
    // remplissage des bords 
    for (int i=0; i < nW; i++){in[i]=out[i];} // haut horizontal
    for (int i=0; i < nW; i++){in[(nTaille-nW)+i]=out[(nTaille-nW)+i];} // bas horizontal
    for (int i=0; i < nH; i++){in[i*nW]=out[i*nW];} // gauche vertical
    for (int i=0; i < nH; i++){in[i*nW+nH-1]=out[i*nW+nH-1];} // droite vertical

    for (int i=1; i < nH-1; i++)
    {
        for (int j=1; j < nW-1; j++)
        {
            in[i*nW+j]=(out[i*nW+j]+out[i*nW+(j-1)]+out[(i*nW)+j+1]+\
                           out[(i+1)*nW+j]+out[(i-1)*nW+j])/5;
        }
    }
}

void filtre_flou2(OCTET *in, OCTET *out, int nW, int nH)
{
    int nTaille = nW * nH;
    //remplissage des bords
    for (int i=0; i < nW; i++){out[i]=in[i];} // haut horizontal
    for (int i=0; i < nW; i++){out[(nTaille-nW)+i]=in[(nTaille-nW)+i];} // bas horizontal
    for (int i=0; i < nH; i++){out[i*nW]=in[i*nW];} // gauche vertical
    for (int i=0; i < nH; i++){out[i*nW+nH-1]=in[i*nW+nH-1];} // droite vertical

    for (int i=1; i < nH-1; i++)
    {
        for (int j=1; j < nW-1; j++)
        { // moyenne des 8 pixels autour d'un pixel + le pixel en question
            out[i*nW+j]=(in[(i-1)*nW+(j-1)] + in[(i-1)*nW+j] + in[(i-1)*nW+j+1] +\
                            in[(i*nW)+j-1] + in[i*nW+j] + in[(i*nW)+j+1] +\
                            in[(i+1)*nW+j-1] + in[(i+1)*nW+j] + in[(i+1)*nW+j+1])/9;
        }
    }
}
void flou_couleur(OCTET *in, OCTET *out, int nW, int nH)
{
    
     for (int i=3; i < (nH-1)*3; i+=3)
    {
        for (int j=3; j < (nW-1)*3; j+=3)
        { // moyenne des 8 pixels autour d'un pixel + le pixel en question
            //rouge
            out[i*nW+j]=(in[(i-1)*nW+(j-1)] + in[(i-1)*nW+j] + in[(i-1)*nW+j+1] +\
                            in[(i*nW)+j-1] + in[i*nW+j] + in[(i*nW)+j+1] +\
                            in[(i+1)*nW+j-1] + in[(i+1)*nW+j] + in[(i+1)*nW+j+1])/9;
            //vert
            out[(i*nW+j)+1]= (in[((i-1)*nW+(j-1))+1] + in[((i-1)*nW+j)+1] + in[((i-1)*nW+j+1)+1] +\
                                in[((i*nW)+j-1)+1] + in[(i*nW+j)+1] + in[((i*nW)+j+1)+1] +\
                                in[((i+1)*nW+j-1)+1] + in[((i+1)*nW+j)+1] + in[((i+1)*nW+j+1)+1])/9;
            //bleu
            out[(i*nW+j)+2]= (in[((i-1)*nW+(j-1))+2] + in[((i-1)*nW+j)+2] + in[((i-1)*nW+j+1)+2] +\
                                in[((i*nW)+j-1)+2] + in[(i*nW+j)+2] + in[((i*nW)+j+1)+2] +\
                                in[((i+1)*nW+j-1)+2] + in[((i+1)*nW+j)+2] + in[((i+1)*nW+j+1)+2])/9;
        }
    }
}

void Ymodif(OCTET *in, OCTET *out, char *nom_in, int nW, int nH, int k){//in et out non alloués, -128 <= k <= 128

    int nTaille = nW * nH;
    int Y;
    char nom_out[250];

    strcpy(nom_out, nom_in);
    nom_out[strlen(nom_out)-4]='\0';
    strcat(nom_out,"modif.pgm");

    allocation_tableau(in, OCTET, nTaille);
    lire_image_pgm(nom_in, in, nTaille);
    allocation_tableau(out, OCTET, nTaille);
    for (int i=0; i < nTaille; i++)
    {
      Y = in[i] + k;
      if (Y < 0) out[i] = 0;
      else if (Y > 255) out[i] = 255;
      else out[i] = Y;
    } 
    ecrire_image_pgm(nom_out, out,  nH, nW);
    printf("Nouveau fichier %s créé\n",nom_out);

    free(in); free(out);
}