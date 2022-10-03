#include <cstdlib>

#include "image_ppm.h"

#define R 0
#define G 1
#define B 2

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Utilisation : %s image_entree.ppm image_sortie.ppm\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Lecture de l'image d'entrée
    //  1 - Lignes / colonnes 
    int rows, cols;
    lire_nb_lignes_colonnes_image_ppm(argv[1], &rows, &cols);

    //  2 - Allouer les tableaux de l'image d'entrée et sortie
    OCTET *inputImg, *outputImg;
    allocation_tableau(inputImg, OCTET, rows * cols * 3);
    allocation_tableau(outputImg, OCTET, rows * cols * 3);

    //  3 - Lecture des pixels de l'image pgm d'entrée dans le tableau correspondant
    lire_image_ppm(argv[1], inputImg, rows * cols);

    // Flouter
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int index = i*cols*3 + j*3;

            for (int color = R; color <= B; ++color) {
                int key = index + color;
                if (i == 0 || j == 0 || i == rows - 1 || j == cols - 1) {
                    outputImg[key] = inputImg[key];
                }
                else {
                    int sum = 0;

                    for (int k = -1; k <= 1; ++k) {
                        for (int m = -1; m <= 1; ++m) {
                            int key = (i + k)*cols*3 + (j + m)*3 + color;
                            sum += inputImg[key];
                        }
                    }

                    outputImg[key] = round(sum / 9);
                }
            }
        }
    }

    // Écriture dans l'image de sortie
    ecrire_image_ppm(argv[2], outputImg, rows, cols);

    // Libération de la mémoire
    free(inputImg); free(outputImg);

    // C'est fini !
    printf("Image floutée : %s\n", argv[2]);
    return 0;
}

// #include <stdio.h>
// #include <stdlib.h>
// #include "image_ppm.h"

// #define R 0
// #define G 1
// #define B 2

// int main(int argc, char* argv[])
// {
//     char cNomImgLue[250];
//     char cNomImgEcrite[250];
// ;
//     int nH, nW, nTaille, nTaille3;
  
//   if (argc != 3) 
//      {
//        printf("Usage: ImageIn.ppm ImageOut.ppm\n"); 
//        exit (1) ;
//      }
    
//     sscanf (argv[1],"%s",cNomImgLue);
//     sscanf (argv[2],"%s",cNomImgEcrite);

//    OCTET *ImgIn, *ImgOut;
   
//    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
//    nTaille = nH * nW;
//    nTaille3 = nTaille * 3;
//    printf("hauteur: %ipx , largeur: %ipx , total: %ipx\n",nH,nW,nTaille);
   
//    allocation_tableau(ImgIn, OCTET, nTaille3);
//    lire_image_ppm(cNomImgLue, ImgIn, nTaille);
//    allocation_tableau(ImgOut, OCTET, nTaille3);
   
//    for (int i = 0; i < nH; ++i) {
//         for (int j = 0; j < nW; ++j) {
//             int index = i*nW*3 + j*3;

//             for (int color = R; color <= B; ++color) {
//                 int key = index + color;
//                 if (i == 0 || j == 0 || i == nH - 1 || j == nW - 1) {
//                     ImgOut[key] = ImgIn[key];
//                 }
//                 else {
//                   int sum = 0;

//                   for (int k = -1; k <= 1; ++k) {
//                       for (int m = -1; m <= 1; ++m) {
//                           int key = (i + k)*nW*3 + (j + m)*3;
//                           sum += ImgIn[key];
//                         }
//                     }
//                   ImgOut[index] = round(sum / 9);
//                 } 
//             }
//         }
//     }
//     // remplissage des bords 
//     // for (int i=0; i < nW*3; i++){ImgOut[i]=ImgIn[i];} // haut horizontal
//     // for (int i=0; i < nW*3; i++){ImgOut[(nTaille-nW)+i]=ImgIn[(nTaille-nW)+i];} // bas horizontal
//     // for (int i=0; i < nH*3; i++){ImgOut[i*nW]=ImgIn[i*nW];} // gauche vertical
//     // for (int i=0; i < nH*3; i++){ImgOut[i*nW+nH-1]=ImgIn[i*nW+nH-1];} // droite vertical

//     // for (int i=3; i < (nH-1)*3; i+=3)
//     // {
//     //     for (int j=3; j < (nW-1)*3; j+=3)
//     //     { // moyenne des 8 pixels autour d'un pixel + le pixel en question
//     //       for (int k=0; k<3; k++){
//     //         ImgOut[(i*nW+j)+k]=(ImgIn[((i-1)*nW+(j-1))+k] + ImgIn[((i-1)*nW+j)+k] + ImgIn[((i-1)*nW+j+1)+k] +
//     //                             ImgIn[((i*nW)+j-1)+k] + ImgIn[(i*nW+j)+k] + ImgIn[((i*nW)+j+1)+k] +
//     //                             ImgIn[((i+1)*nW+j-1)+k] + ImgIn[((i+1)*nW+j)+k] + ImgIn[((i+1)*nW+j+1)+k])/9;
//     //       }
//           /*
//             // //rouge
//             // ImgOut[i*nW+j]=(ImgIn[(i-1)*nW+(j-1)] + ImgIn[(i-1)*nW+j] + ImgIn[(i-1)*nW+j+1] +\
//             //                 ImgIn[(i*nW)+j-1] + ImgIn[i*nW+j] + ImgIn[(i*nW)+j+1] +\
//             //                 ImgIn[(i+1)*nW+j-1] + ImgIn[(i+1)*nW+j] + ImgIn[(i+1)*nW+j+1])/9;
//             // //vert
//             // ImgOut[(i*nW+j)+1]= (ImgIn[((i-1)*nW+(j-1))+1] + ImgIn[((i-1)*nW+j)+1] + ImgIn[((i-1)*nW+j+1)+1] +\
//             //                     ImgIn[((i*nW)+j-1)+1] + ImgIn[(i*nW+j)+1] + ImgIn[((i*nW)+j+1)+1] +\
//             //                     ImgIn[((i+1)*nW+j-1)+1] + ImgIn[((i+1)*nW+j)+1] + ImgIn[((i+1)*nW+j+1)+1])/9;
//             // //bleu
//             // ImgOut[(i*nW+j)+2]= (ImgIn[((i-1)*nW+(j-1))+2] + ImgIn[((i-1)*nW+j)+2] + ImgIn[((i-1)*nW+j+1)+2] +\
//             //                     ImgIn[((i*nW)+j-1)+2] + ImgIn[(i*nW+j)+2] + ImgIn[((i*nW)+j+1)+2] +\
//             //                     ImgIn[((i+1)*nW+j-1)+2] + ImgIn[((i+1)*nW+j)+2] + ImgIn[((i+1)*nW+j+1)+2])/9;
//             */
//     //     }
//     // }

//    ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
//    free(ImgIn);
//    return 1;
// }