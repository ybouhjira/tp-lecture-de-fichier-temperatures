/**
  * Lecture du fichier de températures
  * Réalisé par : Youssef Bouhjira et Mohamed Ayoub El Mioui
  **/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "lecture.h"

/**
 * La fonction principale
 */
int main(void)
{
  // Lire le nom du fichier
  char nomFichier[100];
  printf("Entrez le nom du fichier : ");
  scanf("%[^\n]s", nomFichier);

  // Lire le fichier
  Jour ans[ANS][12][31];
  lecture(nomFichier, ans);

  return 0;
}
