/*
 * DECLARATION DES TYPES UTILISES DANS LES MODULES DU JEU
*/

typedef enum{
  JOUEUR_BLANC,
  JOUEUR_NOIR
}joueur;

typedef enum{
  PION,
  DAME
}typePiece;

typedef enum{
  BLANC,
  NOIR
}couleur;

typedef struct{
  typePiece tpc;
  couleur cpc;
  int posX;
  int posY;
  int val;
}piece;

typedef struct{
  int t[10][10];
  joueur j;
}configuration;

typedef struct {
  int x;
  int y;
}selection;

typedef struct{
  piece pc;
  int x;
  int y;
}coup;

typedef struct{
  char pseudo[100];
  int score;
}score;
