/**
  * Lecture du fichier de températures
  * Réalisé par : Youssef Bouhjira et Mohamed Ayoub El Mioui
  **/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "lecture.h"
#include "requete.h"

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

  int jour = 0;
  int froid = min_mois(ans, 1901, 1, &jour);

  printf("Le jour le plus froid dans le mois 1 de 1901 est %d, "
         "temperarture de %d\n", jour, froid);


  return 0;
}
