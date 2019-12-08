/*
 * MODULE : **** GESTION SAUVEGARDE/CHARGEMENT ****
 * DÉCLARATION des fonctions pour gérer le sauvegarde et chargement d'une partie
 * C'est à dire manipulation des fichiers pour enregistrer une configuration et recuperer une configuration.
*
*/


/* déclaration de la fonction qui sauvegarde la configuration courant dans le fichier save.txt qui se trouve dans la même répértoire que ce module */
void sauvegarde(configuration config,int mode);


/* déclaration de la fonction pour charger une configuration stocker dans le fichier save.txt qui se trouve dans le même répértoire que ce module dans la configuration en cours */
void charger(configuration *config,int *mode);
