/*
 * MODULE : **** PLATEFORME DE JEU ****
 * DECLARATION des fonctions qui manipulent la plateforme de jeu
 * c'est à dire manipule la configuration
 */

/*
 * déclaration de la fonction qui initialise la configuration
 * remplis le damier de taille 10 et positionne les pions
*/
void initConfiguration(configuration *config);


/*
 * déclaration de la fonction qui affiche la configuration dans la console
 * affiche la matrice carré de taille 10 dans config.t
*/
void afficherConfiguration(configuration config);


/*
 * déclaration de la fonction qui change le joueur qui joue 
 * dans la configuration 
*/
void changerJoueur(configuration *config);


/* déclaration de la fonction qui initialise le jeu */
void start();
