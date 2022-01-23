//librairies compatibles windows/linux
#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include<string.h>

#ifdef WIN32 //distrib windows
#include <winsock2.h>

#else //distrib unix
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

#endif

/* Programme client */

int main(int argc, char *argv[]) {

  /* je passe en paramètre l'adresse de la socket du serveur (IP et
     numéro de port) et un numéro de port à donner à la socket créée plus loin.*/

  /* Je teste le passage de parametres. Le nombre et la nature des
     paramètres sont à adapter en fonction des besoins. Sans ces
     paramètres, l'exécution doit être arrétée, autrement, elle
     aboutira à des erreurs.*/
  if (argc != 4){
    printf("utilisation : %s ip_serveur port_serveur port_client\n", argv[0]);
    exit(1);
  }

  /* Etape 1 : créer une socket */   
  int ds = socket(PF_INET, SOCK_DGRAM, 0);

  /* /!\ : Il est indispensable de tester les valeurs de retour de
     toutes les fonctions et agir en fonction des valeurs
     possibles. Voici un exemple */
  if (ds == INVALID_SOCKET){
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
  setbuf(stdout, NULL);
  char nom_sock[101];//nom socket, dernier caractère: \0
  printf("Entrez un nom pour la socket: ");
  scanf("%100s",nom_sock); //taille lue par le scanf limitée à 100 caractères
  /* Etape 3 : Désigner la socket du serveur */
  
  /* Etape 4 : envoyer un message au serveur  (voir sujet pour plus de détails)*/
  
  /* Etape 5 : recevoir un message du serveur (voir sujet pour plus de détails)*/
  
  /* Etape 6 : fermer la socket (lorsqu'elle n'est plus utilisée)*/
  
  
  printf("Client : je termine\n");
  return 0;
}
