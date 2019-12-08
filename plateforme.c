/*
 * MODULE : **** PLATEFORME DE JEU ****
 * DEFINITIONS des fonctions qui manipulent la plateforme de jeu
 * c'est à dire manipule la configuration
*/

#include "constante.h"
#include <stdio.h> /* inclusion de la bibliothèque standard i/o pour utiliser printf */
#include "type.h" /* inclusion des types manipulés dans cette module */
#include <MLV/MLV_all.h>





/* 
 * définition de la fonction qui rempli le damier 
 * cette fonction ne peut être utiliser que par cette module
*/
static void remplirDamier(int t[10][10]){
  int i,j;
 
  for(i=0;i<10;i++){
    for(j=0;j<10;j++){
      /* placer les pions noir */
      if(i<=3){
	/* sur les lignes paires */
	if(i%2 == 0){
	  /* placer un pion noir(1) sur les colonnes impaires */
	  if(j%2 == 1){
	    t[i][j]=1;
	  }
	  /* placer rien(0) sur les colonnes paires */
	  else{
	    t[i][j]=0;
	  }
	}
	/* sur les lignes impaires */
	else{
	  /* placer un pion noir(1) sur les colonnes paires */
	  if(j%2 == 0){
	    t[i][j]=1;
	  }
	  /* placer rien(0) sur les colonnes paires */
	  else{
	    t[i][j]=0;
	  }
	}
      }
      /* placer les pions blanc */
      else if(i>=6){
	/* sur les lignes paires */
	if(i%2 == 0){
	  /* placer un pion blanc(2) sur les colonnes impaires */
	  if(j%2 == 1){
	    t[i][j]=2;
	  }
	  /* placer rien(0) sur les colonnes paires */
	  else{
	    t[i][j]=0;
	  }
	}
	/* sur les lignes impaires */
	else{
	  /* placer un pion blanc(2) sur les colonnes paires */
	  if(j%2 == 0){
	    t[i][j]=2;
	  }
	  /* placer rien(0) sur les colonnes paires */
	  else{
	    t[i][j]=0;
	  }
	}
      }
      /* placer rien sur le reste */
      else{
	t[i][j]=0;
      }
    }
  }
}

/* définition de la fonction qui initialise la plateforme de jeu */
void initConfiguration(configuration *config){
  /* remplir le damier */
  remplirDamier(config->t);
  /* le joueur blanc commence le jeu */
  config->j = JOUEUR_BLANC;
}




/* définition de la fonction qui initialise le jeu */
void start(configuration *config){
  /* Créer une fenêtre */
  MLV_create_window("Jeu de dame","Jeu de dame",WINDOW_WIDTH,WINDOW_HEIGHT);

  /* initialiser le jeu */
  initConfiguration(config);
}




/*
 * définition de la fonction qui affiche la configuration dans la console
 * affiche matrice carré de taille 10 dans config.t
*/
void afficherConfiguration(configuration config){
  int i,j;
  /* affichage du damier */
  printf("\n");
  printf("Etat du damier: \n");
  for(i=0;i<10;i++){
    for(j=0;j<10;j++){
      printf("%d\t",config.t[i][j]);
    }
    printf("\n\n");
  }
  printf("\n\n");
  /* afficher le joueur */
  if(config.j == JOUEUR_BLANC){
    printf("Tour du JOUEUR BLANC");
  }else{
    printf("Tour du JOUEUR NOIR");
  }
  printf("\n");
}



/*
 * définition de la fonction qui change le joueur qui joue 
 * dans la configuration 
*/
void changerJoueur(configuration *config){
  if(config->j == JOUEUR_BLANC)
    config->j = JOUEUR_NOIR;
  else
    config->j = JOUEUR_BLANC;
}
