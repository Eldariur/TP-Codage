/* programme pow qui renvoie un type int */
int pow1(int n,int p){
   int x=n;
   for(int i=1;i<p;i++)
      x=x*n;

   return x;
}

/* programme qui retourne l'inverse de pow 2 ex: 8 => 3 ( 2³) */
int pow2(int n){
   int i;
   for(i=1;n!=2;i++){
      n/=2;
   }

   return i;
}
