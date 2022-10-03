#include <string.h>
#include <stdio.h>//perror
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
// #include <iostream>
#include "./calcul/calcul.h"
#include <pthread.h>

#define bool unsigned int

#define true 1

#define false 0

struct paramsFonctionThread {
  
  int idThread;
  int nbsec;
  int donnee;
  // si d'autres parametres, les ajouter ici.

};
void tache(int *entier,bool slp){
  *entier+=20;
  if(slp) {
    sleep(1);
  }
}

void * fonctionThread (void * params){

  struct paramsFonctionThread * args = (struct paramsFonctionThread *) params;
  pthread_t moi = pthread_self();
  printf("processus: %i, thread: %li, idThread: %i\n",getpid(), moi, args->idThread);

  calcul(args->nbsec);
  if ((args->idThread)%2==0){
    tache(& args->donnee, 1);
  }
  else{
    tache(& args->donnee, 0);

  }
  
  printf("Calcul fini, thread: %li, idThread: %i, Val donnee: %i\n", moi, args->idThread, args->donnee);
  pthread_exit(NULL);
}


int main(int argc, char * argv[]){

  if (argc < 2 ){
    printf("utilisation : %s nombre_threads\n", argv[0]);
    return 1;
  }     
  
  pthread_t threads[atoi(argv[1])];
  int donnee=0;
  struct paramsFonctionThread params;
  // creation des threads 
  for (int i = 0; i < atoi(argv[1]); i++){

    struct paramsFonctionThread params;
    params.idThread=i;
    params.nbsec=i+1;
    params.donnee=donnee;
      // completer pour initialiser les parametres

    if (pthread_create(&threads[i], NULL, fonctionThread,(void *) &params) != 0){
      perror("erreur creation thread");
      exit(1);
    }
  }


// garder cette saisie et modifier le code en temps venu.
  char c; 
  printf("saisir un caractere \n");
  fgets(&c, 2, stdin);

  return 0;
 
}
 
