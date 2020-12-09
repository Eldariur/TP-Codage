#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include "hdbn.h"
#include "hadamard.h"
#include "affichage.h"
#include "recepteur.h"
#include "canal.h"


int main(){
	/* ========== DECLARATION ============= */
	int nb_utilisateur = 4;
	int taille = 4;
	int ** mat_hadamard;
	int ** codes_utilisateur;
	int num_sequence=0;
	int N = 3;

	srand(time(NULL));


	/* ======================= */

	/* ========== Initialisation ============= */
	puts( " ====================== DEBUT DE PROGRAMME ========================= \n" ) ;

	printf("(pour tout passer et aller a HDBn, entrer -1)\n");
	printf("Veuillez rentrer le nombre d'utilisateurs : ");

	scanf("%d",&nb_utilisateur);
	if(nb_utilisateur == -1){
		testHDBN();
		exit(EXIT_SUCCESS);
	}
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


	puts( "\n ====================== FIN DE PROGRAMME ========================= \n" ) ;

	return 0;
}
