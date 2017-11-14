#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "hadamard.h"
#include "canal.h"

int main(){

  int nUsers, tailleH, mot_longueur, i, j;
  int ** mHadamard;
  int ** motcodeUsers;
  int ** codageSequences;
  int ** mots;
  int ** MatriceCanal;

  printf("***** Codeur de Hadamard *****\n\n");

  printf("Saisir le nombre d'utilisateurs: ");
  scanf("%i",&nUsers);
  printf("\n");

  printf("Saisir la longueur des mots: ");
  scanf("%i",&mot_longueur);
  printf("\n");

  mots = SaisirMot(nUsers,mot_longueur);

  printf("\nDefinition d'une taille pour la matrice d'Hadamard ...\n\n");
  tailleH = TailleMatrice(nUsers);
  sleep(1);

  printf("Création de la matrice d'Hadamard ...\n\n");
  mHadamard = MatHadamardCreer(tailleH);
  sleep(1);

  printf("Affichage de la matrice créée:\n\n");
  MatriceAffichage(mHadamard, tailleH, tailleH,LIGNE_ZERO);

  printf("\nAssignation des mots codes à chaque utilisateur ...\n\n");
  motcodeUsers = AssignUsers(nUsers, tailleH, mHadamard);
  MatriceAffichage(motcodeUsers, nUsers+1, tailleH,LIGNE_UN);

  sleep(2);

  printf("\nCréation de la matrice avec les mots codés ...\n\n");

  MatriceCanal = CodageSeq(motcodeUsers,mots,mot_longueur,tailleH,nUsers);
  MatriceAffichage(MatriceCanal,nUsers, mot_longueur * tailleH,LIGNE_ZERO);
  sleep(2);

  printf("Passage dans le canal ...\n\n");
  /*
    *
    * Fonction à faire
    *
  */
  sleep(2);

  printf("Affichage des mots decodé de chaque utilisateur: \n\n");
  /*
    *
    * Fonction(s) à faire
    *
  */
  sleep(2);

  printf("\nDestruction de la matrice avec les mots codés ... \n\n");
  /*
    *
    * Fonction à faire
    *
  */
  sleep(2);

  printf("Destruction de la matrice d'Hadamard ...\n\n");
  MatriceDetruire(mHadamard,tailleH);
  sleep(1);

  printf("***** Fin du codeur *****\n");

}
