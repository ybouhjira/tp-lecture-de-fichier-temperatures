#ifndef LECTURE_H
#define LECTURE_H

#define AN_DEBUT 1901 // L'année de début
#define AN_FIN 2099 // L'année de fin
#define ANS 2099 - 1901 + 1 // Le nombre d'année

/* Les structures */
typedef struct
{
  char min; // température minimum
  char max; // température maximum
} Jour;

/* Les fonctions */
/** Entrées :
  *   an : L'année
  *   mois : Le mois
  * Sorties :
  *   longeur : Le nombre de jour dans le mois
  */
int longueur_mois(int an, int mois)
{
  assert(1 <= mois && mois <= 12);
  return mois == 2 ? an % 4? 28 : 29 : 30 + (((mois * 9) / 8) & 1);
}

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
void lecture(char *nomFichier, Jour ans[AN_FIN - AN_DEBUT][12][31])
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
          lire_mois(fichier, ans[an - AN_DEBUT], an);
        }
    }
  else
    {
      printf("Impossible d'ouvrir le fichier : ");
      perror(NULL);
    }
}

#endif // LECTURE_H
