#include <stdio.h>//perror
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>//close
#include <stdlib.h>
#include <string.h>


#define MAX_BUFFER_SIZE 146980


int main(int argc, char *argv[])
{
  /* etape 0 : gestion des paramètres si vous souhaitez en passer */
  if (argc != 2){
    printf("utilisation : %s port_serveur\n", argv[0]);
    exit(1);
  }
  // char nom_fich[250];
  // sscanf (argv[2],"%s",nom_fich);
  int res,dsClient;  

  /* etape 1 : creer une socket d'écoute des demandes de connexions*/
  int ds = socket(PF_INET, SOCK_STREAM, 0); //SOCK_STREAM pour le tcp, SOCK_DGRAM pour l'udp
  if (ds == -1){
    perror("Serveur : pb creation socket");
    exit(1); // je choisis ici d'arrêter le programme car le reste
	     // dépendent de la réussite de la création de la socket.
  }
  printf("Serveur : creation de la socket réussie \n");

  /* etape 2 : nommage de la socket */
  struct sockaddr_in adServeur;
  adServeur.sin_family=AF_INET;
  adServeur.sin_addr.s_addr=INADDR_ANY;
  adServeur.sin_port=htons((short) atoi(argv[1])); //port serveur passé en argument 1

  if( (res=bind(ds,(struct sockaddr*) &adServeur,sizeof(adServeur))) < 0){
     perror("Serveur : pb nommage socket");
     exit(1);
  }
  printf("Serveur : nommage de la socket réussie \n");

  /* etape 3 : mise en ecoute des demandes de connexions */
  if((res=listen(ds,3)) < 0){
     perror("Serveur : pb passage mode ecoute");
     exit(1);
  }
  printf("Serveur : passage mode ecoute\n");

  /* etape 4 : plus qu'a attendre la demande d'un client */
  struct sockaddr_in adClient;
  socklen_t lgA=sizeof(struct sockaddr_in);
  int taille_nom_fich;
  int taille_fich;

  if((dsClient=accept(ds,(struct sockaddr *) &adClient,&lgA)) < 0)
   {
     perror("Serveur : pb acceptation demande connexion client");
     exit(1);
   }
   printf("Serveur : demande connexion client acceptée\n");

  int totalRecv = 0; // un compteur du nombre total d'octets recus d'un client
  char nom_fich[100];
  if ((res=recv(dsClient,&taille_nom_fich,sizeof(int),0)) < 0){ //reception taille nom fichier
      perror("Serveur : pb reception taille nom fich");
      exit(1);
      }
  printf("Serveur : taille nom fichier recue\n");
  if ((res=recv(dsClient,nom_fich,sizeof(nom_fich),0)) < 0){ //reception taille nom fichier
      perror("Serveur : pb reception nom fich");
      exit(1);
      }
  printf("Serveur : taille nom fichier recue\n");
  // taille_nom_fich=(int) strlen(nom_fich);
  printf("Taille nom fichier: %i, Nom: %s\n",taille_nom_fich,nom_fich);
  
  char* filepath = (char*) malloc(sizeof(char)*(taille_nom_fich+16));
  strcpy(filepath,"./reception/"); // cette ligne n'est bien-sur qu'un exemple et doit être modifiée : le nom du fichier doit être reçu.
  strcat(filepath,nom_fich);


  if ((res=recv(dsClient,&taille_fich,sizeof(int),0)) < 0){ //reception taille fichier
      perror("Serveur : pb reception taille fich");
      exit(1);
      }
  printf("Taille du fichier: %i\n",taille_fich);

  // On ouvre le fichier dans lequel on va écrire
  FILE* file = fopen(filepath, "wb");
  if(file == NULL){
    perror("Serveur : erreur ouverture fichier ");
    exit(1);  
  }

  char buffer[MAX_BUFFER_SIZE];// ="ceci est un exemple de contenu a ecrire dans un fichier\n";
  size_t written=0;
  while(totalRecv<taille_fich){
    if ( (res=recv(dsClient,buffer,sizeof(buffer),0)) < 0){
        perror("Serveur : Problème réception buffer ");
        exit(1);
    }
    written = fwrite(buffer, sizeof(char), strlen(buffer), file);
    totalRecv += res;
    if(written < strlen(buffer)){  // cette ligne est valide uniquement pour ce simple exemple
      perror("Serveur : Erreur a l'ecriture du fichier \n");
      fclose(file); 
    }

  }

  printf("Serveur : ecriture dans fichier reussie. Vous pouvez vérifier la création du fichier et son contenu.\n");
  // fermeture du fichier
  fclose(file);
  // free(nom_fich);
  free(filepath);
  printf("Serveur : c'est fini\n");
}








