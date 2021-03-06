#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#include "hadamard.h"

/*  Fonction : TailleMatrice(...)
 *  Fonction qui calcule la taille de la matrice en fonction
 *	du nombre d'utilisateurs
*/
int TailleMatrice(int NbUtilisateur){

	int i = 2;
	int marq = 0;
	if( NbUtilisateur == 1) return 1;
	else{
		while(marq != 1){
			if(NbUtilisateur <= i)
				marq = 1;
			else
				i = i * 2;
		}
	}
	return i;

}

/*  Fonction : MatHadamardCreer(...)
 *  Création de la matrice d'hadamard
*/
int ** MatHadamardCreer(int NbUtilisateur){

	int i, j;
	int indice = 2;
	int taille = TailleMatrice(NbUtilisateur);

	int ** M = MatriceCreer(taille, taille);

	M[0][0] = 1;
	M[0][1] = 1;
	M[1][0] = 1;
	M[1][1] = -1;

	while(indice < taille){

		for(i = 0; i < indice * 2; i++){
			for(j = 0; j < indice * 2; j++){

				if(i >= indice && j < indice){
					M[i][j] = M[i-indice][j];
				}else if(j >= indice && i < indice){
					M[i][j] = M[i][j-indice];
				}else if (i >= indice && j >= indice){
					M[i][j] = M[i-indice][j-indice] * (-1);
				}
			}
		}

		indice = indice * 2;

	}

	return M;
}

/*  Fonction : AssignUsers(...)
 *  Creer une matrice qui contient le nombre d'utilisateur lignes
 *  et pour chaque utilisateur on atribut une ligne de la matrice d'hadamard
*/
int ** AssignUsers(int nbUser, int taille_mat, int ** mHadamard){
  int j;
  int User_courant;

  int ** motcodeUser = MatriceCreer(nbUser, taille_mat);

  for(User_courant = 0; User_courant < nbUser; User_courant++)
      for(j = 0; j < taille_mat; j++)
        motcodeUser[User_courant][j] = mHadamard[User_courant][j];

  return motcodeUser;
}


/*  Fonction : CodageSeq(...)
 *  Creer une matrice qui contient le codage de chaque sequence
 *  envoyer par l'utilisateur
*/
int ** CodageSeq(int ** motCode, int ** mots, int taille_mot, int taille_motcode, int nUsers){

  int ** codeSeq = MatriceCreer(nUsers, (taille_mot * taille_motcode));

	int indice_mot;

	int User_courant;
	int indice_motCode;

	int indice_sequence;

	for(User_courant = 0; User_courant < nUsers; User_courant++){

		for(indice_mot = 0; indice_mot < taille_mot; indice_mot++){
			for(indice_sequence = 0, indice_motCode = 0; indice_sequence < (taille_mot * taille_motcode); indice_sequence++, indice_motCode++){

				if(indice_motCode == taille_motcode){
					indice_motCode = 0;
					indice_mot++;
				}

				if(mots[User_courant][indice_mot] == -1)
					codeSeq[User_courant][indice_sequence] = -(motCode[User_courant][indice_motCode]);
				else
					codeSeq[User_courant][indice_sequence] = motCode[User_courant][indice_motCode];
			}
		}
	}

	return codeSeq;

}

/*  Fonction : SaisirMot(...)
 *  Fonction qui demmande pour chaque utilisateur le mots
 *	qu'il veut envoyer
*/
int ** SaisirMot(int l, int c){

	int ** m = MatriceCreer(l,c);
	int i,j;

	for(i = 0; i < l; i++){
    printf("Saisir mot utilisateur %i (suite de 0 ou de 1) de taille %i: \n",i,c);
    for(j = 0; j < c; j++){
      scanf("%i",&m[i][j]);
			if(m[i][j] == 0) m[i][j] = -1;
    }
  }

	return m;

}

/*  Fonction : DecoderMot(...)
 *  Fonction qui decode les mots après le passage dans le canal
*/
void DecoderMot(int * mat, int taille_mat, int ** motcode, int taille_motcode, int User_courant, int taille_mot, int * mots_decoder){
	int i, j, k;

	int somme = 0;
	int val;

	for(i = 0, j = 0; j < taille_mat; i++){

		for(k = 0; k < taille_motcode; k++, j++)
			somme += ( mat[j] * motcode[User_courant][k] );

		val = somme / taille_motcode;
		mots_decoder[i] = val;
		somme = 0;

	}

}

/*  Fonction : Decodage(...)
 *  Creer une un tableau qui contient la somme de toutes les colonnes de la matrice codeseq
*/
int ** Decodage(int ** seq, int nb_user, int ** motcode, int taille_motcode, int taille_mot){

	int i, j;
	int user;
	int taille_ligne = taille_mot * taille_motcode;
	int mat[taille_ligne];
	int ** motsdecoder = MatriceCreer(nb_user, taille_mot);

	for(i = 0; i < taille_ligne; i++)
		mat[i] = 0;

	for(i = 0; i < taille_ligne; i++){
		for(j = 0; j < nb_user; j++){
			mat[i] += seq[j][i];
		}
	}

	for(user = 0; user < nb_user; user++){
		DecoderMot(mat, taille_ligne, motcode, taille_motcode, user, taille_mot, motsdecoder[user]);
	}

	return motsdecoder;
}
