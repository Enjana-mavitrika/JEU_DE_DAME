/*
 * MODULE : **** GESTION  DES BOUTTONS abandonner,undo et quitter/saugegarder***
 * DECLARATION DES FONTIONS POUR GERER LES BOUTTONS SUR LE COTER DU DAMIER
*/

/* déclaration de la fonction qui determine si un joueur est revenu au menu principale */
int estRevenuAuMenu(selection s);


/* déclaration de la fonction qui determine si un joueur abandonne la partie */
int aAbandonner(selection s);


  /* définition de la fonction qui determine si un joueur est revenu à la configuration précédente */
  int estRevenuEnArriere(selection s);



  
/* déclaration de la fonction qui permet de revenir à la configuration précedente  */
void revenirEnArriere(configuration *config,configuration configs_saved[3]);


/* déclaration de la fonction qui permet de revenir à la configuration précedente  */
void revenirEnArriere(configuration *config,configuration configs_saved[3]);


/* déclaration de la fonction qui initialise le tableau de configuration qui contient les configurations sauvegardés */
void initConfigs_saved(configuration configs_saved[3]);



/* définition de la fonction qui va mettre à jour le tableaux contenant les configurations précedents à chaque tour */
void mettreAJour_configs_saved(configuration config,configuration configs_saved[3]);



  
