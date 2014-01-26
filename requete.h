#ifndef REQUETE_H
#define REQUETE_H
#include <string.h>
#include "lecture.h"

/** Liste chainée de chaine de caractères */
typedef struct ListeChaines
{
  char val[100]; // Valeur
  struct ListeChaines *suiv;
} ListeChaines;

typedef enum
{
  AN,
  MOIS,
  JOUR,
  MIN,
  MAX,
  MOY_JOUR,
  MOY_MOIS,
  MOY_AN,
  MIN_MOIS,
  MIN_AN,
  MAX_MOIS,
  MAX_AN,
  OU // Séparateur
} Colonne;

typedef enum {JOUR_EST, EGALE, INF, SUP} Fonction;

/** structure condition */
typedef struct
{
  Colonne col; // Colonne sur laquelle appliquer la condition
  Fonction f; // la fonction applique
  ListeChaines *params; // les paramètres de la fonction
} Condition;

/** Liste chainée de conditions */
typedef struct ListeConditions
{
  Condition val;
  struct ListeConditions* suiv;
} ListeConditions;

float moy_jour(Jour ans[ANS][12][31], int an, int mois, int jour)
{
  Jour j = ans[an - AN_DEBUT][mois - 1][jour - 1];
  return ((float) (j.min + j.max)) / 2;
}

float moy_mois(Jour ans[ANS][12][31], int an, int mois)
{
  float moy = 0;
  int j, longueur = longueur_mois(an, mois);
  for(j = 0; j <= longueur; ++j) moy += moy_jour(ans, an, mois, j);
  return moy / longueur;
}

int max_mois(Jour ans[ANS][12][31], int an, int mois)
{
  int max = ans[an - AN_DEBUT][mois - 1][0].max, j;
  for(j = 2; j < longueur_mois(an, mois); ++j)
    {
      int maxJour = ans[an - AN_DEBUT][mois - 1][j - 1].max;
      if(max < maxJour) max = maxJour;
    }
  return max;
}

int min_mois(Jour ans[ANS][12][31], int an, int mois)
{
  int min = ans[an - AN_DEBUT][mois - 1][0].min, j;
  for(j = 2; j < longueur_mois(an, mois); ++j)
    {
      int minJour = ans[an - AN_DEBUT][mois - 1][j - 1].min;
      if(min > minJour) min = minJour;
    }
  return min;
}

float moy_an(Jour ans[ANS][12][31], int an)
{
  float moy = 0;
  int m;
  for(m = 1; m <= 12; ++m) moy += moy_mois(ans, an, m);
  return moy / 12;
}

int min_an(Jour ans[ANS][12][31], int an)
{
  int min = min_mois(ans, an, 1), m;
  for(m = 2; m <= 12; ++m)
    {
      int minMois = min_mois(ans, an, m);
      if(min > minMois) min = minMois;
    }
  return min;
}

int max_an(Jour ans[ANS][12][31], int an)
{
  int max = max_mois(ans, an, 1), m;
  for(m = 2; m <= 12; ++m)
    {
      int maxMois = max_mois(ans, an, m);
      if(max < maxMois) max = maxMois;
    }
  return max;
}

float colonne_a_valeur(Colonne col, Jour ans[ANS][12][31], int an,
int mois, int jour)
{
  switch (col) {
    case JOUR: return jour;
    case AN: return an;
    case MOIS: return mois;

    case MIN: return ans[an - AN_DEBUT][mois - 1][jour - 1].min;
    case MAX : return ans[an - AN_DEBUT][mois - 1][jour - 1].max;

    case MOY_JOUR: return moy_jour(ans, an, mois, jour);
    case MOY_MOIS: return moy_mois(ans, an, mois);
    case MOY_AN: return moy_an(ans, an);

    case MIN_MOIS: return min_mois(ans, an, mois);
    case MIN_AN: return min_an(ans, an);

    case MAX_MOIS: return max_mois(ans, an, mois);
    case MAX_AN: return max_an(ans, an);

    default: assert(0); return 0;
    }
}

int test_jour(Jour ans[ANS][12][31], int an, int mois, int jour,
ListeConditions* conditions)
{
  ListeConditions *courant ;

  for(courant = conditions; courant; courant = courant->suiv)
    {
      // tester la condition courante
      Condition cond = courant->val;

//      switch (cond.f)
//        {

//        }
    }

}

void parcourir(Jour ans[ANS][12][31], ListeConditions *conditions,
ListeChaines *cols, int *ok)
{
  int an, mois, jour;
  ListeChaines *courant = cols;

  for(an = AN_DEBUT; an <= AN_FIN; an++) // an
    for(mois = 1; mois <= 12; ++mois) // mois
      for(jour = 1; jour < longueur_mois(an, mois); ++jour) // jour
        if(test_jour(ans, an, mois, jour, conditions)) // tester
          while(courant)
            {
              // Afficher les colonnes séléctionnée par l'utilisateur
              if(!strcmp(courant->val, "année"))
                printf("%d ", an);
              else if(!strcmp(courant->val, "mois"))
                printf("%d ", mois);
              else if(!strcmp(courant->val, "jour"))
                printf("%d ", jour);
              else if(!strcmp(courant->val, "min"))
                printf("%d ", ans[an][mois][jour].min);
              else if(!strcmp(courant->val, "max"))
                printf("%d ", ans[an][mois][jour].max);
              else if(!strcmp(courant->val, "moy(jour)"))
                printf("%f ", moy_jour(ans, an, mois, jour));
              else if(!strcmp(courant->val, "moy(mois)"))
                printf("%f ", moy_mois(ans, an, mois));
              else if(!strcmp(courant->val, "max(mois)"))
                printf("%d ", max_mois(ans, an, mois));
              else if(!strcmp(courant->val, "min(mois)"))
                printf("%d ", min_mois(ans, an, mois));
              else if(!strcmp(courant->val, "moy(an)"))
                printf("%f ", moy_an(ans, an));
              else if(!strcmp(courant->val, "max(an)"))
                printf("%d ", max_an(ans, an));
              else if(!strcmp(courant->val, "min(an)"))
                printf("%d ", min_an(ans, an));
              else
                *ok = 0;
            }
}

void liste_chaines_ajout_fin(ListeChaines **liste, char *str)
{
  ListeChaines *nouv = calloc(1, sizeof(ListeChaines));
  strcpy(nouv->val, str);
  if(!(*liste)) *liste = nouv;
  else
    {
      ListeChaines *courant = *liste;
      while(courant->suiv) courant = courant->suiv;
      courant->suiv = nouv;
    }
}

void liste_conditions_ajout_fin(ListeConditions **liste, Condition cond)
{
  ListeConditions *nouv = calloc(1, sizeof(ListeConditions));
  nouv->val = cond;
  if(!(*liste)) *liste = nouv;
  else
    {
      ListeConditions *courant = *liste;
      while(courant->suiv) courant = courant->suiv;
      courant->suiv = nouv;
    }
}

ListeChaines* lire_colonnes()
{
  // Colonnes
  printf("colonnes : ");
  char colonne[100];

  ListeChaines *listeColonnes = NULL;
  char c = 'A';
  int i = 0;
  while(c != '\n')
    {
      c = getchar();
      if(c != ' ' && c != '\n') colonne[i++] = c;
      else
        {
          colonne[i] = '\0';
          i = 0;
          liste_chaines_ajout_fin(&listeColonnes, colonne);
        }
    }
  return listeColonnes;
}

Colonne chaine_a_colonne(char chaine[100], int *ok)
{
  if(!strcmp(chaine, "an")) return AN;
  if(!strcmp(chaine, "mois")) return MOIS;

  if(!strcmp(chaine, "jour")) return JOUR;
  if(!strcmp(chaine, "min")) return MIN;
  if(!strcmp(chaine, "max")) return MAX;
  if(!strcmp(chaine, "moy(jour)")) return MOY_JOUR;

  if(!strcmp(chaine, "moy(mois)")) return MOY_MOIS;
  if(!strcmp(chaine, "min(mois)")) return MIN_MOIS;
  if(!strcmp(chaine, "max(mois)")) return MAX_MOIS;

  if(!strcmp(chaine, "moy(an)")) return MOY_AN;
  if(!strcmp(chaine, "max(an)")) return MAX_AN;
  if(!strcmp(chaine, "min(an)")) return MIN_AN;

  // La chaine entrée est invalide
  *ok = 0;
  return 0;
}

Fonction chaine_a_fonction(char chaine[100], int *ok)
{
  if(!strcmp(chaine, "est")) return JOUR_EST;
  if(!strcmp(chaine, "=")) return EGALE;
  if(!strcmp(chaine, "<")) return INF;
  if(!strcmp(chaine, ">")) return SUP;

  // La chaine entrée est invalide
  *ok = 0;
  return 0;
}

ListeConditions* lire_conditions(int *ok)
{
  printf("CONDITIONS : \n    ");
  char mot[100];

  char c = 'a';
  int pos = 0;
  Condition courant ; // Condition courante;
  ListeConditions* conditions = NULL;
  int posCondition = 0; // position dans la structure condition
  while(c != ';')
    {
      c = getchar();

      // ajouter c au mot
      if(c != ' ' && c != '\n' && c != ';') mot[pos++] = c;
      else // fin du mot
        {
          mot[pos] = '\0';
          pos = 0;

          // Ajout a la condition courante
          if(posCondition == 0) // colonne
            {
              courant.col = chaine_a_colonne(mot, ok);
              posCondition++;
            }
          else if(posCondition == 1) // fonction
            {
              courant.f = chaine_a_fonction(mot, ok);
              posCondition++;
            }
          else
            {
              // fin de la condition
              if(strcmp(mot, "et") == 0 || c == '\n')
                {
                  liste_chaines_ajout_fin(&courant.params, mot);
                  liste_conditions_ajout_fin(&conditions, courant);
                  courant.params = NULL; // nouvelle condition
                  posCondition = 0;

                  if(c == '\n') // Ou
                    {
                      printf("ou ");
                      Condition separateur = {OU, EGALE, NULL};
                      liste_conditions_ajout_fin(&conditions, separateur);
                    }
                }
              else if(c == ';')
                {
                  liste_conditions_ajout_fin(&conditions, courant);
                }
              // Lecture des paramètres
              else
                liste_chaines_ajout_fin(&courant.params, mot);
            }
        }
    }
  return conditions;
}



void interrogation(Jour ans[ANS][12][31])
{
  int ok = 1;
  ListeChaines *colonnes = lire_colonnes();
  ListeConditions* conditions =  lire_conditions(&ok);

  parcourir(ans, conditions, colonnes, &ok);
}

#endif // REQUETE_H
