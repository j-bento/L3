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

  /* Je passe en paramètre le numéro de port qui sera donné à la socket créée plus loin.*/

  /* Je teste le passage de parametres. Le nombre et la nature des
     paramètres sont à adapter en fonction des besoins. Sans ces
     paramètres, l'exécution doit être arrétée, autrement, elle
     aboutira à des erreurs.*/
  if (argc != 2){
    printf("utilisation : %s port_serveur\n", argv[0]);
    exit(1);
  }
   int res,dsClient;
  /* Etape 1 : créer une socket */   
  int ds = socket(PF_INET, SOCK_STREAM, 0); //SOCK_STREAM pour le tcp, SOCK_DGRAM pour l'udp

  /* /!\ : Il est indispensable de tester les valeurs de retour de
     toutes les fonctions et agir en fonction des valeurs
     possibles. Voici un exemple */
  if (ds == -1){
    perror("Serveur : pb creation socket");
    exit(1); // je choisis ici d'arrêter le programme car le reste
	     // dépendent de la réussite de la création de la socket.
  }
  
  /* J'ajoute des traces pour comprendre l'exécution et savoir
     localiser des éventuelles erreurs */
  printf("Serveur : creation de la socket réussie \n");
  
  // Je peux tester l'exécution de cette étape avant de passer à la
  // suite. Faire de même pour la suite : n'attendez pas de tout faire
  // avant de tester.
  
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
  /* Etape 4 : accepter une connexion */
  struct sockaddr_in adClient;
  socklen_t lgA=sizeof(struct sockaddr_in);
//   char osef[10];
//   printf("Rentre n'importe quoi pour passer le serveur en mode acceptation\n");
//   fgets(osef,11,stdin);
  char msgClient[100];//message du client

for (int i=0; i<3;i++){
  if((dsClient=accept(ds,(struct sockaddr *) &adClient,&lgA)) < 0)
   {
     perror("Serveur : pb acceptation demande connexion client");
     exit(1);
   }
   printf("Serveur : demande connexion client acceptée\n");
  /* Etape 5 : recevoir un message du client (voir sujet pour plus de détails)*/
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

      /* Etape 6 : renvoyer un message au client (voir sujet pour plus de détails)*/
      int tailleMsg=strlen(msgClient);
      if ((res=send(dsClient, &tailleMsg, sizeof(tailleMsg), 0)) < 0){
         perror("Serveur : pb envoi réponse au client");
         exit(1);
      }
      printf("Serveur : réponse envoyée au client \n");
}

  
  /* Etape 7 : fermer la socket (lorsqu'elle n'est plus utilisée)*/
  if ((res=close(ds)) < 0){
     perror("Serveur : pb fermeture socket");
     exit(1);
  }
  if ((res=close(dsClient)) < 0){
     perror("Serveur : pb fermeture socket client");
     exit(1);
  }
  printf("Serveur : sockets fermées\n");
  
  printf("Serveur : je termine\n");
  return 0;
}
