#include <stdlib.h>
#include <sys/types.h>
#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>//perror
#include <cstring>
#include <unistd.h>
using namespace std;

// la commande ipcs sert à regarder les processus et sémaphores actifs

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
  Acces = 1,
  valRetour,
};

typedef struct {
    long mtype; // type de la struct : demande d'accès / valeur de retour
    int numproc ; // pid du Pi
  } demandeAcces;

typedef struct {
    long mtype; // type de la struct : demande d'accès / valeur de retour
    char msg[TAILLE_MSG] ; // message
  } msgBuf;
  pid_t nump = getpid();

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
    
  int msgid = msgget(cle, IPC_CREAT|IPC_EXCL|0666);// 666 : lecture et écriture pour soi, le groupe et les autres
  if(msgid==-1) {
    perror("erreur msgget : ");
    exit(2);
  }
  
  cout << "file créée" << endl;
  msgBuf msg;
  demandeAcces demande;


// Etape 1 : Recevoir demandes d'accès des processus 
  if (msgrcv(msgid, (void *) &demande, sizeof(demande.numproc), Acces , 0) < 0){
      perror("erreur depot sur la file");
      exit(2);
  }
  cout<<"pid du Pi : "<<demande.numproc<<endl;
  cout<<"pid du Pctrl : "<<nump<<endl;

  // Etape 2 : Renvoi donnée à modifier pour Pi
  if (msgsnd(msgid, (void *) &msg, sizeof(msg.msg), 0) < 0){
      perror("erreur depot sur la file");
      exit(2);
  }
  cout<<"donnée déposée sur la file pour Pi"<<endl;
  msgBuf msgRetour = (msgBuf){.mtype = demande.numproc};
  // Etape 3 : Recevoir message processus
  // if (msg.mtype==)
  if (msgrcv(msgid, (void *) &msgRetour.msg, sizeof(msgRetour.msg), valRetour , 0) < 0){
      perror("erreur depot sur la file");
      exit(2);
  }
  cout << "déposé sur la file" << endl;
  char message[TAILLE_MSG];
  strcpy(message,msgRetour.msg);
  cout << "Le message écrit : "<<message<<endl;
  
  return 0;
}
