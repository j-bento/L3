// #include <iostream>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "calcul/calcul.h"


typedef struct {
  
  // structure pour regrouper les parametres d'un thread. 
  int idThread; // un identifiant de thread, de 1 a N (N le nombre

} params;

void *T1 (void * par){
    printf("thread 1 lancé\n");
    int * cp = (int*)(par);
    for(int i=0; i < 250000000; i++) ++(*cp);
    pthread_exit(NULL);
}

void *T2 (void * par){
    printf("thread 2 lancé\n");
    int * cp = (int*)(par);
    for(int i=0; i < 300000000; i++) ++(*cp);
    pthread_exit(NULL);
}
int main(){

    // if (argc!=2) {
    // printf("argument requis: %s nombre_threads\n",argv[0]);
    // exit(1);
    // }

    // pthread_t threads[atoi(argv[1])];
    // params tabParams;
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER; 
    pthread_t thread1, thread2;
    int res, counter = 0;
    // int res;
    if (pthread_create(&thread1, NULL, T1, (void *) &counter) != 0){
      perror("erreur creation thread");
      exit(1);
    }
    
    if ((res = pthread_join(thread1,NULL)) != 0){
        perror("Problème avec le thread");
        exit(1);
    }
    else{
        printf("thread 1 fini, counter : %i\n",counter);
        if (pthread_create(&thread2, NULL, T2, (void *) &counter) != 0){
            perror("erreur creation thread");
            exit(1);
        }
    }
    
    // int res = pthread_join(thread1, NULL);
    res = pthread_join(thread2, NULL);
    printf(" Total = %i\n",counter);
    // printf("%i\n",res);
    if(res){}
    return 0;
}