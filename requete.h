/**
  * fichier :requete.h
  * Contient les fonctions relatives à l'interrogation des données
  */

#ifndef REQUETE_H
#define REQUETE_H

#include <stdlib.h>
#include <string.h>

#include "lecture.h"
#include "date.h"
#include "structs.h"


/** Entrées :
  *    ans : Les données
  *    an : L'an
  *    mois : Le mois
  *    jour : Le jour
  * Sorties :
  *   La température moyenne de la date donnée.
  */
float moy_jour(Jour ans[ANS][12][31], int an, int mois, int jour)
{
  Jour j = ans[an - ANDB][mois - 1][jour - 1];
  return ((float) (j.min + j.max)) / 2;
}


/** Entrées :
  *    ans : Les données
  *    an : L'an
  *    mois : Le mois
  * Sorties :
  *   La température moyenne du mois.
  */
float moy_mois(Jour ans[ANS][12][31], int an, int mois)
{
  float moy = 0;
  int j, longueur = longueur_mois(an, mois);
  for(j = 0; j <= longueur; ++j) moy += moy_jour(ans, an, mois, j);
  return moy / longueur;
}

/** Entrées :
  *    ans : Les données
  *    an : L'an
  *    mois : Le mois
  * Sorties :
  *   La température maximum du mois.
  */
int max_mois(Jour ans[ANS][12][31], int an, int mois)
{
  int max = ans[an - ANDB][mois - 1][0].max, j;
  for(j = 2; j < longueur_mois(an, mois); ++j)
    {
      int maxJour = ans[an - ANDB][mois - 1][j - 1].max;
      if(max < maxJour) max = maxJour;
    }
  return max;
}


/** Entrées :
  *    ans : Les données
  *    an : L'an
  *    mois : Le mois
  * Sorties :
  *   La température minimum du mois
  */
int min_mois(Jour ans[ANS][12][31], int an, int mois)
{
  int min = ans[an - ANDB][mois - 1][0].min, j;
  for(j = 2; j < longueur_mois(an, mois); ++j)
    {
      int minJour = ans[an - ANDB][mois - 1][j - 1].min;
      if(min > minJour) min = minJour;
    }
  return min;
}

/** Entrées :
  *    ans : Les données
  *    an : L'an
  *    mois : Le mois
  *    jour : Le jour
  * Sorties :
  *   La température moyenne de la date donnée
  */
float moy_an(Jour ans[ANS][12][31], int an)
{
  float moy = 0;
  int m;
  for(m = 1; m <= 12; ++m) moy += moy_mois(ans, an, m);
  return moy / 12;
}


/** Entrées :
  *    ans : Les données
  *    an : L'an
  * Sorties :
  *   La température minimum l'année
  */
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


/** Entrées :
  *    ans : Les données
  *    an : L'an
  *    mois : Le mois
  *    jour : Le jour
  * Sorties :
  *   La température maximum de la date donnée
  */
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

/** Entrées :
 *    col : Une variable de type Colonne contenant la donnée sur laquelle
 *          sera appliquée la condition
 *    ans : Les données
 *    an : L'année
 *    mois : Le mois
 *    jour : Le jour
 * Sorties :
 *   le numéro du jour ou une température min ou max d'un
 * jour, d'un mois ou d'une année
 */

int colonne_a_int(Colonne col, Jour ans[ANS][12][31], int an,
int mois, int jour)
{
  switch (col) {
    case JOUR: return jour;
    case AN: return an;
    case MOIS: return mois;

    case MIN: return ans[an - ANDB][mois - 1][jour - 1].min;
    case MAX : return ans[an - ANDB][mois - 1][jour - 1].max;

    case MIN_MOIS: return min_mois(ans, an, mois);
    case MIN_AN: return min_an(ans, an);

    case MAX_MOIS: return max_mois(ans, an, mois);
    case MAX_AN: return max_an(ans, an);

    default: assert(0); return 0;
    }
}

/** Entrées :
 *    col : Une variable de type Colonne contenant la donnée sur laquelle
 *          sera appliquée la condition
 *    ans : Les données
 *    an : L'année
 *    mois : Le mois
 *    jour : Le jour
 * Sorties :
 *   la température moyenne d'un jour, d'un mois ou d'une année
 */

float colonne_a_float(Colonne col, Jour ans[ANS][12][31], int an,
int mois, int jour)
{
  switch (col)
    {
    case MOY_JOUR: return moy_jour(ans, an, mois, jour);
    case MOY_MOIS: return moy_mois(ans, an, mois);
    case MOY_AN: return moy_an(ans, an);
    default: // erreur
      assert(0);
      return 0;
    }
}

/** Entrées :
 *    cond : Une variable de type Condition
 *    ans : Les données
 *    an : L'année
 *    mois : Le mois
 *    jour : Le jour
 * Sorties :
 *   return 1 si la condition proposée est vérifiée, 0 sinon
 */

int tester_condition(Condition cond, Jour ans[ANS][12][31], int an,
int mois, int jour, int *ok)
{
  switch (cond.col)
    {
    // FLOAT
    case MOY_AN:
    case MOY_JOUR:
    case MOY_MOIS:
      {
        float val = colonne_a_float(cond.col, ans, an, mois, jour);
        switch (cond.f)
          {
          case EGALE: return val == cond.param.val.f;
          case INF: return val < cond.param.val.f;
          case SUP: return val > cond.param.val.f;
          default: // erreur
            *ok = 0;
            return 0;
          }
        break;
      }
      // INT
    default:
      {
        int val = colonne_a_int(cond.col, ans, an, mois, jour);
        switch (cond.f)
          {
          case EGALE: return val == cond.param.val.i;
          case INF: return val < cond.param.val.i;
          case SUP: return val < cond.param.val.i;
          case JOUR_EST:
            return !strcmp(nom_jour(an, mois, val), cond.param.val.jour);
          default:
            *ok = 0;
            return 0;
          }
      }
    }
}

/** Entrées :
 *    ans : Les données
 *    an : L'année
 *    mois : Le mois
 *    jour : Le jour
 *    conditions : Une variable de type ListeConditions
 * Sorties :
 *   return 1 si l'un des groupes de conditions est vérifié, 0 si non
 */

int test_jour(Jour ans[ANS][12][31], int an, int mois, int jour,
ListeConditions *conditions, int *ok)
{
  ListeConditions *lst ; // itérateur pour la liste
  int res = 1; // resultat

  for(lst = conditions; lst; lst = lst->suiv)
    {
      switch (lst->val.col) {
        case OU:
          //si les conditions précédentes sont vérifiées, on arrete
          if(res) return 1;
          //si non on passe aux conditions suivantes
          else res = 1;
          break;
        default:
          res = res && tester_condition(lst->val, ans, an, mois, jour, ok);
          if(!(*ok)) return 0;
        }
    }
  return res;
}

/** Entrées :
 *    ans : Les données
 *    cols : Une variable de type ListeChaines
 *    conditions : Une variable de type ListeConditions
 *    ok : Une variable de type entier (pour vérifier les erreurs)
 * Déscription :
 *    renvoyer sur l'ecran l'ensemble des données vérifiant les conditions
 * précisées
 */

void parcourir(Jour ans[ANS][12][31], ListeConditions *conditions,
ListeChaines *cols, int *ok)
{
  int an, mois, jour;

  for(an = ANDB; an <= ANFN; an++) // an
    {
      for(mois = 1; mois <= 12; ++mois) // mois
        {
          for(jour = 1; jour < longueur_mois(an, mois); ++jour) // jour
            {
              if(test_jour(ans, an, mois, jour, conditions, ok)) // tester
                {
                  ListeChaines *colonneCourante = cols;
                  // parcourir les colonnes et écrire ceux séléctionnées
                  while(colonneCourante)
                    {
                      if(!strcmp(colonneCourante->val, "an"))
                        printf("%d ", an);

                      if(!strcmp(colonneCourante->val, "mois"))
                        printf("%d ", mois);

                      if(!strcmp(colonneCourante->val, "jour"))
                        printf("%d ", jour);

                      if(!strcmp(colonneCourante->val, "min"))
                        printf("%d ",
                               ans[an - ANDB][mois - 1][jour - 1].min);

                      if(!strcmp(colonneCourante->val, "max"))
                        printf("%d ",
                               ans[an - ANDB][mois - 1][jour - 1].max);

                      if(!strcmp(colonneCourante->val, "moy(jour)"))
                        printf("%f ", moy_jour(ans, an, mois, jour));

                      if(!strcmp(colonneCourante->val, "moy(mois)"))
                        printf("%f ", moy_mois(ans, an, mois));

                      if(!strcmp(colonneCourante->val, "max(mois)"))
                        printf("%d ", max_mois(ans, an, mois));

                      if(!strcmp(colonneCourante->val, "min(mois)"))
                        printf("%d ", min_mois(ans, an, mois));

                      if(!strcmp(colonneCourante->val, "moy(an)"))
                        printf("%f ", moy_an(ans, an));

                      if(!strcmp(colonneCourante->val, "max(an)"))
                        printf("%d ", max_an(ans, an));

                      if(!strcmp(colonneCourante->val, "min(an)"))
                        printf("%d ", min_an(ans, an));

                      colonneCourante = colonneCourante->suiv;
                    }
                  printf("\n");
                }
            }
        }
    }
}

/** Entrées :
 *    liste : Une variable de type ListeChaines
 *    str : Une variable de type chaine de caractéres
 * Déscription :
 *    ajouter une donnée de type chaine de caractéres a la fin d'une liste
 * chainée
 */

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

/** Entrées :
 *    liste : Une variable de type ListeChaines
 *    str : Une variable de type chaine de caractéres
 * Déscription :
 *    ajouter une donnée de type Condition a la fin d'une liste
 * chainée de type ListeConditions
 */

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

/** Sorties :
 *    liste : Une variable de type ListeChaines
 * Déscription :
 *    ajouter une donnée de type Condition a la fin d'une liste
 * chainée de type ListeConditions
 */

ListeChaines *lire_colonnes()
{
  while(getchar() != '\n');

  // Colonnes
  printf("COLONNES : \n    ");
  char colonne[100];

  ListeChaines *listeColonnes = NULL;
  char c = 'A';
  int i = 0;
  while(c != '\n')
    {
      c = getchar();
      /*si le caractére lu n'est ni espace ni la fin de la chaine, le mettre
        dans la liste*/
      if(c != ' ' && c != '\n') colonne[i++] = c;
      else//sinon
        {
          colonne[i] = '\0';//marquer la fin de la chaine
          i = 0;
          //l'ajouter a la fin de la liste
          liste_chaines_ajout_fin(&listeColonnes, colonne);
        }
    }
  return listeColonnes;
}

/** 
 * Entrées :
 *    chaine : Une chaine de caractéres de type chaine de longueur 100
 *    ok : Une variable de type entier
 * Sorties :
 *    Colonne : Une variable de type Colonne
 * Déscription :
 *    renvoie le contenu d'une chaine de caractéres
 */

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

/**
 * Entrées :
 *    chaine : Une chaine de caractéres de type chaine de longueur 4
 *    ok : Une variable de type entier
 * Sorties :
 *    Fonction : Une variable de type Fonction
 * Déscription :
 *    renvoie le contenu d'une chaine de caractéres
 */

Fonction chaine_a_fonction(char chaine[4], int *ok)
{
  if(!strcmp(chaine, "est")) return JOUR_EST;
  if(!strcmp(chaine, "=")) return EGALE;
  if(!strcmp(chaine, "<")) return INF;
  if(!strcmp(chaine, ">")) return SUP;

  // La chaine entrée est invalide
  *ok = 0;
  return 0;
}

/**
 * Entrées :
 *    chaine : Une chaine de caractéres de type chaine de longueur 9
 *    cond : Une variable de type Condition
 * Déscription :
 *    remplie la variable cond avec le contenu de chaine, selon le type
 * du parametre
 */

void chaine_a_param(char chaine[9], Condition *cond)
{
  switch (cond->col)
    {
    // jour -> STR pour est , et INT pour EGALE
    case JOUR://dans le cas de JOUR
      switch (cond->f)
        {
        case JOUR_EST://si la fonction est JOUR_EST
          strcpy(cond->param.val.jour, chaine);//affecter le jour
          cond->param.type = STR;//affecter le type de condition
          break;
        default :
          cond->param.type = INT;
          cond->param.val.i = atoi(chaine);
        }
      break;

      // FLOAT
    case MOY_AN:
    case MOY_JOUR:
    case MOY_MOIS:
      cond->param.val.f = atof(chaine);
      cond->param.type = FLOAT;
      break;

      // INT
    default:
      cond->param.type = INT;
      cond->param.val.i = atoi(chaine);
    }
}

/**
 * Entrées :
 *    ok : Une variable de entier (pour vérifier les erreurs)
 * Sorties :
 *    Une variable de type ListeConditions
 * Déscription :
 *    retourne une variable de type ListeConditions, contenant des données
 * (conditions) imposées par l'utilisateur
 */

ListeConditions *lire_conditions(int *ok)
{
  printf("CONDITIONS : \n    ");
  char mot[10];

  char c = 'a';
  int pos = 0;
  Condition courant = {0} ; // Condition courante;
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
                  if(c == '\n')
                    chaine_a_param(mot, &courant);

                  liste_conditions_ajout_fin(&conditions, courant);
                  posCondition = 0; // nouvelle condition

                  if(c == '\n') // Ou
                    {
                      printf("ou ");
                      Condition separateur;
                      separateur.col = OU;
                      liste_conditions_ajout_fin(&conditions, separateur);
                    }
                }
              else if(c == ';')
                {
                  liste_conditions_ajout_fin(&conditions, courant);
                }
              // Lecture des paramètres
              else
                chaine_a_param(mot, &courant);
            }
        }
    }
  return conditions;
}

/**
 * Entrées :
 *    ans : Les données
 * Déscription :
 *    Définir les colonnes et les conditions et faire le parcour des
 * données, en se basant sur ces conditions
 */

void interrogation(Jour ans[ANS][12][31])
{
  int ok = 1;
  ListeChaines *colonnes = lire_colonnes();
  ListeConditions* conditions =  lire_conditions(&ok);

  parcourir(ans, conditions, colonnes, &ok);
}

#endif // REQUETE_H
