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


/** Entrées :
  *    ans : Les données lu du fichier
  *    test : Une fonction qui test une condition sur la ligne
  *      courant et renvoie une boolean indiquant si le cette
  *      dérnière admet la condition. Elle a comme arguments :
  *      ans, l'an, et la date courante (int, int, int)
  * Description :
  *   Parcour tous les jour dans le tableau ans et exécute sur
  * eux la fonction parcourir si cette dérnière retourne 1 la
  * date est affiché
  */
//void parcourir(Jour ans[ANS][12][31],
//int (*test)(Jour[ANS][12][31], int, int, int),
//Liste *cols)
//{
//  int an, mois, jour;
//  for(an = AN_DEBUT; an <= AN_FIN; an++)
//    {
//      if(test(ans, an, mois, jour))
//        {
//          // Parcourir la listes des colonnes
//          Liste *courant = *cols;

//          // Afficher les colonnes séléctionnée par l'utilisateur
//          while(courant)
//            {
//              // année
//              if(!strcmp(courant->val, "année"))
//                printf("%d ", an);

//              // mois
//              if(!strcmp(courant->val, "mois"))
//                printf("%d ", mois);

//              // jour
//              if(!strcmp(courant->val, "jour"))
//                printf("%d ", jour);

//              // min
//              if(!strcmp(courant->val, "min"))
//                printtf("%d ", ans[an][mois][jour].min);

//              // max
//              if(!strcmp(courant->val, "max"))
//                printf("%d ", ans[an][mois][jour].max);

//              // moy(jour)
//              if(!strcmp(courant->val, "moy(jour)"))
//                printf("%f ", moyenne_jour());
//              // TODO: écrire la fonction moyenne_jour

//              // moy(mois)
//              if(!strcmp(courant->val, "moy(mois)"))
//                pritnf("%d ", moyenne_mois());
//              // TODO : écrire la fonction moyenne_mois

//              // max(mois)
//              if(!strcmp(courant->val, "max(mois)"))
//                printf("%d ", max_mois());
//              // TODO :écrire max_mois()

//              // min(mois)
//              if(!strcmp(courant->val, "min(mois)"))
//                printf("%d ", min_mois());
//              // TODO : écrire min_mois()

//              // moy(an)
//              if(!strcmp(courant->val, "moy(an)"))
//                printf("%f ", moyenne_an());
//              // TODO : écrire moyenne_an()

//              // max(an)
//              if(!strcmp(courant->val, "max(an)"))
//                printf("%d ", max_an());

//              // min(an)
//              if(!strcmp(courant->val, "min(an)"))
//                printf("%d ", min_an());
//              // TODO : écrire min_an()
//            }
//        }
//    }
//}

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
  *ok = 1;

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
  *ok = 1;
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

void interrogation()
{
  int ok = 1;
    ListeChaines *colonnes = lire_colonnes();
  ListeConditions* conditions =  lire_conditions(&ok);

  if(!ok) // erreur
    printf("Requete invalide.\n");
  else // traitement de la requete
    {
      ListeConditions *courant = conditions;
      while(courant)
        {
         printf("%d, %d, ",  courant->val.col, courant->val.f);

         ListeChaines *str = courant->val.params;
         while(str)
           {
             printf("%s, ", str->val);
             str = str->suiv;
           }
         printf("\n");
         courant = courant->suiv;
        }
    }
}

#endif // REQUETE_H
