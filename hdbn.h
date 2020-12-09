#define M 50
#define ARITHMETIQUE 1
#define HDBN1 1
#define HDBN2 2
#define HDBN3 3
#define HDBN4 4

void encodage_HDBn(int n, int taille, int entree[], int sortie[], int P[], int N[]);
void decodage_HDBn(int n, int taille, int entree[], int P[], int N[], int sortie[], int erreur[]);
void testHDBN();
