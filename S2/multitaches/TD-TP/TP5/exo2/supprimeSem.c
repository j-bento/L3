#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>

int main(int argc, char * argv[]){

  if (argc!=3) {
    printf("Nbre d'args invalide, utilisation :\n");
    printf("%s fichier-pour-cle-ipc entier-pour-cle-ipc\n", argv[0]);
    exit(0);
  }
	  
  int cleSem=ftok(argv[1], atoi(argv[2]));

  int idSem = semget(cleSem, atoi(argv[2]), 0600);

  // j'utilise semget de sorte a s'assurer que le tableau a d�truire existe.
  if (idSem==-1){
    perror("erreur semget");
    exit(-1);
  }

  printf("sem id : %d \n", idSem);

  // destruction :
  if (semctl(idSem, 0, IPC_RMID, NULL)==-1)
    perror(" erreur semctl : ");

  return 0;
}

