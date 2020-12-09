#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "pow.h"
#include "aleatoire.h"


void M(char *s){
  printf("==============MARQUEUR %s=================\n",s);
}
void P(int n){
  for(int i=0;i<n;i++){
    puts("");
  }
}

// programme copié de hadamar.c
int taille_mat2(int nb_users){
  int c=0;/*compteur*/
  int p=0; /*puissance de 2 */
  int taille=pow1(2,p); /*dimension de la matrice d'hadamard*/

  if(nb_users == 1)return 1;
  else if( nb_users == 3)return 4;
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



/* But: Mettre en oeuvre un codeur Gold et JPL pour générer une séquence binaire aléatoire */
void mainAleat(){
  /* ========== DECLARATION ============= */
  int taille_seq = 20; // ex: taille de 20 à générer
  int long_mat = 2; // long par défaut
  int i,j,y,z,n=0;

  char car[20];
  char car2;
  int truc;
  int continu = 1;


  /* ========== Initialisation ============= */
  /*
      Pour avoir une séquence de longueur n (ex: 20) on choisi de ne garder que les n premiers bits
      de la séquence générée au lieu de prendre aléatoirement une séquence de n bits dedans
      cela nous évite de garder en mémoire un tableau de taille 3*7*31 par exemple
      et également d'avoir une taille fixe de tableau
  */
  puts( " ====================== DEBUT DE PROGRAMME ========================= \n" ) ;
  printf("Quel est la longueur de la séquence à générée : \n");
  scanf("%d", &taille_seq);
  /* variables */
  int long_seq = taille_seq;
  char seq_gene[long_seq];
  char poly_gene[20];// ex: polynôme générateur 01001

  for (i = 0; i < long_seq; i++) {
    seq_gene[i]='0';
  }

//  while(car != 'N'){
//puts("\nSouhaitez-vous continuer ?[Y:N]");

  while(continu == 1){
    int choix=0;

    printf("Quel est le polynôme générateur (ex:01001): \n");
    scanf("%s", poly_gene);

    long_mat = strlen(poly_gene);
    char seq[long_mat];

    printf("Quel est le registre d'initialisation: \n");
    scanf("%s", seq);
    printf("longueur de taille : %d à générer\n",long_mat);

    // /* ======================= */

    //test affichage
    puts("tab générateur: ");
    for(i=0;i<long_mat;i++){
      printf("%c |",poly_gene[i]);
    }
    P(2);
    //tempo = 01001
    //seq   = 11111

    /* boucle tant que 11111 n'est pas réapparu */
    for(i=0;i<long_seq;i++){ //long_seq-1
        n=0;
        printf("seq_gene[%d]=%d + %d \n",i,seq[long_mat-1]-'0',seq_gene[i]-'0');
        seq_gene[i]=( ((seq[long_mat-1]-'0') + (seq_gene[i]-'0')) %2)+'0';
        //test affichage
        P(1);
        for(z=0;z<long_mat;z++){
          printf("%c|",seq[z]);
        }
        P(1);
        for(y=long_mat-1;y!=-1;y--){ //on boucle à l'envers pour ne pas regarder ce qu'on vient de modifier
          if(poly_gene[y] == '1'){
            n+=seq[y]-'0';
          }
          if(y == 0){
            //on ne fait rien
          }
          else{
            seq[y]=seq[y-1];
          }
        }
        //printf("n=%d\n",n );
        n=n%2;
        seq[0]=n+'0';

        //printf("le bit sera : %d\n",n );

    }// fin boucle principale

    puts("\nLa séquence générée est :\n");
    for (i = 0; i < long_seq; i++) {
      printf("%c|",seq_gene[i] );
    }

    puts("\nVoulez vous continuer ? [Y:N]");
    scanf("%s",&car2 );

    while(choix == 0 && continu == 1){
      switch(car2){
        case 'Y':
          choix=1;
          break;
        case 'N':
          choix=1;
          continu=0;
          break;
        default :
          puts("\nCaractère non reconnu: [Y:N]");
          scanf("%s",&car2 );
          break;
      }//fin switch
    }

}//fin while



  puts( "\n====================== FIN DE PROGRAMME ========================= \n" ) ;
}
