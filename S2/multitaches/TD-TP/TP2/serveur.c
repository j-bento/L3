#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

/* Programme serveur */

int main(int argc, char *argv[]) {

  if (argc != 2){
    printf("utilisation : %s port_serveur\n", argv[0]);
    exit(1);
  }
   int res,dsClient;
  /* Etape 1 : créer une socket */   
  int ds = socket(PF_INET, SOCK_STREAM, 0); //SOCK_STREAM pour le tcp, SOCK_DGRAM pour l'udp

  if (ds == -1){
    perror("Serveur : pb creation socket");
    exit(1);
  }
  printf("Serveur : creation de la socket réussie \n");
  
  /* Etape 2 : Nommer la socket du seveur */
  struct sockaddr_in adServeur;
  adServeur.sin_family=AF_INET;
  adServeur.sin_addr.s_addr=INADDR_ANY;
  adServeur.sin_port=htons((short) atoi(argv[1])); //port serveur passé en argument 1
  
  if( (res=bind(ds,(struct sockaddr*) &adServeur,sizeof(adServeur))) < 0){
     perror("Serveur : pb nommage socket");
     exit(1);
  }
  printf("Serveur : nommage de la socket réussie \n");
  /* Etape 3 : passer la socket en mode écoute */
  if((res=listen(ds,3)) < 0){
     perror("Serveur : pb passage mode ecoute");
     exit(1);
  }
  printf("Serveur : passage mode ecoute\n");

  struct sockaddr_in adClient;
  socklen_t lgA=sizeof(struct sockaddr_in);
//   char osef[10];
//   printf("Rentre n'importe quoi pour passer le serveur en mode acceptation\n");
//   fgets(osef,11,stdin);
  char msgClient[100];//message du client
   int pere=getpid();

while (getpid()==pere && 1){  // on fork que si l'on est le père et on boucle sur accept
  if((dsClient=accept(ds,(struct sockaddr *) &adClient,&lgA)) < 0)
   {
     perror("Serveur : pb acceptation demande connexion client");
     exit(1);
   }
   printf("Serveur : demande connexion client acceptée\n");
   // printf("pid actuel: %i, pid pere: %i\n",getpid(),pere);
   fork(); // on fork et on sort instantanément de la boucle
  }

   if (getpid()!=pere){ // on traite le client avec le processus fils
      // printf("pid: %i\n",getpid());
      // fermeture socket serveur
      if ((res=close(ds)) < 0){
         perror("Serveur : pb fermeture socket");
         exit(1);
      }
      printf("Serveur : socket serveur fermée pour le processus fils\n");
      // reception message client
      if ((res=recv(dsClient,&msgClient,sizeof(msgClient),0)) < 0){
      perror("Serveur : pb reception message");
      exit(1);
      }
      // strcat(msgClient,"\0");
      printf("Serveur : message recu : %s \nDu domaine %s, port %d, adresse IP : %s\n",
       msgClient,
       (adClient.sin_family == AF_INET?"AF_INET":"UNKNOWN"),
       ntohs(adClient.sin_port),
       inet_ntoa(adClient.sin_addr));
      // renvoi message au client
      int tailleMsg=strlen(msgClient);
      if ((res=send(dsClient, &tailleMsg, sizeof(tailleMsg), 0)) < 0){
         perror("Serveur : pb envoi réponse au client");
         exit(1);
      }
      printf("Serveur : réponse envoyée au client \n");
      if ((res=close(dsClient)) < 0)
      {
         perror("Serveur : pb fermeture socket client");
         exit(1);
      }

      printf("Serveur : socket client fermée\n");
   }
   
// cette instruction permet d'attendre la fin de l'execution de tous les fils d'un processus
while(wait(0)!=-1){}

  /* Etape 7 : fermer la socket (lorsqu'elle n'est plus utilisée)*/
if (getpid()==pere){
   if ((res=close(ds)) < 0){
      perror("Serveur : pb fermeture socket");
      exit(1);
   }
   printf("Serveur : je termine\n");
}
  return 0;
}
