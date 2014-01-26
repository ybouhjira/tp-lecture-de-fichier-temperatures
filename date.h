#ifndef DATE_H
#define DATE_H

#define ANDB 1901 // L'année de début
#define ANFN 2099 // L'année de fin
#define ANS 2099 - 1901 + 1 // Le nombre d'année

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
int jours_mois(short int mois, int an)
{
  int nombreJours = 0, m;
  for(m = mois - 1; m >= 1; --m) nombreJours += longueur_mois(an, m);
  return nombreJours;
}

char* nom_jour(int an, int mois, int jour)
{
  int jours_an = (an - ANDB) * 365 + (an - ANDB) / 4;
  int indice =  (jours_an + jours_mois(mois, an) + jour - 1) % 7;

  switch(indice)
    {
    case 0: return "mardi";
    case 1: return "mercredi";
    case 2: return "jeudi";
    case 3: return "vendredi";
    case 4: return "samedi";
    case 5: return "dimanche";
    default: return "lundi";
    }
}


#endif // DATE_H
