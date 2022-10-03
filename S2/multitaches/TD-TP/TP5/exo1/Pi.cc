#include <stdlib.h>
#include <sys/types.h>
#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>//perror
#include <cstring>
#include <unistd.h>
using namespace std;

// la commande ipcs sert à regarder les processus et sémaphores actifs.

/** taille du message (en nombre de caractères)
 */
#define TAILLE_MSG 32 

int main(int argc, char * argv[]){

  /*
    Etapes: 
      - Pctrl crée la file et attend jusqu'à recevoir une demande d'accès (sous forme de numproc dans un struct ?)
      - send du Pi au Pctrl pour la demande d'accès à la donnée partagée (numproc)
      - send du Pctrl au Pi pour renvoyer la donnée partagée à Pi
      - send du Pi au Pctrl qui rentre son message dans la file
  */
enum m_type{
  valRetour = 1,
  Acces,
};

typedef struct {
    long mtype; // type de la struct : demande d'accès / valeur de retour
    int numproc ; // pid du Pi
  } demandeAcces;

typedef struct {
    int mtype; // type de la struct : demande d'accès / valeur de retour
    char msg[TAILLE_MSG] ; // message
  } msgBuf;

  // pid_t nump = getpid();

  if (argc!=3) {
    cout<<"Nbre d'args invalide, utilisation :"<< endl;
    cout << argv[0] << " fichier-pour-cle-ipc entier-pour-cle-ipc"<< endl;
    exit(0);
  }
	
  key_t cle=ftok(argv[1], atoi(argv[2]));

  if (cle==-1) {
    perror("Erreur ftok : ");
    exit(2);
  }

  cout << "clé créée" << endl;
    
  int msgid = msgget(cle, 0666);
  if(msgid==-1) {
    perror("erreur acquisition file : ");
    exit(2);
  }
  
  cout << "file acquise" << endl;
  
  demandeAcces demande;
  demande.numproc = getpid();
  cout<<"pid du Pi actuel : "<<demande.numproc<<endl;
  // message à envoyer
  msgBuf msg;
  char message[TAILLE_MSG];
  cout<<"Entrez un message à envoyer à Pctrl (" << TAILLE_MSG << " caractères max):"<<endl;
  cin>>message;
  //demande d'autorisation à Pctrl
  if (msgsnd(msgid, (void *) &demande, sizeof(demande.numproc), 0) < 0){
      perror("erreur depot sur la file");
      exit(2);
  }
  cout<<"demande autorisation à la file acceptée"<<endl;
  // réception donnée partagée
  if (msgrcv(msgid, (void *) &msg, sizeof(msg.msg), demande.numproc , 0) < 0){
      perror("erreur récup message sur la file");
      exit(2);
  }
  cout<<"var à modifier récupérée de la file"<<endl;

  // modif de la var partagée puis renvoi
  strcpy(msg.msg,message);
  if (msgsnd(msgid, (void *) &msg, strlen(msg.msg), 0) < 0){
      perror("erreur depot sur la file");
      exit(2);
  }

  return 0;
}
