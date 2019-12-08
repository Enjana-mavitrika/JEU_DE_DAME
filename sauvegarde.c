/*
 * MODULE : **** GESTION SAUVEGARDE/CHARGEMENT ****
 * DEFINITION des fonctions pour gérer le sauvegarde et chargement d'une partie
 * C'est à dire manipulation des fichiers pour enregistrer une configuration et recuperer une configuration.
*
*/

#include <stdlib.h>
#include <stdio.h>
#include "type.h"


/* définition de la fonction qui sauvegarde une configuration en cours dans le fichier save.txt qui se trouve dans le même répértoire que ce module */
void sauvegarde(configuration config,int mode){
  /* copier la configuration dans un fichier nommé save.txt */
  FILE *save;
  int i,j; /* variable courant pour parcourir le tableau d'entier dans la configuration */
  /* ouvrir le fichier en écriture */
  save = fopen("save.txt","w+");

  /* parcourir config.t et écrire les valeurs dans fichier save.txt */
  for(i=0;i<10;i++){
    for(j=0;j<10;j++){
      fprintf(save,"%d ",config.t[i][j]);
    }
  }
  
  /* mettre le joueur  */
  if(config.j == JOUEUR_BLANC)
    fprintf(save,"%d",11);
  else
    fprintf(save,"%d",22);

  /* et mettre le mode de jeu à la fin*/
  fprintf(save," %d",mode);

  /* fermer le fichier */
  fclose(save);
  
}

/* définition de la fonction pour charger une configuration stocker dans le fichier save.txt qui se trouve dans le même répértoire que ce module dans la configuration en cours */
void charger(configuration *config,int *mode){
  FILE *save;
  int i,j;
  int joueur;
  save = fopen("save.txt","r");
  /* restaurer la configuration */
  for(i=0;i<10;i++){
    for(j=0;j<10;j++){
      if(fscanf(save,"%d ",&config->t[i][j]) != 1){
	exit(-1);
      };
    }
  }

  /* restaurer le joueur */
  if(fscanf(save,"%d",&joueur) != 1){
    exit(-1);
  };
  if(joueur == 11){
    config->j = JOUEUR_BLANC;
  }else{
    config->j = JOUEUR_NOIR;
  }

  /* restaurer le mode de jeu */
  if(fscanf(save," %d",mode) != 1){
    exit(-1);
  }

  fclose(save);
}
