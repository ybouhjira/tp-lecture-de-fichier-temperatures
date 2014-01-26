#ifndef LECTURE_H
#define LECTURE_H

#include "date.h"

/* Les structures */
typedef struct
{
  char min; // température minimum
  char max; // température maximum
} Jour;

/* Les fonctions */


/** Entrées :
  *    fichier : Le fichier
  *    jours : résultat de la lecture
  *    mois
  * Description :
  *   Lit les température min et max de tous les jours
  * d'un mois et les enregistre dans le tableau jours.
  */
void lire_jours(FILE* fichier, Jour jours[31], int mois, int an)
{
  int j; // jour courant
  for(j = 1; j <= longueur_mois(an, mois); ++j)
    fscanf(fichier, "%*d : %d,%d\n", (int*) &jours[j - 1].min,
        (int*) &jours[j - 1].max);
}

/** Entrées :
  *    fichier : Le fichier
  *    mois : résultat de la lecture
  * Description :
  *   Les 12 mois appartir de la position actuelle dans
  * le fichier et enregistre le résultat dans mois.
  */
void lire_mois(FILE* fichier, Jour mois[12][31], int an)
{
  int m; // mois courant
  for(m = 1; m <= 12; ++m)
    {
      while(fgetc(fichier) != '\n'); // sauter la ligne du mois
      lire_jours(fichier, mois[m - 1], m, an);
    }
}

/** Entrées :
  *    nomFichier : Le nom du fichier
  *    ans : résultat de la lecture
  * Description :
  *   Lit le fichier nommé nomFichier et l'enregistre
  * son contenu dans Jour.
  */
void lecture(char *nomFichier, Jour ans[ANS][12][31])
{
  // Ouvrir le fichier
  FILE *fichier = fopen(nomFichier, "r");
  if(fichier)
    {
      while(!feof(fichier))
        {
          // Lire l'année
          int an;
          fscanf(fichier, "%d :\n", &an);

          // Lire les mois
          lire_mois(fichier, ans[an - ANDB], an);
        }
    }
  else
    {
      printf("Impossible d'ouvrir le fichier : ");
      perror(NULL);
    }
}

#endif // LECTURE_H
