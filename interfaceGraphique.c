/*
 * MODULE : **** GESTION INTERFACE GRAPHIQUE  ****
 * DÉFINITION des fonctions qui gèrent l'affichage des menus, damier et bouttons à l'écran en utilisant la bibliothèque MLV et les fonctions qui vont gérer les évènement récuperer au clavier ou souris pour manipuler l'affichage et jouer avec la souris.
*
*/

#include "constante.h"
#include "type.h"
#include <MLV/MLV_all.h> /* inclure la bibliothèque MLV */




/* définition de la fonction afficher_configuration qui affiche l'état de la partie en utilisant la bibliothèque MLV */
void afficher_configuration(configuration config){
  int i,j;

  /* On charge en mémoire les fichier images */

  MLV_Image *fond_bois = MLV_load_image("images/fond_bois.jpeg");
  MLV_Image *jaune_vide = MLV_load_image("images/jaune_vide.png");
  MLV_Image *noir_dame_blanc = MLV_load_image("images/noir_dame_blanc.png");
  MLV_Image *noir_dame_noir = MLV_load_image("images/noir_dame_noir.png");
  MLV_Image *noir_pion_blanc = MLV_load_image("images/noir_pion_blanc.png");
  MLV_Image *noir_pion_noir = MLV_load_image("images/noir_pion_noir.png");
  MLV_Image *noir_vide = MLV_load_image("images/noir_vide.png");
  MLV_Image *noir_pion_blanc_marquer = MLV_load_image("images/noir_pion_blanc_marquer.png");
  MLV_Image *noir_dame_blanc_marquer = MLV_load_image("images/noir_dame_blanc_marquer.png");
  MLV_Image *noir_dame_noir_marquer = MLV_load_image("images/noir_dame_noir_marquer.png");
  MLV_Image *noir_pion_noir_marquer = MLV_load_image("images/noir_pion_noir_marquer.png");
  MLV_Image *abandon = MLV_load_image("images/abandon.png");
  MLV_Image *quit = MLV_load_image("images/quit.png");
  MLV_Image *undo = MLV_load_image("images/undo.png");
  
  /* effacer la fenêtre */
  MLV_clear_window(MLV_COLOR_WHITE);

  /* afficher le fond en bois */
  MLV_draw_image(fond_bois,0,0);
  
  /* creer le damier */
  for(i=0; i < N; i++){
    for(j=0; j < N; j++){
      if((i%2 == 0 && j%2==0) || (i%2 == 1 && j%2 == 1)){
	/* afficher une case vide jaune */
	/* on le redimenssionne */
	MLV_resize_image_with_proportions(jaune_vide,WIDTH,HEIGHT);
	/* on affiche l'image */
	MLV_draw_image(jaune_vide,X+WIDTH*j,Y+HEIGHT*i);
      }
      else{
	if(config.t[i][j] == 0){
	  /* afficher une case vide noir */
	  /* on le redimenssionne */
	  MLV_resize_image_with_proportions(noir_vide,WIDTH,HEIGHT);
	  /* on affiche l'image */
	  MLV_draw_image(noir_vide,X+WIDTH*j,Y+HEIGHT*i);
	}
	else if(config.t[i][j] == 2){
	  /* afficher une case noir avec un pion blanc */
	  /* on le redimenssionne */
	  MLV_resize_image_with_proportions(noir_pion_blanc,WIDTH,HEIGHT);
	  /* on affiche l'image */
	  MLV_draw_image(noir_pion_blanc,X+WIDTH*j,Y+HEIGHT*i);
	}
	else if(config.t[i][j] == 4){
	  /* afficher une case noir avec une dame blanche */
	  /* on le redimenssionne */
	  MLV_resize_image_with_proportions(noir_dame_blanc,WIDTH,HEIGHT);
	  /* on affiche l'image */
	  MLV_draw_image(noir_dame_blanc,X+WIDTH*j,Y+HEIGHT*i);
	}
	else if(config.t[i][j] == 1){
	  /* afficher une case noir avec un pion noir */
	  /* on le redimenssionne */
	  MLV_resize_image_with_proportions(noir_pion_noir,WIDTH,HEIGHT);
	  /* on affiche l'image */
	  MLV_draw_image(noir_pion_noir,X+WIDTH*j,Y+HEIGHT*i);
	}
	else if(config.t[i][j] == 3){
	  /* afficher une case noir avec une dame noir */
	  /* on le redimenssionne */
	  MLV_resize_image_with_proportions(noir_dame_noir,WIDTH,HEIGHT);
	  /* on affiche l'image */
	  MLV_draw_image(noir_dame_noir,X+WIDTH*j,Y+HEIGHT*i);
	}
	else{
	  if(config.t[i][j] == -1){
	    /* afficher une case noir avec un pion noir marquer */
	  /* on le redimenssionne */
	  MLV_resize_image_with_proportions(noir_pion_noir_marquer,WIDTH,HEIGHT);
	  /* on affiche l'image */
	  MLV_draw_image(noir_pion_noir_marquer,X+WIDTH*j,Y+HEIGHT*i);
	  }
	  if(config.t[i][j] == -3){
	    /* afficher une case noir avec une dame noir marquer */
	  /* on le redimenssionne */
	  MLV_resize_image_with_proportions(noir_dame_noir_marquer,WIDTH,HEIGHT);
	  /* on affiche l'image */
	  MLV_draw_image(noir_dame_noir_marquer,X+WIDTH*j,Y+HEIGHT*i);
	  }
	  if(config.t[i][j] == -2){
	    /* afficher une case noir avec un pion blanc marquer */
	  /* on le redimenssionne */
	  MLV_resize_image_with_proportions(noir_pion_blanc_marquer,WIDTH,HEIGHT);
	  /* on affiche l'image */
	  MLV_draw_image(noir_pion_blanc_marquer,X+WIDTH*j,Y+HEIGHT*i);
	  }
	  if(config.t[i][j] == -4){
	    /* afficher une case noir avec une dame blanche marquer */
	  /* on le redimenssionne */
	  MLV_resize_image_with_proportions(noir_dame_blanc_marquer,WIDTH,HEIGHT);
	  /* on affiche l'image */
	  MLV_draw_image(noir_dame_blanc_marquer,X+WIDTH*j,Y+HEIGHT*i);
	  }
	}
      }
    }
  }

  
  /* afficher les bouttons */
  /* afficher boutton abandonner */
  MLV_resize_image_with_proportions(abandon,50,50);
  MLV_draw_image(abandon,(600-50+10),10);
  MLV_draw_text((600+15),10+20,"Abandonner",MLV_COLOR_BLACK);
  /* afficher boutton undo */
  MLV_resize_image_with_proportions(undo,50,50);
  MLV_draw_image(undo,(600-50+10),10+50+5);
  MLV_draw_text((600+15),(10+50+5+20),"Undo",MLV_COLOR_BLACK);
  /* afficher boutton quitter/sauvegarder */
  MLV_resize_image_with_proportions(quit,50,50);
  MLV_draw_image(quit,(600-50+10),(10+50+5+50+5));
  MLV_draw_text((600+15),(10+50+5+50+5+10),"Quitter/",MLV_COLOR_BLACK);
  MLV_draw_text((600+15),(10+50+5+50+5+20),"Sauvegarde",MLV_COLOR_BLACK);
  

  /* afficher le JOUEUR qui doit joueur */
  if(config.j == JOUEUR_NOIR){
    MLV_draw_text((600-50),(10+50+5+50+5+100),"TOUR DU NOIR",MLV_COLOR_RED);
  }else{
    MLV_draw_text((600-50),(10+50+5+50+5+100),"TOUR DU BLANC",MLV_COLOR_PURPLE);
  }

  /* actualiser la fenêtre */
  MLV_actualise_window();
  
}







/* définition de la fonction pour afficher le menu */
void afficherMenu(){
  /* charger l'image de fond du menu */
  MLV_Image *fond_menu = MLV_load_image("images/fond_menu.png");
  /* charger les images des bouttons */
  MLV_Image *button1 = MLV_load_image("images/boutton1.png");
  MLV_Image *button2 = MLV_load_image("images/boutton2.png");
  MLV_Image *button_continue2 = MLV_load_image("images/boutton_continu.png");
  MLV_Image *boutton_meilleur_score = MLV_load_image("images/boutton_meilleur_score.png");
  MLV_Image *boutton_quitter = MLV_load_image("images/boutton_quitter.png");
  /* effacer la fenêtre */
  MLV_clear_window(MLV_COLOR_WHITE);

  /* On affiche l'image de fond */
  /* on affiche l'image */
  MLV_resize_image_with_proportions(fond_menu,850,520);
  MLV_draw_image(fond_menu,0,0);

  /* on affiche les bouttons menu */
  MLV_resize_image_with_proportions(button1,150,50);
  MLV_draw_image(button1,(350-75),75);
  MLV_resize_image_with_proportions(button2,150,50);
  MLV_draw_image(button2,(350-75),(75+50));
  MLV_resize_image_with_proportions(button_continue2,150,50);
  MLV_draw_image(button_continue2,(350-75),(75+100));
  MLV_resize_image_with_proportions(boutton_meilleur_score,150,50);
  MLV_draw_image(boutton_meilleur_score,(350-75),(75+150));
  MLV_resize_image_with_proportions(boutton_quitter,150,50);
  MLV_draw_image(boutton_quitter,(350-75),(75+200));
  /* actualiser la fenêtre */
  MLV_actualise_window();
}






/* définition de la fonction sélection avec IG */
void selectionClic(selection *select){
  int i,j;
  int mouseX,mouseY;
  /* attendre un clic de la part de l'utilisateur */
  MLV_wait_mouse(&mouseX,&mouseY);

  /* si l'utilisateur a selectionner un pion */
  for(i=0;i<10;i++){
    for(j=0;j<10;j++){
      /* calculer les coordonnés de selection en fonction des coordonnés recuperer par la souris  */
      if(mouseX >= X+WIDTH*j && mouseX <= X+WIDTH*j+WIDTH && mouseY >= Y+HEIGHT*i && mouseY <= Y+HEIGHT*i+HEIGHT){
	select->x = j;
	select->y = i;
      }
    }
  }

  /* si l'utilisateur a selectionner un boutton pour quitter,abondonner ou revenir en arrière */
  if(mouseX >= (600-50+10) && mouseX <= (600-50+10+50)){
    /* l'utilisateur a cliqué sur le boutton abandonner */
    if(mouseY>= 10 && mouseY < 10+50){
      select->x = -1;
      select->y = -1;
    }
    /* l'utilisateur a cliqué sur le boutton undo */
    if(mouseY >= 10+50+10 && mouseY < 10+50+10+50){
      select->x = -2;
      select->y = -2;
    }
    /* l'utilisateur a cliqué sur le boutton quitter */
    if(mouseY >= ((10+50)*2+10) && mouseY <= ((10+50)*2+10)+50){
      select->x = -3;
      select->y = -3;
    }
  }
}





/* définition de la fonction deplacer avec IG */
void deplacerClic(coup* cp){
  int i,j;
  int mouseX,mouseY;
  /* attendre un clic de la part de l'utilisateur */
  MLV_wait_mouse(&mouseX,&mouseY);
  for(i=0;i<10;i++){
    for(j=0;j<10;j++){
      /* calculer les coordonnés de selection en fonction des coordonnés recuperer par la souris  */
      if(mouseX >= X+WIDTH*j && mouseX <= X+WIDTH*j+WIDTH && mouseY >= Y+HEIGHT*i && mouseY <= Y+HEIGHT*i+HEIGHT){
	cp->x = j;
	cp->y = i;
      }
    }
  }
}





/* définition de la fonction choix mode avec IG */
void choixModeClic(int *mode){
  int mouseX,mouseY;
  int indicateur = 0;
  do{
    /* attendre un clic de la part de l'utilisateur */
    MLV_wait_mouse(&mouseX,&mouseY);
    /* si l'utilisateur clic dans un des bouttons */
    if(mouseX >= (350-75) && mouseX <= (350-75+150)){
      /* si l'utilisateur clic sur le boutton 1 JOUEUR */
      if(mouseY >= 75 && mouseY < (75+50)){
	*mode = 1;
	indicateur = 0;
      }
      /* si l'utilisateur clic sur le boutton 2 JOUEUR */
      else if(mouseY >= (75+50) && mouseY < (75+100) ){
	*mode = 2;
	indicateur = 0;
      }
      /* si l'utilisateur clic sur continuer */
      else if(mouseY >= (75+100) && mouseY < (75 + 150)){
	*mode = 3;
	indicateur = 0;
      }
      /* si l'utilisateur clic sur meilleur scores */
      else if(mouseY >= (75 + 150) && mouseY < (75 + 200)){
	*mode = 4;
	indicateur = 0;
      }
      else if(mouseY >= (75 + 200) && mouseY < (75 + 250)){
	*mode = 5;
	indicateur = 0;
      }
      /* sinon il n'a pas cliquer sur un boutton donc redemander */
      else{
	indicateur = 1;
      }
    }
    /* l'utilisateur n'a pas cliqué sur un boutton donc redemander */
    else{
      indicateur = 1;
    }
  }while (indicateur == 1);
}


