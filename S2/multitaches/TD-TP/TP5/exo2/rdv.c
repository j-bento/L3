#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <time.h>
// #include <iostream>
//pour ajouter la fonction calcul

void calcul(int nSem) {
  int wait = (rand() % 6) + 1;
  printf("[%i] Calcul d'environ %i secondes.\n", nSem, wait);
  sleep(wait);
}

int main(int argc, char * argv[]){
  srand(time(NULL) ^ (getpid() << 16));
  if (argc!=4) {
    printf("Nbre d'args invalide, utilisation :\n");
    printf("%s fichier-pour-cle-ipc entier-pour-clé-ipc nombreRdv\n", argv[0]);
    exit(0);
  }

  //création du la clé de sémaphore  
  int clesem = ftok(argv[1], atoi(argv[2]));
  int nbRdv = atoi(argv[3]);

  //création du tableau de sémaphores
  int idSem=semget(clesem,1,0600);
  
  if(idSem == -1){
    perror("erreur semget : ");
    exit(-1);
  }
      
        typedef union semun {
            int val;
            struct semid_ds *buf;
            ushort *array;
        } SemUn;

        // valinit.array = (unsigned short*)malloc(nbSem * sizeof(unsigned short)); 

        // if (semctl(idSem, 0, GETALL, valinit) == -1){ //parametre 2 ignoré car on utilise GETALL
        //   perror("erreur initialisation sem : ");
        //   exit(1);
        // } 
        SemUn unionAff;
        unionAff.array=(ushort*)malloc(nbRdv * sizeof(ushort)); 

        for(int i=0; i<nbRdv; i++){
        calcul(idSem); //calcul
        printf("[%i] Calcul terminé, mise à jour du point de rendez-vous.\n", idSem);

        struct sembuf op[]={{i,-1,0},{i,0,0}}; // 2 elts dans op[] (ici p et z) (p : n < 0, v : n = 0, z : n > 0)
        // printf("Valeurs des semaphores [ "); 
        // for(int i=0; i < nbSem-1; i++){
        //   printf("%d, ", valinit.array[i]);
        // }
        // printf("%d ] \n", valinit.array[nbSem-1]);
        
        if(semop(idSem,op,1) == -1){
            perror("erreur semop");
            exit(1);
        }
        semctl(idSem,nbRdv,GETALL,unionAff);
        printf("Sémaphore actuelle : %i\n",i);
        printf("Valeurs des semaphores: [ "); 
        for(int i = 0; i < nbRdv - 1; i++) {
            printf("%d, ", unionAff.array[i]);
        } 
        printf("%d ] \n", unionAff.array[nbRdv - 1]);
        // Tant que semaphores[i] n'est pas à 0, on attend.
        if(semop(idSem,op + 1,1)==-1){
            perror("erreur semop");
            exit(1);
        }

        }
        return 0;
        }