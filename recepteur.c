#include <stdlib.h>
#include <stdio.h>
#include "affichage.h"
#include "recepteur.h"

/* mot_code : mot codé à déchiffrer
	sequence : sequence d'hadamard utilisée pour chiffrer le mot
	taille : taille de la sequence d'hadamard
	N : taille du mot originel
*/
int recepteur(int * mot_code, int * sequence, int taille, int N){

	int vrai = 1;
	int mot_original[N];
	/*Boucle de déchiffrage */

		printf("Je suis le recepteur. Je recois le mot code\n");

		printf("Dechiffrage du mot code en cours...\n");

		for(int i = 0; i < N; i++) {
			/*On repete N fois la sequence en appliquant le mot dessus*/
			for(int j = i*taille; j < (i * taille + taille); j++) {

				if(mot_code[j] != sequence[j % taille]){
					vrai = 0;
				}

			}

			if(vrai)
				mot_original[i] = 1;
			else
				mot_original[i] = 0;

			vrai = 1;
		}


		printf("Mot code dechiffre ! Le mot originel est : \n");
		afficher_tab_int(mot_original, N);

		printf("Fin du dechiffrage.\n");

		afficher_separateur();
      
}