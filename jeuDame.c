/**
 *  Jeu de dame
 *  PROJET PROGRAMATION C L2 
 *  Groupe: IBRAHIMA DIALLO - SOLOFO RABONARIJAONA
**/

/* LES BIBLIOTHEQUES */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "type.h" /* inclusion des type creé */
#include "constante.h" /* inclusion des constantes */
#include "plateforme.h" /* inclusion de la module qui manipule la configuration */
#include "bougerPiece.h" /* inclusion de la module qui manipule les pièces sur la configuration */
#include "gestionScoreEtFin.h" /* inclusion de la module qui gère les scores et fin de partie */
#include "gestionBoutton.h" /* inclusion de la module qui gère les bouttons sur le côté du damier */
#include "sauvegarde.h" /* inclusion de la module qui gère le sauvegarde et chargement d'une partie */
#include "intelligenceArtificiel.h" /* inclusion de la module qui permettra à la machine de jouer à la place d'un utilisateur en mode 1 joueur */
#include "interfaceGraphique.h" /**/




/* FONCTIONS PRINCIPALE */
int main(){
  /* déclaration des variables */
  configuration config;
  configuration configTemp; /* pour stocker la dernière configuration */
  selection select;
  coup monCoup;
  piece maPiece;
  int i,j;
  /*int c;*/ /* pour vider le buffer */
  /*int scanf1;*//* pour recuperer le premier scanf (mode de jeu) */
  int s=0; /* pour selectionner une pièce */
  int dep=0; /* pour simple deplacement */
  int prise=0; /* pour une prise */
  int abandon; /* indicateur pour vérifier si un joueur a abandonner */
  int fini=0; /* indicateur pour vérifier si une partie est fini ou pas */
  int mode = 1; /* indicateur du mode de jeu */
  coup cps[20]; /* tableaux de coup pour stocker les coups. requise comme paramètre dans la fonction nombreDePrisePossible() */
  int cps_l;  /* variable pour stocker le nombre de coups dans cps. requise comme paramètre dans la fonction nombreDePrisePossible() */
  coup cpExcls[50]; /* les coup déjà testés à exclure */
  int reselection=0; /* pour identifier une reselection de pièce pour une rafle */
  selection reselect; /* selection pour stocker la reselection pour une rafle */
  piece maPieceRes; /* piece pour stocker la piece reselectionner pour une rafle */
  int nbrPrisePossible; /* variable indiquant le nombre de prise possible pour une pièce sélectionner */
  int menu = 0; /* variable initialiser à 0 et ne change pas dans le programme pour pouvoir rester dans la première boucle et ainsi revenir à chaque fin de partie au menu  */
  configuration configs_saved[3]; /* pour stocker les 3 dernière configurations utiliser pour revenir en arrière via le boutton undo */
  int indicateur_menu = 0; /* indicateur pour vérifier si un joueur est revenu au menu principale */
  char pseudoGagnant[100]; /* stocker le pseudo saisi par l'utilisateur */

  /* initialiser la suite générant le nombre aléatoire */
   srand(time(NULL));

  /* initialiser monCoup */
  monCoup.x = 0;
  monCoup.y = 0;
  
  /* initialiser select */
  select.x = 0;
  select.y = 0;

  /* initialiser le jeu : creer la fenêtre et initialise la configuration */
  start(&config);

  
  do{
    /* initialiser configs_saved[3] */
    initConfigs_saved(configs_saved);
    /* afficher le menu */
    afficherMenu();

    /* SELECTIONNER LE MODE DE JEU */

    /*do{
      printf("\nSELECTIONNER LE MODE DE JEU :\n");
      printf("tapez 1 => 1 JOUEUR\n");
      printf("tapez 2 => 2 JOUEUR\n\n");
      scanf1 = scanf("%d",&mode);
      while((c=getchar()) != '\n' && c != EOF);
      }while(scanf1 != 1);*/

    /* choix du mode de jeu au menu */
    choixModeClic(&mode);

      
    /* si l'utilisateur veut afficher les meilleurs scores  */
    if(mode == 4){
      /* tant que l'utilisateur affiche les meilleurs score */
      do{
      afficherMeilleurScore();
      afficherMenu();
      choixModeClic(&mode);
      }while(mode == 4);
    }
    /* si le joueur veut continuer la dernière partie */
    if(mode == 3){
      charger(&config,&mode);
      /* reinitialiser select */
      select.x = -1;
      select.y = -1;
    }
    /* si le joueur veut quitter le jeu */
    else if(mode == 5){
      exit(0);
    }
    else{
      /* sinon initialiser la configuration */
      initConfiguration(&config);
    }


    do{

      /* enregistrer la dernière configuration dans configTemp pour permettre au joueur de reselectionner en cas d'erreur de selection */
      for(i=0;i<N;i++){
	for(j=0;j<N;j++){
	  configTemp.t[i][j] = config.t[i][j];
	}
      }
      configTemp.j = config.j;

      /* vérifier si la partie est fini */
      fini = estFinie(configTemp);
      printf("fini = %d\n",fini);
      if(!fini){

	do{
	  /* afficher la configuration */
	  afficher_configuration(configTemp);
	  afficherConfiguration(configTemp);
	  config=configTemp;
    
	  /* demander au joueur de selectionner une pièce */
	  do{

	    /* si pas de reselection pour une rafle */
	    if(!reselection){
	      /* si le mode de jeu est 1 JOUEUR */
	      if(mode == 1){
		/* si c'est le tour de l'ordi */
		if(config.j == JOUEUR_NOIR){
		  ordinateurSelectionne(config,&select,cps,&cps_l);
		}else{
		  /* demander au joueur de selectionner un pion*/
		  selectionClic(&select);
		}
	      }
	      else{
		/* sinon le mode de jeu est 2 JOUEUR */
		selectionClic(&select);
	      }
	    }
	    /* si on fait une reselection pour une rafle */
	    else{
	      /* on reselectionne la pièce déplacer précedement automatiquement */
	      select.x = reselect.x;
	      select.y = reselect.y;
	    }
	    printf("select x = %d select y= %d\n",select.x,select.y);
	    /*printf("Votre selection : x y\n");
	      if(scanf("%d %d",&select.x,&select.y) != 2){
	      s=0;
	      };*/

	
	
	    if(select.x >= 0 && select.y >= 0){
	      s = selectionEstValide(config,select);
	    }
	    printf(" s = %d \n\n",s);
	    

	    /* si le joueur est revenu en arriere */
	    if(estRevenuEnArriere(select)){
	      /* revenir au configuration précedent */
	      revenirEnArriere(&config,configs_saved);
	      /* ne pas valider la selection */
	      s=0;
	      /* réafficher la configuration */
	      afficher_configuration(config);
	      afficherConfiguration(config);
	      /* reinitialiser selection select */
	      select.x = 0;
	      select.y = 0;
	    }else{
	      /* sinon juste mettre à jour configs_saved[3] */
	      mettreAJour_configs_saved(config,configs_saved);
	    }


	    /* si le joueur a abandonné */
	    /* recuperer abandon ordi apartir de aAbandonner */
	    abandon = aAbandonner(select);

	    /* si le joueur revient au Menu Principale */
	    if(estRevenuAuMenu(select)){
	      indicateur_menu = 1;
	      /* ne pas valider la selection */
	      s = 0;
	      /* réinitialiser selection select */
	      select.x = 0;
	      select.y = 0;
	    }
	    else{
	      indicateur_menu = 0;
	    }
	    

	
	    /* vider le buffer */
	    /*while((c=getchar()) != '\n' && c != EOF);*/
	  }while(!s && !abandon && !indicateur_menu);


	  if(s){
	    /* la sélection est valide donc selectionner la pièce */
	    maPiece = selectionner(&config,select);
	    if(maPiece.tpc == PION)
	      printf("PION\n");
	    if(maPiece.tpc == DAME)
	      printf("DAME\n");
	    if(maPiece.cpc == BLANC)
	      printf("BLANC\n");
	    if(maPiece.cpc == NOIR)
	      printf("NOIR\n");

	
	    printf("abandon = %d\n",abandon);

     

	    /* afficher la configuration */
	    afficher_configuration(config);
	    afficherConfiguration(config);

	    /* demander au joueur de jouer un coup  */
	    /*
	      printf("votre déplacement : x y \n");
	      if(scanf("%d %d",&monCoup.x,&monCoup.y) != 2){
	      dep = 0;
	      }
	    */
	
	    /* si aucun joueur n'a abandonner ni revenu au menu principale */
	    if(!abandon && !indicateur_menu){
	      /* si le mode de jeu est 1 JOUEUR */
	      if(mode == 1){
		if(config.j == JOUEUR_NOIR){
		  ordinateurJouerCoup(config,maPiece,&monCoup);
		}else{
		  deplacerClic(&monCoup);
		}
	      }
	      /* sinon le mode de jeu est 2 JOUEUR */
	      else{
		deplacerClic(&monCoup);
	      }
	      dep = deplacerEstValide(config,maPiece,monCoup);
	    }
	    printf("coup x %d coup y %d",monCoup.x,monCoup.y);
	    printf("dep = %d\n",dep);
	    prise = priseEstValide(config,maPiece,monCoup);
	    printf("prise = %d\n",prise);
	    /* vider le buffer */
	    /*c=0
	      while((c=getchar()) != '\n' && c != EOF);*/
	  }
	}while(dep == 0 && prise == 0 && abandon == 0 && indicateur_menu == 0);

	if(s){
	  /* si c'est un simple déplacement */
	  if(prise){
	    /* deplacer la pièce */
	    prisePiece(&config,maPiece,monCoup);
	    /* reselectionner la pièce */
	    reselect.x = monCoup.x;
	    reselect.y = monCoup.y;
	    maPieceRes.posX = reselect.x;
	    maPieceRes.posY = reselect.y;
	    maPieceRes.tpc = maPiece.tpc;
	    maPieceRes.cpc = maPiece.cpc;

	    nbrPrisePossible = nombreDePrisePossible(config,maPieceRes,cps,&cps_l,cpExcls);
	    printf("nombre de Prise Possible = %d\n",nbrPrisePossible);
	    /* vérifier si une prise est encore possible après le coup pour la pièce déplacer */
	    if(nbrPrisePossible>0){
	      reselection = 1;
	    }else{
	      reselection = 0;
	    }

	    printf("reselection = %d \n",reselection);
	  }
	  /* sinon c'est une prise */
	  else{
	    /* effectuer la prise */
	    deplacerPiece(&config,maPiece,monCoup);
	  }
	}
      }

  
  
      /* changer les pions arrivés à la base après un deplacement ou une prise adverse en dame */
      /* et si on est pas en cours d'une rafle */
      if(!reselection){
	changerPionEnDame(&config);
      }

      /* changer le joueur s'il n'a pas abandonné ni reselection automatique ni est revenu au Menu */
      if(!abandon && !reselection && !indicateur_menu)
	changerJoueur(&config);

      /* sauvegarder la partie */
      if(!fini && !abandon){
	/* si la partie n'est pas encore fini sauvegarder */
	sauvegarde(config,mode);
      }
    
    }while(!abandon && !fini && !indicateur_menu);

    if(config.j == JOUEUR_NOIR)
      printf("Config.j = NOIR\n");
    else
      printf("config.j = BLANC\n");

    /* si un joueur a abandonné ou si le jeu est fini */
    if(abandon || fini){
      /*  en mode 1 joueur si victoire par abondan le joueur dans la configuration n'a pas été changer donc changer le joueur gagnant */
      if(abandon && mode == 1){
	changerJoueur(&config);
      }

      if(abandon && mode == 2){
	changerJoueur(&config);
	}

      /* si le jeu est en mode 2 joueurs ou si en mode 1 joueur mais que le joueur a gagné */
      if((mode == 2) || (mode == 1 && config.j == JOUEUR_BLANC)){
	/* Afficher le gagnant */
	if(config.j == JOUEUR_NOIR){
	  printf("LE GAGNANT EST LE JOUEUR NOIR\n");
      }else
       {
	 printf("LE GAGNANT EST LE JOUEUR BLANC\n");
       }

	/* demander le pseudo du joueur gagnant */
	demanderPseudoGagnant(pseudoGagnant,config.j);

	/* traiter score */
	traiterScore(pseudoGagnant);

	/* Afficher les score */
	afficherScoreRecap();
      }
      else{
	/* sinon le joueur en mode 1 joueur a perdu contre l'ordinateur donc affcher défaite */
	printf("VOUS AVEZ PERDU DOMMAGE !! REESSAYER VOUS AUREZ UNE CHANCE LA PROCHAINE FOIS.\n");
	afficherDefaite();
      }
	

      /* afficher le pseudo du joueur gagnant */
      printf("pseudo Gagnant : %s \n",pseudoGagnant);

      /* si la partie est finie réinitialiser la configuration avant de sauvegarder*/
      initConfiguration(&config);
      
    }


    
    /* sauvegarder avant d'aller au menu */
      sauvegarde(config,mode);
  
  }while(!menu);
  exit(0);
}


