#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "pow.h"
#include "aleatoire.h"
#include "affichage.h"
#include "recepteur.h"

char xor(char c1, char c2){
   char _c1 = c1 == '1' ? '0' : '1';
   char _c2 = c2 == '1' ? '0' : '1';
   char c1_c2 = c1 == '1' && _c2 == '1' ? '1' : '0';
   char _c1c2 = _c1 == '1' && c2 == '1' ? '1' : '0';
   return c1_c2 == '1' || _c1c2 == '1' ? '1' : '0';
}

char * generer_code_longeur_maximale(char registre_initial[], char polynome_generateur[], int longeur_sequence){
   int longeur_registre_init = strlen(registre_initial);
   int longeur_registre_totale = longeur_registre_init*longeur_registre_init-1;
   char registres[longeur_registre_totale][longeur_registre_init];
   char resultat[longeur_registre_totale];
   resultat[0] = registre_initial[longeur_registre_init - 1];
   char * retour = malloc(sizeof(char) * longeur_sequence);
   strcpy(registres[0], registre_initial);

   char bits_a_comparer[longeur_registre_init];
   strcpy(bits_a_comparer, polynome_generateur);

   char res_xor;
   int ou_commencer;

   for(int i = 1; i < longeur_registre_totale; i++){
      //on recopie la ligne du dessus en décalant de 1
      for(int j = 1; j < longeur_registre_init; j++){
         registres[i][j] = registres[i-1][j-1];
      }

      //initialisation du premier bit a XOR
      for (int j = 0; j < longeur_registre_init; j++) {
         if(bits_a_comparer[j] != '0'){
            res_xor = registres[i-1][j];
            ou_commencer = j;
            break;
         }
      }

      for(int j = ou_commencer+1; j < longeur_registre_init; j++) {
         if(bits_a_comparer[j] != '0'){
            res_xor = xor(res_xor, registres[i-1][j]);
         }
      }

      registres[i][0] = res_xor;
      resultat[i] = registres[i][longeur_registre_init-1];
   }

   for(int i = 0; i < longeur_sequence; i++) {
      retour[i] = resultat[i];
   }
   return retour;
}

void testCodeLongeurMax(){
   afficher_separateur();

   char registre_initial[20];
   char polynome_generateur[20];
   char * sequence_generee;
   int longeur_sequence;

   printf("Registre d'initialisation : ");
   scanf("%s", registre_initial);

   printf("Polynome Generateur (ex: 1+x+x3 => 1101) : ");
   scanf("%s", polynome_generateur);

   printf("Longeur de la séquence a générer :");
   scanf("%d", &longeur_sequence);

   sequence_generee = generer_code_longeur_maximale(registre_initial, polynome_generateur, longeur_sequence);
   printf("Séquence générée : %s\n", sequence_generee);
   free(sequence_generee);
   afficher_separateur();
}

void testCodeurDeGold(){
   char registre_initial[20];
   char polynome_generateur[20];
   char * sequence_generee1;
   char * sequence_generee2;
   int longeur_sequence;

   afficher_separateur();
   printf("Creation du premier code a Longeur Maximale :\n");
   printf("Registre d'initialisation : ");
   scanf("%s", registre_initial);
   printf("Polynome Generateur (ex: 1+x+x3 => 1101) : ");
   scanf("%s", polynome_generateur);
   printf("Longeur de la séquence a générer :");
   scanf("%d", &longeur_sequence);
   sequence_generee1 = generer_code_longeur_maximale(registre_initial, polynome_generateur, longeur_sequence);

   afficher_separateur();
   printf("Creation du deuxieme code a Longeur Maximale :\n");
   printf("Registre d'initialisation : ");
   scanf("%s", registre_initial);
   printf("Polynome Generateur (ex: 1+x+x3 => 1101) : ");
   scanf("%s", polynome_generateur);
   sequence_generee2 = generer_code_longeur_maximale(registre_initial, polynome_generateur, longeur_sequence);

   printf("Séquence générée 1 : %s\n", sequence_generee1);
   printf("Séquence générée 2 : %s\n", sequence_generee2);

   afficher_separateur();
   printf("Génération d'un code de Gold de longeur %d\n", longeur_sequence);

   char code_gold[longeur_sequence];

   for(int i = 0; i < longeur_sequence; i++){
      code_gold[i] = ((sequence_generee1[i] - '0' + sequence_generee2[i] - '0') % 2) + '0';
   }

   printf("Code gold obtenu : %s\n", code_gold);

   free(sequence_generee1);
   free(sequence_generee2);
   afficher_separateur();
}

void testCodeurJPL(){
   char registre_initial[20];
   char polynome_generateur[20];
   char * sequence_generee1;
   char * sequence_generee2;
   char * sequence_generee3;
   int longeur_sequence;

   afficher_separateur();
   printf("Creation du premier code a Longeur Maximale :\n");
   printf("Registre d'initialisation : ");
   scanf("%s", registre_initial);
   printf("Polynome Generateur (ex: 1+x+x3 => 1101) : ");
   scanf("%s", polynome_generateur);
   printf("Longeur de la séquence a générer :");
   scanf("%d", &longeur_sequence);
   sequence_generee1 = generer_code_longeur_maximale(registre_initial, polynome_generateur, longeur_sequence);

   afficher_separateur();
   printf("Creation du deuxieme code a Longeur Maximale :\n");
   printf("Registre d'initialisation : ");
   scanf("%s", registre_initial);
   printf("Polynome Generateur (ex: 1+x+x3 => 1101) : ");
   scanf("%s", polynome_generateur);
   sequence_generee2 = generer_code_longeur_maximale(registre_initial, polynome_generateur, longeur_sequence);

   afficher_separateur();
   printf("Creation du troisieme code a Longeur Maximale :\n");
   printf("Registre d'initialisation : ");
   scanf("%s", registre_initial);
   printf("Polynome Generateur (ex: 1+x+x3 => 1101) : ");
   scanf("%s", polynome_generateur);
   sequence_generee3 = generer_code_longeur_maximale(registre_initial, polynome_generateur, longeur_sequence);

   printf("Séquence générée 1 : %s\n", sequence_generee1);
   printf("Séquence générée 2 : %s\n", sequence_generee2);
   printf("Séquence générée 2 : %s\n", sequence_generee3);

   afficher_separateur();
   printf("Génération d'un code JPL de longeur %d\n", longeur_sequence);

   char code_JPL[longeur_sequence];

   for(int i = 0; i < longeur_sequence; i++){
      code_JPL[i] = ((sequence_generee1[i] - '0' + sequence_generee2[i] - '0') % 2) + '0';
   }

   for(int i = 0; i < longeur_sequence; i++){
      code_JPL[i] = ((code_JPL[i] - '0' + sequence_generee3[i] - '0') % 2) + '0';
   }

   printf("Code JPL obtenu : %s\n", code_JPL);

   free(sequence_generee1);
   free(sequence_generee2);
   free(sequence_generee3);
   afficher_separateur();
}

void testAleat(){
   afficher_separateur();
   printf("Test a effectuer :\n");
	printf("1 - Génération d'un code a Longeur Maximale\n");
	printf("2 - Génération d'un codeur de Gold\n");
	printf("3 - Mise en oeuvre d'un codeur JPL\n");
   int choix = 0;
   do {
      scanf("%d", &choix);
   } while(choix < 1 || choix > 3);

   switch(choix){
		case 1: testCodeLongeurMax();
			exit(EXIT_SUCCESS);
		case 2: testCodeurDeGold();
			exit(EXIT_SUCCESS);
		case 3: testCodeurJPL();
			exit(EXIT_SUCCESS);
	}
}
