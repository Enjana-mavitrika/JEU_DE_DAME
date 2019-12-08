/*
 * MODULE : **** GESTION DES SCORES , DES PSEUDOS ET AFFICHAGE FIN DE PARTIE ****
 * DECLARATION des fonctions pour gérer les scores et l'affichage à la fin d'une partie 
 * C'est à dire manipulation des fichiers pour stocker les couples pseudo scores permettre aux utilisateur de saisir leurs pseudos et calculer leurs scores en fonctions de leurs pseudos.Et gérer les évènement d'affichage pour afficher le récapitulatifs des scores des joueurs mais aussi afficher les 20 meilleurs scores
*
*/



/* déclaration de la fonction qui affiche les récapitulatif des dernière score enregistré dans le fichier score.txt */
void afficherScoreRecap();


/* déclaration de la fonction qui affiche les 20 meilleurs scores */
void afficherMeilleurScore();


/* déclaration de la fonction qui enregistre calcule et enregistre le score */
void traiterScore(char*pseudo);


/* déclaration de la fonction qui affiche le message défaite à l'écran */
void afficherDefaite();


/* déclaration de la fonction qui permet de demander le nom du joueur gagnant */
void demanderPseudoGagnant(char pseudoGagnant[100],joueur j);


/* Déclaration de la fonction qui détermine si une partie est finie */
int estFinie(configuration config);
