#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "pow.h"
#include "hadamard.h"
#include "affichage.h"



void init_mat(int **mat,int taille){

   for(int i=0;i<taille;i++){
      for (int j = 0; j < taille; j++) {
         mat[i][j]=1;
      }
   }
}

/*calcule la taille de la matrice en fonction du nombre d'utilisateur*/
int taille_mat_selon_user(int nb_users){
   int c=0;/*compteur*/
   int p=0; /*puissance de 2 */
   int taille=pow1(2,p); /*dimension de la matrice d'hadamard*/

   if(nb_users == 1)
      return 1;
   else if(nb_users == 2)
      return 2;
   else if( nb_users == 3)
      return 4;
   else {
      while(c <= nb_users){

         if(taille<c){
            p++;
            taille = pow1(2,p);
         }

         c++;

      }

      return taille;
   }
}

void generer_hadamard(int ** hada, int n){

   // int H1[2][2]={ {1,1}, {1,-1} };
   int taille = n;
   int init=0,x1,y1;
   int cmpt=1,cmptX,cmptY,compt=2;


   if(n == 2)
      hada[1][1] = -1;
   else {

      while(cmpt < pow2(n) ){
         for(x1=0,cmptX=0; cmptX<compt ;x1+=taille,cmptX++){
            for(y1=0,cmptY=0; cmptY<compt ;y1+=taille,cmptY++){
               /* initialisation */
               /* cela sert à forcer un tour de boucle avec y1 = 0 pour taille et taille/2 */
               if(!init && y1 != 0){
                  y1 = 0;
                  cmptY--;
                  init = 1;
               }

               for (int i=0;i<taille;i++){

                  for(int j=0;j<taille;j++){
                     if(i+1>taille/2 && j+1>taille/2){
                        hada[i+x1][j+y1]*=-1;
                     } else {
                        hada[i+x1][j+y1]*=1;
                     }
                  }
               }

               if( x1==0 && y1 == 0 && !init)
               taille/=2;
            }
         }
         taille/=2;
         cmpt++;
         compt*=2;
      }
   }

}


int selecteur(int n){
   /*Cherche un place libre dans un tableau static entre l'indice 0 et l'indice n-1
   renvoie l'indice libre si il en trouve ou -1 si les indices sont tous plein*/

   /*int static permettant de savoir si c'est le premier appel de la fonction*/
   static int first_time = 0;
   static int tab[MAX_TAB];

   if(first_time == 0){
      for(int i = 0; i < MAX_TAB; i++)
         tab[i] = -1;
      first_time = 1;
   }

   int i;
   int case_test;

   //vérification si le tableau n'est pas plein entre les indices
   for(i = 0; i < n && tab[i] != -1; i++){}

   if(i == n)
      return -1;

   //on cherche une case vide
   while(1){
      case_test = rand()%n;
      if(tab[case_test] == -1){
         tab[case_test] = case_test;
         return case_test;
      }
   }
}

void testHadamard(){

   /* ========== DECLARATION ============= */

   int nb_utilisateur = 4;
	int taille = 4;
	int ** mat_hadamard;
	int ** codes_utilisateur;
	int num_sequence=0;
	int N = 3;

	srand(time(NULL));

   printf("Veuillez rentrer le nombre d'utilisateurs : ");

	scanf("%d",&nb_utilisateur);
	taille = taille_mat_selon_user(nb_utilisateur);

	/* ======================= */

	//mot envoyé par l'utilisateur
	int mot[N];
	//tableau contenant la sequence codée
	int sequence[taille];
	//tableau contenant le mot codé
	int mot_code[taille*N];

	//Géneration de la séquence aléatoire
	for(int i=0;i<N;i++){
		mot[i] = rand()%2;
	}

	printf("La séquence générée : ");
	for(int i=0;i<N;i++){
		printf(" %d ",mot[i]);
	}
	printf("\n");

	/* ========== ALLOCATION ============= */
	mat_hadamard = (int **) malloc(taille * sizeof(int *));
	if(NULL == mat_hadamard){
		perror("Pb malloc sur la matrice hadamard");
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < taille; ++i){
		mat_hadamard[i] = (int *) malloc(taille * sizeof(int));
		if(NULL == mat_hadamard[i]){
			perror("Pb malloc sur une ligne de la matrice hadamard");
			exit(EXIT_FAILURE);
		}
	}

	codes_utilisateur = malloc(nb_utilisateur * sizeof(int **));
	if(NULL == mat_hadamard){
		perror("Pb malloc sur le tableau contenant les codes des utilisateurs");
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < nb_utilisateur; ++i){
		codes_utilisateur[i] = malloc(N * taille * sizeof(int));
		if(NULL == mat_hadamard[i]){
			perror("Pb malloc sur une ligne du tableau contenant les codes des utilisateurs");
			exit(EXIT_FAILURE);
		}
	}
	/* ======================= */


	/* ========== Programme ============= */

	/*Création et affichage de la matrice de Hadamard de taille correspondante*/
	init_mat(mat_hadamard,taille);
	generer_hadamard(mat_hadamard,taille);
	printf("\nLa matrice Hadamard de taille %d est :\n", taille);
	afficher_hadamard(mat_hadamard,taille);

	/*Attribution d'une sequence pour chaque user*/
	for(int utilisateur = 0; utilisateur < nb_utilisateur; utilisateur++){

		/*selection d'une ligne libre au hasard*/
		if((num_sequence = selecteur(taille)) == -1){
			perror("probleme selection ligne dans matrice hadamard");
			exit(EXIT_FAILURE);
		}

		for(int i = 0; i < taille; i++){
			sequence[i]= mat_hadamard[num_sequence][i];
		}
		printf("Le user %d utilise la séquence n°%d : \n", utilisateur+1, num_sequence+1);
		afficher_tab_int(sequence, taille);

		/*Temporisation pour un meilleur affichage*/
		sleep(1);

		/*boucle de chiffrage du mot*/
		for(int i = 0; i < N; i++) {
			/*On repete N fois la sequence en appliquant le mot dessus*/
			for(int j = i*taille; j < (i * taille + taille); j++) {
				if(mot[i]){
					mot_code[j] = sequence[j % taille] == 1 ? 1 : 0;
				} else {
					mot_code[j] = -1 * sequence[j % taille] == 1 ? 1 : 0;
				}
			}
		}

		/*on ajoute le mot codé au tableau contenant tout les mots codés*/
		for(int i = 0; i < taille * N; i++)
			codes_utilisateur[utilisateur][i] = mot_code[i];

		printf("Voici la sequence codée : ");
		afficher_tab_int(mot_code, taille*N);

		afficher_separateur();

      recepteur(mot_code,sequence,taille,N);
	}

	/* ======================= */

	/* ========== LIBERATION ============= */
	for (int i = 0; i < taille; ++i)
	free(mat_hadamard[i]);
	free(mat_hadamard);
	for (int i = 0; i < nb_utilisateur; ++i)
	free(codes_utilisateur[i]);
	free(codes_utilisateur);
	/* ======================= */
}
