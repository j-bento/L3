#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include<arpa/inet.h>
#include<string.h>


/* Ce programme est à compléter et à déposer sur Moodle (c'est le seul fichier à déposer).

   Lire attentivement les instructions en commentaires pour compléter correctement ce programme.
 
   Les principales étapes de ce programme sont :
 
   1) demander à un serveur UDP une liste d'adresses de serveurs TCP existants.
 
   2) se connecter à l'un de ces serveurs TCP et échanger avec ce serveur.
 
   3) faire évoluer votre programme pour ajouter un serveur TCP qui échangera avec un exécutable client fourni.
 
   4) modifier votre programme pour qu'il soit capable de traiter plusieurs clients de manière itérative.
 
   5) modifier votre programme pour qu'il soit capable de traiter plusieurs clients  simultanéments (en utilisant la fonction fork()).
 
   Attention : vous devez déposer un code qui compile. Exemple : si vous êtes à l'étape 4 qui n'est pas fonctionnelle, la mettre en commentaire pour que toutes les étapes d'avant soient validées.
  
*/

#define MAXSRV 100


// cette structure est le type du message à envoyer au serveur UDP
struct nomClient{
  short type; // doit être égal à 1
  char hostname[50];
};

typedef struct nomClient sNomClient;

int main(int argc, char *argv[]) {

  if (argc != 4){
    printf("Utilisation : %s ip_serveurUDP port_serveurUDP param3 \n param3 est un entier dont la signification sera fournie par une question. En attendant cette question, passer n'importe quelle valeur\n", argv[0]);
    exit(0);
  }
  
  /* Etape 1 : envoyer un message au serveur UDP et recevoir une réponse :
  
     1) le message à envoyer est de type sNomClient. Il permet d'envoyer le nom de la machine sur laquelle s'exécute votre client. Voir plus loin le code fourni pour vous aider.
   
     2) le message à recevoir est une liste d'élements de type sock_addr_in. Chaque élément représente l'adresse d'un serveur TCP existant.
   
  */
  
  int dSUDP= socket(PF_INET, SOCK_DGRAM, 0);
  
  if (dSUDP < 0){
    perror("Erreur a la creation de la socket :");
    return 1;
  }     
 
  // designer la socket distante du serveur UDP 
   if (dSUDP == -1){
    perror("Client : pb creation socket \n");
    exit(1);
    }

  printf("Client : creation de la socket réussie \n");

  struct sockaddr_in aD;
  
  aD.sin_family=AF_INET;
  //...
  aD.sin_addr.s_addr=INADDR_ANY;
//   aD.sin_port=htons((short) atoi(argv[3]));
  int res=bind(dSUDP,(struct sockaddr*) &aD,sizeof(aD));         
 
  // Le code suivant prépare le message à envoyer au serveur UDP.
  sNomClient nom;
  nom.type = 1;
  nom.hostname[0]='\0';
  char h[50];
  gethostname(h, 50); // récupère le nom de la machine que vous utilisez.
  strcat(nom.hostname, h);
  // Le message à envoyer au serveur UDP est construit.
  // Envoyer ce message au serveur UDP
  socklen_t lgA = sizeof(struct sockaddr_in) ;
  struct sockaddr_in sockServ ;
  sockServ.sin_family = AF_INET ;
  sockServ.sin_addr.s_addr = inet_addr(argv[1]) ;
  sockServ.sin_port = htons( (short) atoi(argv[2])) ;

  res = sendto(dSUDP, &nom, sizeof(nom), 0, (struct sockaddr*)&sockServ, lgA);

  if (res == -1)
  {
    perror("pb envoi message");
    exit(1);
  }

  printf("message envoyé \n");
  // ...

  // la réponse à recevoir est a stocker dans le tableau suivant. votre programme recevra au plus 50 adresses de serveurs TCP
  struct sockaddr_in reponse[50];

  res=recvfrom(dSUDP,&reponse,sizeof(reponse),0,(struct sockaddr*)&sockServ, &lgA);

  if (res == -1)
  {
    perror("pb reception reponse");
    exit(1);
  }
  printf("message recu du serveur \n");
  // ...

  /* affichage de la liste des adresses recues et demande de choix d'un
     serveur. On suppose qu'au moins un serveur tourne. En l'absence d'un serveur, on termine proprement */

  printf("Les serveurs TCP existants : \n"); 
  for(int i = 0; i < 50; i++) // Attention : une modification doit être faite ici.
    printf("%d. IP %s, port %d \n", i+1, inet_ntoa(reponse[i].sin_addr),  ntohs(reponse[i].sin_port));
    
  printf("Choisir un numero de serveur (1 ou 2 ou ... ): \n");
  int numS;
  scanf("%d", &numS);

  
  // A présent, plus besoin d'échanger avec le serveur UDP.
 
 
  /* Etape 2 : Echanger avec le serveur TCP choisi. 
    
     Après connexion :
 
     1) recevoir une chaîne de caractères dont la taille est connue par le serveur (à vous d'en déduire ce qui est nécecessaire de faire) puis afficher le message reçu.
   
     2) recevoir un entier. 
     
     Remarque : le serveur peut mettre fin à l'échange avec votre client à n'importe quel moment. Il faut donc bien prévoir ce cas.
   
     3) termine les échanges avec le serveur TCP.
      
  */ 
 
 
 // A vous de jouer
 // ...

  int dsTCP=socket(AF_INET, SOCK_STREAM, 0);
   if (dsTCP == -1){
    perror("pb creation socket");
    exit(1);
   }
   printf("socket tcp creee\n");

  struct sockaddr_in sockServTCP ;
  sockServTCP.sin_family = AF_INET ;
  sockServTCP.sin_addr.s_addr = reponse[numS].sin_addr.s_addr ;
  sockServTCP.sin_port = reponse[numS].sin_port ;

//  if((res=connect(dsTCP,(struct sockaddr*)&sockServTCP,lgA)) < 0){
//      perror("pb demande connexion ");
//      exit(1);
//   }
//    printf("demande connexion effectuée\n");
//    // 1)
//    char msgServ[250];
//    res=recv(dsTCP,msgServ,sizeof(msgServ),0);
//    if(res<0){
//      perror("pb reception message");
//      exit(1);
//   }

//    printf("message recu: %s\n",msgServ);
//    // 2)
//    int msgServ2;
//    res=recv(dsTCP,&msgServ2,sizeof(int),0);
//    if(res<0){
//      perror("pb reception message 2");
//      exit(1);
//   }
//    printf("message 2 recu: %i\n",msgServ2);
//    // 3)
//    res=close(dsTCP);
  
  // L'étape suivante est indépendante de la précédente. Donc, elle peut s'exécuter même en cas d'erreurs / fermetures de scokets lors des précédents échange.
  
  /* Etape 3 : Mettre en place un serveur TCP. Ensuite passer à l'étape 4 : Modifier ce serveur pour qu'il soit itératif. Enfin, l'étape 5 : modifier le serveur pour qu'il soit concurrent (en utilisant la fonction fork()). 
 
     Pour l'étape 3, le serveur a un numéro de port qui est le dernier paramètre de votre programme. Ce serveur doit faire ce qui suit pour chaque client :
 
     1) recevoir un tableau de 320000 entiers (int) envoyé par ce client
     2) renvoyer le tableau reçu au client.
     3) recevoir en réponse une chaine de caractères dont la taille est connue par le client (à vous de savoir ce qu'il est nécessaire de faire pour l'obtenir) 
     4) terminer l'échange avec ce client
     
     Pour tester votre serveur, executez le le binaire ./bin/clients fourni. Ce dernier lancera 5 clients.
  */ 
  
 // A vous de jouer.

   //Etape 3
   int dsClient;
   int ds = socket(PF_INET, SOCK_STREAM, 0);

  if (ds == -1){
    perror("Serveur : pb creation socket");
    exit(1);
  }
  printf("Serveur : creation de la socket réussie \n");
  
  struct sockaddr_in adServeur;
  adServeur.sin_family=AF_INET;
  adServeur.sin_addr.s_addr=INADDR_ANY;
  adServeur.sin_port=htons((short) atoi(argv[3]));
  
  if( (res=bind(ds,(struct sockaddr*) &adServeur,sizeof(adServeur))) < 0){
     perror("Serveur : pb nommage socket");
     exit(1);
  }
  printf("Serveur : nommage de la socket réussie \n");
 
  if((res=listen(ds,10)) < 0){
     perror("Serveur : pb passage mode ecoute");
     exit(1);
  }
  printf("Serveur : passage mode ecoute\n");
  struct sockaddr_in adClient;
  int msgClient[320000];
  //Code pour gérer un seul client
//   if((dsClient=accept(ds,(struct sockaddr *) &adClient,&lgA)) < 0){
//       perror("Serveur : pb acceptation demande connexion client");
//       exit(1);
//    }
//    printf("Serveur : demande connexion client acceptée\n");

//    if ((res=recv(dsClient,&msgClient,sizeof(msgClient),0)) < 0){
//       perror("Serveur : pb reception message");
//       exit(1);
//    }
//    printf("Serveur : message recu du client %i\n",msgClient[1]);
//    if ((res=send(dsClient, &msgClient, sizeof(msgClient), 0)) < 0){
//          perror("Serveur : pb envoi réponse au client");
//          exit(1);
//       }
//       printf("Serveur : réponse envoyée au client \n");

   //Etape 4 : Serveur itératif
   // while(1){
   //    if((dsClient=accept(ds,(struct sockaddr *) &adClient,&lgA)) < 0){
   //       perror("Serveur : pb acceptation demande connexion client");
   //       exit(1);
   //    }
   //    printf("Serveur : demande connexion client acceptée\n");

   //    if ((res=recv(dsClient,&msgClient,sizeof(msgClient),0)) < 0){
   //       perror("Serveur : pb reception message");
   //       exit(1);
   //    }
   //    printf("Serveur : message recu du client\n");
   //    if ((res=send(dsClient, &msgClient, sizeof(msgClient), 0)) < 0){
   //       perror("Serveur : pb envoi réponse au client");
   //       exit(1);
   //    }
   //    printf("Serveur : réponse envoyée au client \n");
   // }

   //Etape 5 : serveur concurrent
   int pere=getpid();
    while(getpid()==pere && 1){
    if((dsClient=accept(ds,(struct sockaddr *) &adClient,&lgA)) < 0){
         perror("Serveur : pb acceptation demande connexion client");
         exit(1);
    }
    printf("Serveur : demande connexion client acceptée\n");
    fork();
  }
   if (getpid()!=pere){ // on traite le client avec le processus fils
      if ((res=close(ds)) < 0){
         perror("Serveur : pb fermeture socket");
         exit(1);
      }
      printf("Serveur : socket serveur fermée pour le processus fils\n");

      if ((res=recv(dsClient,&msgClient,sizeof(msgClient),0)) < 0){
         perror("Serveur : pb reception message");
         exit(1);
      }
      printf("Serveur : message recu du client \n");
      if ((res=send(dsClient, &msgClient, sizeof(msgClient), 0)) < 0){
         perror("Serveur : pb envoi réponse au client");
         exit(1);
      }
      printf("Serveur : réponse envoyée au client \n");
   }
while(wait(0)!=-1){}

  /* Etape 7 : fermer la socket (lorsqu'elle n'est plus utilisée)*/
if (getpid()==pere)
   {
   if ((res=close(ds)) < 0)
      {
      perror("Serveur : pb fermeture socket");
      exit(1);
      }
   printf("Serveur : je termine\n");
   }
}
  
