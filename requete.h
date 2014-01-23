#ifndef REQUETE_H
#define REQUETE_H
#include "lecture.h"

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
void parcourir(Jour ans[ANS][12][31],
  int (*test)(Jour[ANS][12][31], int, int, int))
{
  int an, mois, jour;
  for(an = AN_DEBUT; an <= AN_FIN; AN++)
      if(test(ans, an, mois, jour))
          printf("%d/%d/%d\n", jour, mois, an);
}

#endif // REQUETE_H
