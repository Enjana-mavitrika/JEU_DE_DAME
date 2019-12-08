/*
 * MODULE : **** BOUGER LES PIECES ****
 * DECLARATION des fonctions pour manipuler les pions sur le damier
 * c'est à dire modifier les valeurs dans la matrice de configuration
*/



/* déclaration de la fonction pour selectionner une piece dans une configuration */
piece selectionner(configuration *config,selection s);


/* déclaration de la fonction pour vérifier si une selecton dans une configuration est valide */
int selectionEstValide(configuration config, selection s);


/* déclaration de la fonction pour déplacer une piece sur le damier  */
void deplacerPiece(configuration *config,piece p,coup cp);


/* déclaration de la fonction pour vérifier si un coup pour déplacer une pièce dans la configuration est valide selon les règles du jeu de dame */
int deplacerEstValide(configuration config,piece p,coup cp);


/* déclaration de la fonction prise qui permettra de prendre une piece du damier */
void prisePiece(configuration *config,piece p,coup cp);


/* déclaration de la fonction qui vérifie si une prise est valide selon les règles du jeu de dame */
int priseEstValide(configuration config,piece p,coup cp);


/* déclaration de la fonction pour changer les pions en dame */
void changerPionEnDame(configuration *config);
