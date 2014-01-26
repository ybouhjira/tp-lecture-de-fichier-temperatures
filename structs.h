#ifndef STRUCTS_H
#define STRUCTS_H

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


typedef union
{
  char jour[9];
  float f;
  int i;
} UParam;

typedef enum {STR, INT, FLOAT} TypeParam;

typedef struct
{
  UParam val;
  TypeParam type;
} Param;

/** structure condition */
typedef struct
{
  Colonne col; // Colonne sur laquelle appliquer la condition
  Fonction f; // la fonction applique
  Param param; // les paramètres de la fonction
} Condition;

/** Liste chainée de conditions */
typedef struct ListeConditions
{
  Condition val;
  struct ListeConditions* suiv;
} ListeConditions;

#endif // STRUCTS_H
