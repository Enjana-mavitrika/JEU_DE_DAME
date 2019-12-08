/*
 * MODULE : **** GESTION INTELLIGENCE ARTIFICIELLE  ****
 * DÉCLARATION des fonctions pour permettre à l'ordinateur de jouer à la place d'un utilisateur. Les fonctions déplacent les pièce automatiquement tout en respectant les règles. L'ordinateur joue les pièces noir.
*
*/


/* déclaration de la fonction qui compte le nombre de possibilité de capture */
/* prends en paramètre un tableau de coup et met dans ce tableau les coups pour effectuer les prises et prend un autre tableau de coup pour mettre les coup à exclure */
int nombreDePrisePossible(configuration config,piece p,coup cps[N],int *cps_l,coup cpExcls[N]);



/* déclaration de la fonction qui determine le nombre de possibilité de déplacement pour une pièce et les coups correspondants */
int nombreDeplacementPossible(configuration config,piece pc,coup cps[N]);


/* déclaration DES FONCTIONS  qui va permettre à L'ORDINATEUR DE JOUER à la place du JOUEUR_NOIR */

/* déclaration de la fonction selectionner */
void ordinateurSelectionne(configuration config,selection *select,coup cps[N],int *cps_l);


/* déclaration de la fonction pour jouer un coup */
void ordinateurJouerCoup(configuration config,piece p,coup *cp);
