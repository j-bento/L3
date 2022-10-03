// #include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include "calcul/calcul.h"

// structure qui regroupe les variables partagees entre les threads.
struct varPartagees {
  int nbZones;
  int * di; // le tableau indique dans l'enonce
  pthread_cond_t cond;
  pthread_mutex_t verrou;
};

// structure qui regroupe les parametres d'un thread
struct params {

  int idThread; // cet entier correspond au numero de traitement associe a un thread
  
  struct varPartagees * vPartage;


};

// fonction associee a chaque thread secondaire a creer.

void * traitement (void * p) {

  struct params * args = (struct params *) p;
  struct  varPartagees *  vPartage = args -> vPartage;

  for(int i = 1; i <= vPartage -> nbZones; i++){

    
    
    if( args -> idThread != 1){ // le premier traitement n'attend personne
      
      
      while(1){
   	// attente fin traitement sur la zone i 
      }
    }

    

      // dans cette partie, le traitement de la zone i est a faire en faisant une simulation d'un long calcul (appel a calcul(...)
    
    
      // a la fin du traitement d'une zone, le signaler pour qu'un thread en attente se reveille. 
      
 
  pthread_exit(NULL); 
  }
}




int main(int argc, char * argv[]){
  
  if (argc!=3) {
    printf(" argument requis: %s nb_traitements nb_zones\n",argv[0]);
    exit(1);
  }
 
   // initialisations 
  pthread_t threads[atoi(argv[1])];
  struct params tabParams[atoi(argv[1])];

  struct varPartagees vPartage;

  vPartage.nbZones =  atoi(argv[2]);
  vPartage.di = NULL;
  int err;
  if ((err = pthread_cond_init(&vPartage.cond, NULL)) != 0) {
    printf("Erreur init var conditionnelle");
    exit(EXIT_FAILURE);
  }

  if ((err = pthread_mutex_init(&vPartage.verrou, NULL)) != 0) {
    perror("Erreur init mutex");
    exit(EXIT_FAILURE);
  }

  srand(atoi(argv[1]));  // initialisation de rand pour la simulation de longs calculs
 
  // creation des threads 
  for (int i = 0; i < atoi(argv[1]); i++){
    tabParams[i].idThread = i+1 ;
    tabParams[i].vPartage = &vPartage; 
    if (pthread_create(&threads[i], NULL, traitement,(void *) &tabParams[i]) != 0){
      perror("erreur creation thread");
      exit(1);
    }
  }

  
  // attente de la fin des threads. Partie obligatoire 
  for (int i = 0; i < atoi(argv[1]); i++){
    pthread_join(threads[i],NULL);
    printf("fin thread n°%i\n",i+1);
  }
  printf("thread principal : fin de tous les threads secondaires\n");

  // liberer les ressources avant terminaison 
  
  return 0;
}
 
