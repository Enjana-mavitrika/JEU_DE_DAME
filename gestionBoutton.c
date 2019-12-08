/*
 * MODULE : **** GESTION  DES BOUTTONS abandonner,undo et quitter/saugegarder***
 * DEFINITION DES FONCTIONS POUR GERER LES BOUTTONS SUR LE COTER DU DAMIER 
*/

#include "type.h"
#include "plateforme.h" /* inclure plateforme pour utiliser la fonction initConfiguration() dans la fonction initConfigs_saved() */


/* définition de la fonction qui determine si un joueur est revenu au menu principale */
int estRevenuAuMenu(selection s){
  if(s.x == -3 && s.y == -3){
    return 1;
  }else{
    return 0;
  }
}


/* définition de la fonction qui determine si un joueur abandonne la partie */
int aAbandonner(selection s){
  if(s.x == -1 && s.y == -1){
    return 1;
  }else{
    return 0;
  }
}

/* définition de la fonction qui determine si un joueur est revenu à la configuration précédente */
int estRevenuEnArriere(selection s){
  if(s.x == -2 && s.y == -2){
    return 1;
  }else{
    return 0;
  }
}


/* définition de la fonction qui copie une configuration dans un autre configuration */
static void copierConfig(configuration source,configuration *dest){
  int i,j;
  for(i=0;i<10;i++){
    for(j=0;j<10;j++){
      /* recopier la matrice de source dans celle de dest */
      dest->t[i][j]=source.t[i][j];
    }
  }
  /* recopier le joueur courant de source dans celui de test */
  dest->j = source.j;
}


/* définition de la fonction qui permet de revenir à la configuration précedente  */
void revenirEnArriere(configuration *config,configuration configs_saved[3]){
  configuration config_tmp;
  /* sauvegarder la dernière configuration enregistré dans config_tmp */
  copierConfig(configs_saved[2],&config_tmp);
  /* mettre à jour les configurations enregistré */
  /* mettre configs_saved[1] dans configs_saved[2] */
  copierConfig(configs_saved[1],&configs_saved[2]);
  /* mettre configs_saved[0] dans configs_saved[1] */
  copierConfig(configs_saved[0],&configs_saved[1]);
  /* mettre configuration courant dans configs_saved[0] */
  copierConfig(*config,&configs_saved[0]);
  /* mettre la dernière configuration enregistré comme configuration courant */
  copierConfig(config_tmp,config);

  
}



/* définition de la fonction qui initialise le tableau de configuration qui contient les configurations sauvegardés */
void initConfigs_saved(configuration configs_saved[3]){
  int i;
  for(i=0;i<3;i++){
    initConfiguration(&configs_saved[i]);
  }
}




/* définition de la fonction qui va mettre à jour le tableaux contenant les configurations précedents à chaque tour */
void mettreAJour_configs_saved(configuration config,configuration configs_saved[3]){
  /* mettre configs_saved[1] dans configs_saved[2] */
  copierConfig(configs_saved[1],&configs_saved[2]);
  /* mettre configs_saved[0] dans configs_saved[1] */
  copierConfig(configs_saved[0],&configs_saved[1]);
  /* mettre configuration courant dans configs_saved[0] */
  copierConfig(config,&configs_saved[0]);
}
