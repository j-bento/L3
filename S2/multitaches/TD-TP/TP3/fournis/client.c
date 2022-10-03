#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include <sys/stat.h>

#define MAX_BUFFER_SIZE 146980

int main(int argc, char *argv[]) {

  if (argc != 4){
    printf("utilisation : client ip_serveur port_serveur nom_fichier\n\
    Remarque : le parametre nom_fichier correspond au nom d'un fichier existant dans le répertoire emission\n");
    exit(0);
  }
  int res;
  int taille_fich=strlen(argv[3]);
  char *nom_fich=(char*) malloc(sizeof(char)*taille_fich);
  strcpy(nom_fich,argv[3]);
  int taille_nom_fich=strlen(nom_fich);

  /* etape 1 : créer une socket */   
  int ds = socket(PF_INET, SOCK_STREAM, 0);//SOCK_STREAM pour le tcp, SOCK_DGRAM pour l'udp
  if (ds == -1){
    perror("Client : pb creation socket");
    exit(1); // je choisis ici d'arrêter le programme car le reste
	     // dépendent de la réussite de la création de la socket.
  }
  printf("Client : creation de la socket réussie \n");
  /* etape 2 : designer la socket du serveur */
  struct sockaddr_in sockServ ;
  sockServ.sin_family = AF_INET ;
  sockServ.sin_addr.s_addr = inet_addr(argv[1]) ; // adresse IP serveur
  sockServ.sin_port = htons( (short) atoi(argv[2])) ; // exemple "3430", port serveur
  socklen_t lgA = sizeof(struct sockaddr_in) ;
  /* etape 3 : demander une connexion */
  if((res=connect(ds,(struct sockaddr*)&sockServ,lgA)) < 0){
     perror("Client : pb demande connexion");
     exit(1);
  }
   printf("Client : demande connexion effectuée\n");
  /* etape 4 : envoi de fichier : attention la question est générale. Il faut creuser pour définir un protocole d'échange entre le client et le serveur pour envoyer correctement un fichier */

  int totalSent = 0; // variable pour compter le nombre total d'octet effectivement envoyés au serveur du début à la fin des échanges.

  if((res = send(ds, &taille_nom_fich, sizeof(int), 0)) < 0){
         perror("Client : pb envoi taille du nom du fich");
      }
  
  printf("Client : taille du nom du fich envoyé au serveur\n"); 

  if((res = send(ds, nom_fich, taille_nom_fich, 0)) < 0){
         perror("Client : pb envoi nom fich");
      }
  
  printf("Client : nom fich envoyé au serveur\n"); 

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
      return octets_envoyes;
  }
 
  /* le bout de code suivant est une lecture de contenu d'un fichier dont le nom est passé en paramètre.
     - pour lire un fichier, il faut l'ouvrir en mode lecture
     - la lecture se fait par blocs d'octets jusqu'à la fin du fichier.
     - la taille d'un bloc est définie par la constante MAX_BUFFER_SIZE que vous pouvez modifier.

     Le code est à compléter pour mettre en place l'envoi d'un fichier.
  */

  // construction du nom du chemin vers le fichier
  char* filepath = malloc(strlen(nom_fich) + 16); // ./emission/+nom fichier +\0
  filepath[0] = '\0';
  strcat(filepath, "./emission/");
  strcat(filepath, nom_fich);

  printf("Client : je vais envoyer %s\n", filepath);

  // obtenir la taille du fichier
  struct stat attributes;
  if(stat(filepath, &attributes) == -1){
    perror("Client : erreur stat ");
    free(filepath);
    exit(1);
  }

  int file_size = attributes.st_size; // cette copie est uniquement informer d'où obtenir la taille du fichier.
  
  printf("Client : taille du fichier : %d octets\n", file_size);
  if((res=send(ds,&file_size,sizeof(int),0)) < 0){
    perror("Client : pb envoi taille fichier ");
    free(filepath);
    exit(1);
  }
  printf("Client : taille fichier envoyée\n");
  
  // lecture du contenu d'un fichier
  FILE* file = fopen(filepath, "rb");
  if(file == NULL){
    perror("Client : erreur ouverture fichier \n");
    free(filepath);
    exit(1);   
  }
  free(filepath);

  int total_lu = 0;
  char buffer[MAX_BUFFER_SIZE];
  while(total_lu < file_size){
    
    size_t read = fread(buffer, sizeof(char), MAX_BUFFER_SIZE, file);
    if(read == 0){
      if(ferror(file) != 0){
        perror("Client : erreur lors de la lecture du fichier \n");
        fclose(file);
        exit(1);
      }else{
        printf("Client : arrivé a la fin du la lecture du fichier\n");// fin du fichier
	break;
      }
    }
    printf("Client : j'ai lu un bloc du fichier \n");  
    if ( (res=sendTCP(ds,buffer,strlen(buffer))) < 0){
      perror("Client : Problème lors de l'envoi du bloc");
      fclose(file);
      exit(1);
    }
    else{
      printf("Client : Bloc envoyé\n");
      totalSent += 
      total_lu += read;
    }
  }

  // fermeture du fichier
  fclose(file); 
  free(nom_fich);
  printf("Client : j'ai lu au total : %d octets \n", total_lu);  
 
 
  printf("Client : c'est fini\n");
}
