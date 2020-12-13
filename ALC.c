#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 20

/* CONDITIONS */
pthread_cond_t cond_jpl = PTHREAD_COND_INITIALIZER; /* Création de la condition */
pthread_cond_t cond_hada = PTHREAD_COND_INITIALIZER; /* Création de la condition */
pthread_cond_t cond_hdbn = PTHREAD_COND_INITIALIZER; /* Création de la condition */

/* MUTEX */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; /* Création du mutex */

void* threadHadamard (void* arg);
void* threadJPL (void* arg);
void* threadActif (int nb);
void* threadHDBn (void* arg);
void* threadMain (void* arg);

int etat = 0; //0 =>UNKNOWN 1=>INITIATED 2=>ACTIVE
char choix;
int nb=0;


void unknown(){
  //printf("\nL'état est UNKNOWN\n");
  etat = 0;
}

void initiated(){
  //printf("\nL'état est INITIATED\n");
  etat = 1;
}

void active(){
  //printf("\nL'état est ACTIVE\n");
  etat = 2;
}

int main (void)
{

	pthread_t monThreadMain;
	pthread_t monThreadHadamard;
	pthread_t monThreadActif;
	pthread_t monThreadJPL;
	pthread_t monThreadHDBn;

	pthread_create (&monThreadMain, NULL, threadMain, (void*)NULL);
	pthread_create (&monThreadActif, NULL, threadActif, (void*)NULL);
	pthread_create (&monThreadJPL, NULL, threadJPL, (void*)NULL);
	pthread_create (&monThreadHDBn, NULL, threadHDBn, (void*)NULL);
	pthread_create (&monThreadHadamard, NULL, threadHadamard, (void*)NULL); /* Création des threads */

	pthread_join (monThreadMain, NULL);
	pthread_join (monThreadHadamard, NULL);
	pthread_join (monThreadHDBn, NULL);
	pthread_join (monThreadActif, NULL);
	pthread_join (monThreadJPL, NULL);

	return 0;
}


/* ======================== THREAD ===========================*/
void* threadMain (void* arg)
{
	// printf("\n\tQuel thread souhaitez vous regarder ?\nPour Hadamard -> H\nPour JPL -> J\nPour HDBn -> A\n");
	// scanf("%c",&choix);
  nb = 0;
	threadActif(nb);
	pthread_exit(NULL); /* Fin du thread */
}

void* threadHadamard (void* arg)
{
	while(1) /* Boucle infinie */
	{
		pthread_cond_wait (&cond_hada, &mutex); /* En attente de la condition qui me dit d'activer mon programme */
    active();
		printf("\nJe suis le thread hadamard\n");
    mainHada();
    initiated();
		sleep(2);

	}

	pthread_exit(NULL); /* Fin du thread */
}


void* threadHDBn (void* arg)
{
	while(1) /* Boucle infinie */
	{
		pthread_cond_wait (&cond_hdbn, &mutex); /* En attente de la condition qui me dit d'activer mon programme */
    active();
		printf("\nJe suis le thread HDBn\n");
    mainHDBN();
    initiated();
		sleep(2);
	}

	pthread_exit(NULL); /* Fin du thread */
}

void* threadJPL (void* arg)
{
	while(1) /* Boucle infinie */
	{
		pthread_cond_wait (&cond_jpl, &mutex); /* En attente de la condition qui me dit d'activer mon programme */
    active();
		printf("\nJe suis le thread JPL\n");
		mainAlea();

    initiated();
		sleep(2);
	}

  printf("\nJe sors du thread JPL\n");
	pthread_exit(NULL); /* Fin du thread */
}


void* threadActif (int nb)
{
  initiated();
	while(1) /* Boucle infinie */
	{

    if( etat == 1){
        printf("\n\tQuel est mon choix ?\nPour Hadamard -> H\nPour HDBn -> S\nPour JPL -> J\n");
    		scanf("%c",&choix);
    		switch (choix) {
    			case 'H':
    				printf("Mon choix est Hadamard\n");
            active();
    				pthread_cond_signal (&cond_hada); /* En attente de la condition qui me dit d'activer mon programme */
            pthread_exit(NULL); /* Fin du thread */
    				break;
    			case 'S':
    				printf("Mon choix est HDBN\n");
            active();
    				pthread_cond_signal (&cond_hdbn); /* En attente de la condition qui me dit d'activer mon programme */
            pthread_exit(NULL); /* Fin du thread */
    				break;
    			case 'J':
    				printf("Mon choix est JPL\n");
            active();
    				pthread_cond_signal (&cond_jpl); /* En attente de la condition qui me dit d'activer mon programme */
            pthread_exit(NULL); /* Fin du thread */
    				break;
    			default:
    				printf("Caractère non reconnu\n");
            //pthread_exit(NULL); /* Fin du thread */
    				break;
    		}
	   }
     sleep(2);
 


	pthread_exit(NULL); /* Fin du thread */
}
