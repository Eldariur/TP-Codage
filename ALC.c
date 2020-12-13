#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


int main(int argc, char * argv[]){

puts( " ====================== DEBUT DE PROGRAMME ========================= \n" ) ;
  
  starttask(T1);
  starttask(T2);
  V(mutexV);
  while(1){
    opfond();
    P(mutexV,NULL);
    AccessV();
    V(mutexV);
  }

  puts( "\n ====================== FIN DE PROGRAMME ========================= \n" ) ;
}
