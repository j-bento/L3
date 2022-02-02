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

  /* Etape 1 : créer une socket */   
  int ds = socket(PF_INET, SOCK_DGRAM, 0);

  /* /!\ : Il est indispensable de tester les valeurs de retour de
     toutes les fonctions et agir en fonction des valeurs
     possibles. Voici un exemple */
  if (ds == -1){
    perror("Serveur : pb creation socket :");
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

  int res=bind(ds,(struct sockaddr*) &adServeur,sizeof(adServeur));
  
  if (res==-1){
     perror("Serveur : pb nommage socket ");
     exit(1);
  }
  printf("Serveur : nommage de la socket réussie \n");
  socklen_t namelen = sizeof(adServeur);
   if (getsockname(ds, (struct sockaddr *) &adServeur, &namelen) < 0)
   {
       perror("Serveur : getsockname()");
       exit(3);
   }

   printf("Serveur : port assigné: %d\n", ntohs(adServeur.sin_port));
   printf("Serveur : adresse assignée: %s\n",inet_ntoa(adServeur.sin_addr));

  /* Etape 4 : recevoir un message du client (voir sujet pour plus de détails)*/
//   int msgClient[10];
  char msgClient[100];//message du client
  struct sockaddr_in adClient;
  socklen_t lgA = sizeof(struct sockaddr_in) ;

  do{
      res=recvfrom(ds,&msgClient,sizeof(msgClient),0,(struct sockaddr*) &adClient, &lgA);
      if (res==-1){
      perror("Client : pb reception message \n");
      exit(1);
      }
      printf("Serveur : message recu : %s \nDu domaine %s, port %d, adresse IP : %s\n",
       msgClient,
       (adClient.sin_family == AF_INET?"AF_INET":"UNKNOWN"),
       ntohs(adClient.sin_port),
       inet_ntoa(adClient.sin_addr));

      /* Etape 5 : envoyer un message au serveur (voir sujet pour plus de détails)*/
      int tailleMsg=strlen(msgClient);
      if ((res=sendto(ds, &tailleMsg, sizeof(tailleMsg), 0, (struct sockaddr*)&adClient, lgA)) < 0){
         perror("Serveur : pb envoi réponse au client \n");
         exit(1);
      }
      printf("Serveur : réponse envoyée au client \n");
  } while (strcmp(msgClient,"fin")!=0 && strcmp(msgClient,"end")!=0);

  /* Etape 6 : fermer la socket (lorsqu'elle n'est plus utilisée)*/
  if ((res=close(ds)) ==-1){
     perror("Serveur : pb fermeture socket \n");
     exit(1);
  }
  printf("Serveur : socket fermée\n");
  printf("Serveur : je termine\n");
  return 0;
}