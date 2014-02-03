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
int max_mois(Jour ans[ANS][12][31], int an, int mois, int *jour)
{
  int max = ans[an - ANDB][mois - 1][0].max, j;
  if(jour) *jour = 1;
  for(j = 2; j < longueur_mois(an, mois); ++j)
    {
      int maxJour = ans[an - ANDB][mois - 1][j - 1].max;
      if(max < maxJour)
        {
          *jour = j ;
          max = maxJour;
        }
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
int min_mois(Jour ans[ANS][12][31], int an, int mois, int *jour)
{
  int min = ans[an - ANDB][mois - 1][0].min, j;
  if(jour) *jour = 1;
  for(j = 2; j < longueur_mois(an, mois); ++j)
    {
      int minJour = ans[an - ANDB][mois - 1][j - 1].min;
      if(min > minJour)
        {
          min = minJour;
          if(jour) *jour = j;
        }
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
int min_an(Jour ans[ANS][12][31], int an, int *mois, int *jour)
{
  int min = min_mois(ans, an, 1, jour), m;
  if(mois) *mois = 1;
  for(m = 2; m <= 12; ++m)
    {
      int minMoisJour = 1;
      int minMois = min_mois(ans, an, m, &minMoisJour);
      if(min > minMois)
        {
         min = minMois;
         *mois = m;
         *jour = minMoisJour;
        }
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
int max_an(Jour ans[ANS][12][31], int an, int *mois, int *jour)
{
  int max = max_mois(ans, an, 1, jour), m;
  if(mois) *mois = 1;
  for(m = 2; m <= 12; ++m)
    {
      int maxMoisJour = 1;
      int maxMois = max_mois(ans, an, m, &maxMoisJour);
      if(max < maxMois)
        {
          max = maxMois;
          if(mois) *mois = m;
          if(jour) *jour = maxMoisJour;
        }
    }
  return max;
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


#endif // REQUETE_H
