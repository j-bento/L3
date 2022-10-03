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
    printf("utilisation : %s ip_serveur port_serveur port_client\n", argv[0]);
    exit(1);
  }
  int res;
  /* Etape 1 : créer une socket */   
  int ds = socket(PF_INET, SOCK_STREAM, 0);//SOCK_STREAM pour le tcp, SOCK_DGRAM pour l'udp

  /* /!\ : Il est indispensable de tester les valeurs de retour de
     toutes les fonctions et agir en fonction des valeurs
     possibles. Voici un exemple */
  if (ds == -1){
    perror("Client : pb creation socket");
    exit(1); // je choisis ici d'arrêter le programme car le reste
	     // dépendent de la réussite de la création de la socket.
  }
  
  /* J'ajoute des traces pour comprendre l'exécution et savoir
     localiser des éventuelles erreurs */
  printf("Client : creation de la socket réussie \n");
  // hypothèse de cette fonction: on connait la taille exacte du message à envoyer
  int sendTCP(int sock, void *msg, int sizeMsg){ //void*: pointeur sur une case mémoire de tout type
      int res,reste_octets,octets_envoyes;
      reste_octets=sizeMsg;
      octets_envoyes=0;
      while(reste_octets!=0){
         res=send(sock,msg+octets_envoyes,reste_octets,0); //res stocke le nombre d'octets envoyés
         if ( res<= 0 ){
            return res;
         }
         reste_octets-=res;
         octets_envoyes+=res;
      }
      return 1;
  }
  
  /* Etape 3 : Désigner la socket du serveur */
  struct sockaddr_in sockServ ;
  sockServ.sin_family = AF_INET ;
  sockServ.sin_addr.s_addr = inet_addr(argv[1]) ; // adresse IP serveur
  sockServ.sin_port = htons( (short) atoi(argv[2])) ; // exemple "3430", port serveur
  socklen_t lgA = sizeof(struct sockaddr_in) ;

  /* Etape 4 : demande connexion au serveur  (voir sujet pour plus de détails)*/
  if((res=connect(ds,(struct sockaddr*)&sockServ,lgA)) < 0){
     perror("Client : pb demande connexion");
     exit(1);
  }
   printf("Client : demande connexion effectuée\n");
  /* Etape 5 : envoyer un message au serveur  (voir sujet pour plus de détails)*/
  void prg1(){
      int res;
      char msg[6];// = {'s', 't', 'r', 'i', 'n', 'g'};
      fgets(msg,6,stdin);
      char msg2[6];
      memcpy(msg2,msg,strlen(msg)-1);
      // char msg[11] = "un message ";
      // for (int i=0; i<strlen(msg)+2;i++) printf("%c",msg[i]);
      // msg[strcspn(msg,"\n")]=0; //pour enlever le \n qui se rajoute à la fin de msg
      // msg[strcspn(msg,"\0")]=0; //enlever le \0 ?
      if((res = send(ds, &msg2, strlen(msg), 0)) < 0){//(send sans le \0)
         perror("Client : pb envoi message");
      }
      printf("Client : message envoyé au serveur (1)\n");    
      // strcat(msg,"\0");
      if((res = send(ds, &msg2, strlen(msg)+1, 0)) < 0){//(send sans le \0)
         perror("Client : pb envoi message");
      }
  printf("Client : message envoyé au serveur (2)\n");
  }
//   prg1();
  char msg[100];
  printf("Rentrez un message (100 caracteres max): ");
  // scanf("%100s",msg); //nul, ne marche pas avec les espaces
  fgets(msg,101,stdin);
  msg[strcspn(msg,"\n")]=0; //pour enlever le \n qui se rajoute à la fin de msg
  printf("votre message: %s \n",msg);

  res=sendTCP(ds,msg,strlen(msg)+1);
  if (res==-1){
     perror("Client : pb envoi sendTCP");
     exit(1);
  }
  else if (res==0){
     printf("Client : socket serveur fermée");
  }

//   if((res = send(ds, &msg, strlen(msg)+1, 0)) < 0){//sizeof(struct...) longueur adresse
//       perror("Client : pb envoi message");
//   }
//   printf("Client : message envoyé au serveur\n");

  /* Etape 6 : recevoir un message du serveur (voir sujet pour plus de détails)*/
  int msgServ;//message du serveur
  if ((res=recv(ds,&msgServ,sizeof(msgServ),0)) < 0){
     perror("Client : pb reception message");
     exit(1);
  }
  printf("Client : message reçu du serveur: %i \n",msgServ);

  /* Etape 7 : fermer la socket (lorsqu'elle n'est plus utilisée)*/
  if ((res=close(ds)) < 0){
     perror("Client : pb fermeture socket");
     exit(1);
  }
  printf("Client : socket fermée\n");
  
  printf("Client : je termine\n");
  return 0;
}
