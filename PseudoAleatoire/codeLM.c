#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define ENTREE_SORTIE_REGISTRE 4

/*
*   colonne 0 : Sortie XOR
*   colonne 1 : Entree XOR
*   colonne 2 : Sortie Etage
*   colonne 3 : Entree Etage
*/

/*
*   ligne 0:        Premier étage du registre
*   ligne 1..n-2:   N ième étages du registre
*   ligne n-1       Dernier étage du registre -> sortie
*/

void afficherTable(int ** table1, int nb_etages){

  int i, j;

  for(i = 0; i < nb_etages; i++){
    for(j = 0; j < ENTREE_SORTIE_REGISTRE; j++){
      printf("%i ",table1[i][j]);
    }
    printf("\n");
  }
}

int ** creerTableEtages(int nombre_etages){

  /* Créer une table à n étages pour un registre */

  int i;
  int ** table = (int **) malloc(sizeof(int*)*nombre_etages);
  for(i=0;i<nombre_etages;i++){
    table[i] = (int *) malloc(sizeof(int)*ENTREE_SORTIE_REGISTRE);
  }
  return table;

}

void initRegistre(int ** table, int nombre_etages){

  /* Initialise la table du registre */

  int i, j;
  for(i = 0; i < nombre_etages; i++){
    for(j = 0; j < ENTREE_SORTIE_REGISTRE; j++){
      if(j == 3)
        table[i][j] = 1;
      else if(i == nombre_etages - 1 && j == 1)
        table[i][j] = -1;
      else
        table[i][j] = 0;
    }
  }
}

void copieTable(int ** table1, int ** table2, int nombre_etages){

  /* Copie une table à l'identique */

  int i, j;
  for(i = 0; i < nombre_etages; i++){
    for(j = 0; j < ENTREE_SORTIE_REGISTRE; j++){
      table1[i][j] = table2[i][j];
    }
  }
}

void actionDecalage(int ** table, int ** table_copie, int nombre_etages, int * sortie){

  /* Actionne le registre pour 1 décalage */

  int i, j;

  for(i = 0; i < nombre_etages; i++){

      if(i == 0){
        table[i][0] = table[i][1] ^ table[i][2];
        table[i][2] = table[i][3];
        table[i][3] = table_copie[i][0];
        table[i+1][3] = table_copie[i][2];
      }else if( i == nombre_etages - 1){
        table[i-1][1] = table[i][0];
        (*sortie) = table[i][2];
        table[i][0] = table[i][2];
        table[i][2] = table_copie[i][3];
      }else{
        table[i-1][1] = table[i][0];
        table[i][0] = table[i][1] ^ table[i][2];
        table[i+1][3] = table[i][2];
        table[i][2] = table_copie[i][3];
      }
    }
}

void actionRegistre(int nb_etages){

  srand(time(NULL));

  int i,j;
  int sortie;
  int ** table1 = creerTableEtages(nb_etages);
  int ** table2 = creerTableEtages(nb_etages);

  initRegistre(table1,nb_etages);
  initRegistre(table2,nb_etages);
  copieTable(table2,table1,nb_etages);

  printf("\nSortie du registre: \n\n");

  for(i = 0; i < (pow(2,nb_etages) - 1); i++){

    actionDecalage(table1, table2, nb_etages, &sortie);
    copieTable(table2,table1,nb_etages);
    printf("%i ",sortie);
  }
  printf("\n\n");
}

int main(){
  actionRegistre(3);
}
