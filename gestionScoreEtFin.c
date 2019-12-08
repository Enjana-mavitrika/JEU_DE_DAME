/*
 * MODULE : **** GESTION DES SCORES , DES PSEUDOS ET AFFICHAGE FIN DE PARTIE ****
 * DEFINITION des fonctions pour gérer les scores et l'affichage à la fin d'une partie 
 * C'est à dire manipulation des fichiers pour stocker les couples pseudo scores permettre aux utilisateur de saisir leurs pseudos et calculer leurs scores en fonctions de leurs pseudos.Et gérer les évènement d'affichage pour afficher le récapitulatifs des scores des joueurs mais aussi afficher les 20 meilleurs scores
*
*/

#include "type.h"
#include <MLV/MLV_all.h>



/* définition de la fonction qui affiche les récapitulatif des dernière score enregistré dans le fichier score.txt */
void afficherScoreRecap(){
  score scr_recuperer[1000];
  char pseudo1[100];
  int score1;
  FILE*fichier;
  int c;
  int i=0;
  int posY = 40;
  int nbrScore = 0;
  char scr[10];
  fichier = fopen("score.txt","r");
  /* tant qu'on arrive pas à la fin du fichier score.txt ou recuperer 100 couple pseudo:score  */
  do{
    /* recuperer le couple pseudo:score */
    c = fscanf(fichier,"%s : %d ",pseudo1,&score1);
    printf("c = %d \n",c);
    if(c == 2){
      strcpy(scr_recuperer[i].pseudo,pseudo1);
      scr_recuperer[i].score = score1;
      i++;
    }
  }while(c != EOF && i<1000);

  /* afficher les scores à l'interface graphique  */
  /* Nettoyer l'écran */
  MLV_clear_window(MLV_COLOR_WHITE);

  /* Afficher titre */
  MLV_draw_text(10,10,"RÉCAPITULATIF DES SCORES :",MLV_COLOR_PURPLE);
  /* Afficher instruction pour quitter l'affichage */
   MLV_draw_text( 240, 10, "\"Appuyez sur une touche du clavier pour quitter\" ", MLV_COLOR_GREEN );

  /* Afficher en tête */
  MLV_draw_text(10,25,"pseudo",MLV_COLOR_RED);

  /* Afficher en tête */
  MLV_draw_text(160,25,"score",MLV_COLOR_RED);

  printf("i = %d \n",i);
  /* Afficher les 50 dernières scores dans l'ordre du plus récent au plus vieux */
  while(i>0 && nbrScore < 50){
    printf("entrer dans while \n");
    MLV_draw_text(10,posY,scr_recuperer[i-1].pseudo,MLV_COLOR_BLACK);
    sprintf(scr,"%d",scr_recuperer[i-1].score);
    MLV_draw_text(160,posY,scr,MLV_COLOR_BLACK);
    nbrScore ++;
    i--;
    /* interligne de 15px entre les scores */
    posY += 15;
    MLV_actualise_window();
  }

  MLV_actualise_window();

  /* Attendre que l'utilisateur appuie sur une touche pour quitter */
  MLV_wait_keyboard(NULL,NULL,NULL);

  /* fermer le fichier */
  fclose(fichier);
  
}





/* définition de la fonction qui affiche les 20 meilleurs scores */
void afficherMeilleurScore(){
  score scr_recuperer[1000];
  char pseudo1[100];
  int score1;
  FILE*fichier;
  int c;
  int i=0;
  int posY = 40;
  int nbrScore = 0;
  char scr[10];
  int j,k;
  score scr_tmp;
  int nbrScoreAfficher = 20;
  fichier = fopen("score.txt","r");
  /* tant qu'on arrive pas à la fin du fichier score.txt ou recuperer 100 couple pseudo:score  */
  do{
    /* recuperer le couple pseudo:score */
    c = fscanf(fichier,"%s : %d ",pseudo1,&score1);
    printf("c = %d \n",c);
    if(c == 2){
      strcpy(scr_recuperer[i].pseudo,pseudo1);
      scr_recuperer[i].score = score1;
      i++;
    }
  }while(c != EOF && i<1000);

  /* afficher les scores à l'interface graphique  */
  /* Nettoyer l'écran */
  MLV_clear_window(MLV_COLOR_WHITE);

  /* Afficher titre */
  MLV_draw_text(10,10,"LES 20 MEILLEURS SCORES :",MLV_COLOR_PURPLE);
  /* Afficher instruction pour quitter l'affichage */
   MLV_draw_text( 240, 10, "\"Appuyez sur une touche du clavier pour quitter\" ", MLV_COLOR_GREEN );

  /* Afficher en tête */
  MLV_draw_text(10,25,"pseudo",MLV_COLOR_RED);

  /* Afficher en tête */
  MLV_draw_text(160,25,"score",MLV_COLOR_RED);

  /* trier le tableaux src_recuperer en fonction des scores dans l'ordre croissant */
  /* parcourir le tableau avec 2 curseurs qui se suive */
  j=0;
  k=1;
  while(j<i-1 && k<i){
    /* si le score du précedent est supérieur au score du suivant */
    if(scr_recuperer[j].score > scr_recuperer[k].score){
      /* échanger les scores */
      strcpy(scr_tmp.pseudo,scr_recuperer[j].pseudo);
      scr_tmp.score = scr_recuperer[j].score;
      strcpy(scr_recuperer[j].pseudo, scr_recuperer[k].pseudo);
      scr_recuperer[j].score = scr_recuperer[k].score;
      strcpy(scr_recuperer[k].pseudo,scr_tmp.pseudo);
      scr_recuperer[k].score = scr_tmp.score;

      /* et refaire le parcour */
      j = 0;
      k=1;
      printf("j = %d \n",j);
    }else{
    j++;
    k++;
    }
  }
  
  
  /* Afficher les 20 meilleurs scores */
  while(i>0 && nbrScore < nbrScoreAfficher){
    printf("entrer dans while \n");
    MLV_draw_text(10,posY,scr_recuperer[i-1].pseudo,MLV_COLOR_BLACK);
    sprintf(scr,"%d",scr_recuperer[i-1].score);
    MLV_draw_text(160,posY,scr,MLV_COLOR_BLACK);
    nbrScore ++;
    i--;
    /* interligne de 15px entre les scores */
    posY += 15;
    MLV_actualise_window();
  }

  MLV_actualise_window();

  /* Attendre que l'utilisateur appuie sur une touche pour quitter */
  MLV_wait_keyboard( NULL, NULL, NULL );

  /* fermer le fichier */
  fclose(fichier);
}





/* définition de la fonction qui enregistre calcule et enregistre le score */
void traiterScore(char*pseudo){
  int trouvee = 0; /* indicateur pour savoir si le pseudo a été trouvé dans les fichier ou pas */
  int c = 2;
  char pseudo1[100];
  int score = 0;
  FILE*fichier;
  FILE*fichier2;
  /* ouvrir le fichier en lecture/écriture */
  fichier = fopen("score.txt","r+");
  printf("a passer fopen \n");
  /* ouvrir le fichier2 en lecture/écriture */
  fichier2 = fopen("score2.txt","w+");

  while(c != EOF){
    c = fscanf(fichier,"%s : %d ",pseudo1,&score);
    if(c == 2){
      if(strcmp(pseudo1,pseudo) == 0){
	score ++;
	trouvee = 1;
      }
      fprintf(fichier2,"%s : %d ",pseudo1,score);
   
    }
  }

  /* si on a pas retrouver le pseudo dans le fichier */
  if(!trouvee){
    /* on le rajoute dans le fichier et lui attribuer sa première victoire */
    fprintf(fichier2,"%s : %d ",pseudo,1);
  }

  /* effacer le contenu de fichier */
  fichier = fopen("score.txt","w");

  /* remettre le pointeur sur le fichier 2 au début du fichier */
  fseek(fichier2,0,SEEK_SET);

  /* copier le contenu du fichier2 dans fichier */
  c=0;
  while(c != EOF){
    c = fscanf(fichier2,"%s : %d ",pseudo1,&score);
    if(c == 2){
      fprintf(fichier,"%s : %d ",pseudo1,score);
    }
  }

  /* fermer les fichiers */
  fclose(fichier);
  fclose(fichier2);
}




/* définition de la fonction qui affiche le message défaite à l'écran */
void afficherDefaite(){
  /* Nettoyer l'écran */
  MLV_clear_window(MLV_COLOR_WHITE);

  /* Afficher texte félicitation */
  MLV_draw_text(60,100,"DOMMAGE !! VOUS AVEZ PERDU !! ",MLV_COLOR_RED);
  MLV_draw_text(60,150," MAIS REESSAYER ENCORE VOUS AUREZ PLUS DE CHANCE LA PROCHAINE FOIS.",MLV_COLOR_BLUE);
  /* Afficher instruction pour quitter l'affichage */
   MLV_draw_text( 240, 180, "\"Appuyez sur une touche du clavier pour quitter\" ", MLV_COLOR_GREEN );
  MLV_actualise_window();
  /* Attendre que l'utilisateur appuie sur une touche pour quitter */
  MLV_wait_keyboard( NULL, NULL, NULL );
}





/* définition de la fonction qui permet de demander le nom du joueur gagnant */
void demanderPseudoGagnant(char pseudoGagnant[100],joueur j){
  int i;
  const char *texte_felicitation;
  const char *texte_afficher;
  char *text;
  /* adapter le texte afficher selon le joueur gagnant */
  if(j == JOUEUR_BLANC ){
    texte_felicitation = " LE GAGNANT EST LE JOUEUR BLANC !!! BRAVO !!";
    texte_afficher = " Veillez saisir le PSEUDO du JOUEUR BLANC : ";
      }
  else{
    texte_felicitation = " LE GAGNANT EST LE JOUEUR NOIR !!! BRAVO !!";
    texte_afficher = " Veillez saisir le PSEUDO du JOUEUR NOIR : ";
  }
  /* Nettoyer l'écran */
  MLV_clear_window(MLV_COLOR_WHITE);

  /* Afficher texte félicitation */
  MLV_draw_text(60,100,texte_felicitation,MLV_COLOR_PURPLE);

  /* Afficher la consigne */
  MLV_draw_text(180,180,texte_afficher,MLV_COLOR_BLACK);
  MLV_actualise_window();

  /* Afficher la boite de saisie pour recuperer le pseudo */
  MLV_wait_input_box(
		     180,200,
		     150,40,
		     MLV_COLOR_RED,MLV_COLOR_BLUE,MLV_COLOR_WHITE,
		     "Pseudo : ",&text
		     );
  /* copier les 100 première caractère de text dans pseudoGagnant */
  for(i=0;i<100;i++){
    if(i==99)
      pseudoGagnant[i] = '\0';
    else
      pseudoGagnant[i] = text[i]; 
  }

  printf("(fonction) pseudo Gagnant : %s \n",text);
  
}


/* Définition de la fonction qui détermine si une partie est finie */
int estFinie(configuration config){
  int i,j;
  int noir=0;
  int blanc=0;
  /* s'il y a plus de pièce blanc ou noir sur le damier */
  for(i=0;i<10;i++){
    for(j=0;j<10;j++){
      if(config.t[i][j] == 2 || config.t[i][j] == 4)
	blanc ++;
      if(config.t[i][j] == 1 || config.t[i][j] == 3)
	noir ++;
    }
  }
  if(noir == 0 || blanc == 0)
      return 1;
  else
    return 0;
}
