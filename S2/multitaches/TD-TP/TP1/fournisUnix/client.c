#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

/* Programme client */

int main(int argc, char *argv[]) {

  /* je passe en paramètre l'adresse de la socket du serveur (IP et
     numéro de port) et un numéro de port à donner à la socket créée plus loin.*/

  /* Je teste le passage de parametres. Le nombre et la nature des
     paramètres sont à adapter en fonction des besoins. Sans ces
     paramètres, l'exécution doit être arrétée, autrement, elle
     aboutira à des erreurs.*/
  if (argc != 4){
     //exemple: ./bin/client 91.174.102.81 32768 2000
    printf("utilisation : %s ip_serveur port_serveur port_client\n", argv[0]);
    exit(1);
  }

  /* Etape 1 : créer une socket */   
  int ds = socket(PF_INET, SOCK_DGRAM, 0);

  /* /!\ : Il est indispensable de tester les valeurs de retour de
     toutes les fonctions et agir en fonction des valeurs
     possibles. Voici un exemple */
  if (ds == -1){
    perror("Client : pb creation socket :");
    exit(1); // je choisis ici d'arrêter le programme car le reste
	     // dépendent de la réussite de la création de la socket.
  }
  
  /* J'ajoute des traces pour comprendre l'exécution et savoir
     localiser des éventuelles erreurs */
  printf("Client : creation de la socket réussie \n");
  
  // Je peux tester l'exécution de cette étape avant de passer à la
  // suite. Faire de même pour la suite : n'attendez pas de tout faire
  // avant de tester.
  
  /* Etape 2 : Nommer la socket du client */
  struct sockaddr_in ad;
  ad.sin_family=AF_INET;
  ad.sin_addr.s_addr=INADDR_ANY;
  ad.sin_port=htons((short) atoi(argv[3])); //port client passé en argument 3
  int res=bind(ds,(struct sockaddr*) &ad,sizeof(ad));
  
  if (res==-1){
     perror("Client : pb nommage socket :");
     exit(1);
  }
  printf("Client : nommage de la socket réussie \n");

  /* Etape 3 : Désigner la socket du serveur */
  struct sockaddr_in sockServ ;
  sockServ.sin_family = AF_INET ;
  sockServ.sin_addr.s_addr = inet_addr(argv[1]) ; // adresse IP serveur
  sockServ.sin_port = htons( (short) atoi(argv[2])) ; // exemple "3430", port serveur

  /* Etape 4 : envoyer un message au serveur  (voir sujet pour plus de détails)*/
  socklen_t lgA = sizeof(struct sockaddr_in) ;
  char msg[100];
  printf("Rentrez un message (100 caracteres max): ");
  scanf("%100s",msg);
  printf("votre message: %s \n",msg);

  res = sendto(ds, msg, strlen(msg)+1, 0, (struct sockaddr*)&sockServ, lgA) ;//sizeof(struct...) longueur adresse
  if (res==-1){
     perror("Client : pb envoi message :");
     exit(1);
  }
  printf("Client : envoi message réussi\n");
  /* Etape 5 : recevoir un message du serveur (voir sujet pour plus de détails)*/
  int msgServ;//message du serveur
  res=recvfrom(ds,&msgServ,sizeof(msgServ),0,(struct sockaddr*)&sockServ, &lgA);
  if (res==-1){
     perror("Client : pb reception message :");
     exit(1);
  }
  printf("Client : message reçu du serveur: %i \n",msgServ);
  /* Etape 6 : fermer la socket (lorsqu'elle n'est plus utilisée)*/
  res=close(ds);
  if (res==-1){
     perror("Client : pb fermeture socket :");
     exit(1);
  }
  printf("Client : socket fermee\n");

  printf("Client : je termine\n");
   return 0;
}
