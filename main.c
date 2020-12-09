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
#include "aleatoire.h"


int main(){
		puts( " ====================== DEBUT DE PROGRAMME ========================= \n" ) ;

	printf("Code a éxecuter :\n");
	printf("1 - Code d'étalement\n");
	printf("2 - Codeur HDBn\n");
	printf("3 - Générateur pseudo-aléatoire\n");
	printf("4 - Agent Life Cycle\n");
	int choix = 0;
	do {
		scanf("%d", &choix);
	} while(choix < 1 || choix > 4);

	switch(choix){
		case 1: testHadamard();
			exit(EXIT_SUCCESS);
		case 2: testHDBN();
			exit(EXIT_SUCCESS);
		case 3: testAleat();
			exit(EXIT_SUCCESS);
		case 4: printf("WIP\n");
			exit(EXIT_SUCCESS);
	}

	puts( "\n ====================== FIN DE PROGRAMME ========================= \n" ) ;

	return 0;
}
