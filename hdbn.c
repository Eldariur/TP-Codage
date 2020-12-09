#include<stdlib.h>
#include<stdio.h>
#include "hdbn.h"
#include "affichage.h"

void encodage_HDBn(int n, int taille, int entree[taille], int sortie[taille], int P[taille], int N[taille]){
	int last_altern = 1;
	int last_1_bit = 1;
	int nb_zero = 0;
	int viol = 0; //(boolean)

	switch(n){
			case 1 :
				for(int i = 0; i < taille; i++){
					if(entree[i] == 1){
						sortie[i] = entree[i] * last_altern;
						last_altern *= -1;
						last_1_bit = sortie[i];
						nb_zero = 0;
					} else {
							sortie[i] = 0;
					}
				}
			break;
			default:
				for(int i = 0; i < taille; i++){
					if(entree[i] == 1){
						sortie[i] = entree[i] * last_altern;
						last_altern *= -1;
						last_1_bit = sortie[i];
						nb_zero = 0;
					} else {
						nb_zero++;
						if(nb_zero == n + 1){
							if(viol > 0){
								sortie[i] = last_1_bit * -1;
								sortie[i-n] = last_1_bit * -1;
								last_altern *= -1;
							} else {
								sortie[i] = last_1_bit;
								viol++;
							}

							nb_zero = 0;
						} else {
							sortie[i] = 0;
						}
					}
				}
			break;
	}

	for(int i = 0; i < taille; i++){
		switch(sortie[i]){
			case 1:
				P[i] = 1;
				N[i] = 0;
			break;
			case -1:
				P[i] = 0;
				N[i] = 1;
			break;
			case 0:
				P[i] = N[i] = 0;
			break;
		}
	}
}

int n_dernier_sont_zero(int tab[], int i, int n){
	for(int j = 1; j <= n; j++){
		if(tab[i-j] != 0)
			return 0;
	}
	return 1;
}

void decodage_HDBn(int n, int taille, int entree[taille], int P[taille], int N[taille], int sortie[taille], int erreur[taille]){
	//on vérifie si il y a des erreur entre le code, le P et le N
	for(int i = 0; i < taille; i++){
		switch(entree[i]){
			case 	1:
				erreur[i] = 0;
				if(N[i] == 1)
					erreur[i] = 1;
				if(P[i] == 0)
					erreur[i] = 1;
				if(N[i] == 0 && P[i] == 0)
					erreur[i] = 1;
			break;
			case -1:
				erreur[i] = 0;
				if(P[i] == 1)
					erreur[i] = 1;
				if(N[i] == 0)
					erreur[i] = 1;
				if(N[i] == 0 && P[i] == 0)
					erreur[i] = 1;
			break;
			case 	0:
				erreur[i] = 0;
				if(P[i] == 1 || N[i] == 1)
					erreur[i] = 1;
			break;
		}
	}

	int viol = 0; //(boolean)

	//on décode tout ça
	switch(n){
		//HDB1
		case 1:
			for(int i = 0; i < taille; i++) {
				switch (entree[i]) {
					case 0:
						sortie[0] = 0;
					break;
					default:
						sortie[i] = 1;
					break;
				}
			}
		break;
		//HDBN tout sauf 1
		default:
			for(int i = 0; i < taille; i++) {
				printf("entree[%d]: %d\n", i, entree[i]);
				//Si le bit est un 0, alors tout va bien
				if(entree[i] == 0)
					sortie[i] = 0;
				else {
					//sinon, on fait des tests
					if(i >= n){
						if(viol > 0){
							if(n_dernier_sont_zero(entree, i, n-1) && entree[i-n] == entree[i]){
								sortie[i] = 0;
								sortie[i-n] = 0;
							} else {
								sortie[i] = 1;
							}
						} else {
							if(n_dernier_sont_zero(entree, i, n)){
								sortie[i] = 0;
								viol++;
							}	else {
								sortie[i] = 1;
							}
						}
					} else {
						sortie[i] = 1;
					}
				}
			}
		break;
	}
}

void testHDBN(){
	int code_entree[14] = {1,0,0,0,0,1,1,0,0,0,0,0,1,0};
	int code_sortie[14];
	int code_decode[14];
	int P[14];
	int N[14];
	int erreur[14];
	encodage_HDBn(HDBN3, 14, code_entree, code_sortie, P, N);
	decodage_HDBn(HDBN3, 14, code_sortie, P, N, code_decode, erreur);
	printf("Code de départ\t\t\t\t\t: ");
	afficher_tab_int(code_entree, 14);
	printf("Code en sortie du codeur\t\t\t: ");
	afficher_tab_int(code_sortie, 14);
	printf("P\t\t\t\t\t\t: ");
	afficher_tab_int(P, 14);
	printf("N\t\t\t\t\t\t: ");
	afficher_tab_int(N, 14);
	printf("Code en sortie du decodeur\t\t\t: ");
	afficher_tab_int(code_decode, 14);
	printf("Erreur de transmission (rien normalement)\t: ");
	afficher_tab_int(erreur, 14);
}
