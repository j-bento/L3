// #include <iostream>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "calcul/calcul.h"

struct predicatRdv {

  // regroupe les donnees partagees entres les threads participants aux RdV :
  int donneePartagee; // compteur
  pthread_cond_t cond; // variable conditionnelle
  pthread_mutex_t verrou; // verrou

};
// 1.
// les 3 paradigmes de synchronisation
// exclusion mutuelle: non / attente évènement: oui / attente fin thread: non
// donc -> variables conditionnelles
struct params {
  
  // structure pour regrouper les parametres d'un thread. 

  int idThread; // un identifiant de thread, de 1 a N (N le nombre
		// total de threads secondaires
  int nbThreads;
  struct predicatRdv *varPartagee;

};

// fonction associee a chaque thread participant au RdV.

void * participant (void * p){ 

  struct params * args = (struct params *) p;
  struct predicatRdv * predicat = args -> varPartagee;
  
  int attente = args->idThread + rand() % 3;
  printf("thread n°%i, début du calcul. Attente : %i secondes\n", args->idThread, attente * 3);
  // Simulation d'un long calcul pour le travail avant RdV
  calcul(attente); // C'est un exemple.
  printf("1er calcul terminé pour thread n°%i\n",args->idThread);
  pthread_mutex_lock(&args->varPartagee->verrou);
  // printf("Lock du thread %i\n",args->idThread);
  // RdV

  // compteur : donneePartagee
  predicat->donneePartagee += 1;
  // printf("Valeur donnee partagée: %i\n", predicat->donneePartagee);
  if(predicat->donneePartagee >= args->nbThreads){ // attention : le dernier arrive ne doit pas attendre. Il doit reveiller tous les autres.
    pthread_cond_broadcast(&predicat->cond);
    printf("Point de rdv atteint, threads tous libérés\n");
  }
  else{ 
    pthread_cond_wait(&predicat->cond,&predicat->verrou);
  }
  pthread_mutex_unlock(&predicat->verrou);
  attente = args -> idThread + rand() % 3;
  printf("thread n°%i, début du 2ème calcul. Attente : %i secondes\n", args->idThread, attente * 3);
  calcul(attente); // reprise et poursuite de l'execution.
  // printf("2ème calcul terminé\n");
  pthread_exit(NULL); // fortement recommande.
}


int main(int argc, char * argv[]){
  
  if (argc!=2) {
    printf("argument requis: %s nombre_threads\n",argv[0]);
    exit(1);
  }

 
  // initialisations 
  pthread_t threads[atoi(argv[1])];
  struct predicatRdv predRdv;
  struct params tabParams[atoi(argv[1])];
  int err;
  // predRdv.cond = PHTREAD_COND_INITIALIZER;
    if ((err = pthread_cond_init(&predRdv.cond, NULL)) != 0) {
        printf("Erreur init var conditionnelle");
        exit(EXIT_FAILURE);
    }

    if ((err = pthread_mutex_init(&predRdv.verrou, NULL)) != 0) {
        perror("Erreur init mutex");
        exit(EXIT_FAILURE);
    }

    predRdv.donneePartagee = 0;

  srand(atoi(argv[1]));  // initialisation de rand pour la simulation de longs calculs
  // creation des threads 
  for (int i = 0; i < atoi(argv[1]); i++){
    tabParams[i].idThread = i+1 ;
    tabParams[i].nbThreads = atoi(argv[1]) ;
    tabParams[i].varPartagee = &predRdv ;

    if (pthread_create(&threads[i], NULL, participant, (void *) &tabParams[i]) != 0){
      perror("erreur creation thread");
      exit(1);
    }
  }

  // attente de la fin des threads. Partie obligatoire 
  for (int i = 0; i < atoi(argv[1]); i++){
      pthread_join(threads[i], NULL);
      printf("fin thread n°%i\n",i+1);
    }
  printf("thread principal : fin de tous les threads secondaires\n");

  // terminer "proprement". 
  pthread_cond_destroy(&predRdv.cond);
  pthread_mutex_destroy(&predRdv.verrou);
  return 0;
}