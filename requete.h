#ifndef REQUETE_H
#define REQUETE_H
#include <string.h>
#include "lecture.h"

/**
  * Liste chainée de chaine de caractères
  */
typedef struct Liste
{
  char val[100]; // Valeur
  struct Liste *suiv;
} Liste;

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

void liste_ajout_fin(Liste **liste, char *str)
{
  Liste *nouv = calloc(1, sizeof(Liste));
  strcpy(nouv->val, str);
  if(!(*liste)) *liste = nouv;
  else
    {
      Liste *courant = *liste;
      while(courant->suiv) courant = courant->suiv;
      courant->suiv = nouv;
    }
}

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
  MAX_AN
} Colonne;

typedef enum
{
  JOUR_EST,
  JOUR_EGALE,
  JOUR_ENTRE,
  AN_EGALE,
  MOIS_EGALE
} Fonction;

typedef struct
{
  Colonne col;
  Fonction f;
  Liste *params;
} Condition;

void interrogation()
{
  // Colonnes
  printf("colonnes : ");
  char colonne[100];

  Liste *listeColonnes = NULL;
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
          liste_ajout_fin(&listeColonnes, colonne);
        }
    }

  // Conditions


}

#endif // REQUETE_H
