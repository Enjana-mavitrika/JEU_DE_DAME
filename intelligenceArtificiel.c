/*
 * MODULE : **** GESTION INTELLIGENCE ARTIFICIELLE  ****
 * DEFINITION des fonctions pour permettre à l'ordinateur de jouer à la place d'un utilisateur. Les fonctions déplacent les pièce automatiquement.
*
*/

#include "constante.h"
#include "type.h"
#include "stdio.h" /* inclure stdio pour utiliser printf pour débugger les fonctoins */
#include "bougerPiece.h" /* inclure le module bougerPiece pour gérer les déplacement des pièces */
#include <stdlib.h> /* inclure stdlib pour utiliser la fonction rand() */


/* définition de la fonction qui compte le nombre de possibilité de capture */
/* prends en paramètre un tableau de coup et met dans ce tableau les coups pour effectuer les prises et prend un autre tableau de coup pour mettre les coup à exclure */
int nombreDePrisePossible(configuration config,piece p,coup cps[N],int *cps_l,coup cpExcls[N]){
  int i,j;
  int k=0;
  int l=0;
  int indicateurPrise = 0;
  int prise = 0;
  coup cp; /* stocker le coup à tester */
  cps_l = 0;
  
  /* POUR UN PION */
  /* tester s'il existe plus d'une possibilité de capture pour la pièce */
  if(p.tpc == PION){
    if(p.cpc == BLANC){
      if(config.t[p.posY+1][p.posX+1] % 2 != 0 && config.t[p.posY+2][p.posX+2] == 0 && p.posY+2 < 10 && p.posX+2 < 10){
	cps[k].x=p.posX+2;
	cps[k].y=p.posY+2;
	cps_l ++;
	cpExcls[k].x=p.posX+1;
	cpExcls[k].y=p.posY+1;
	prise ++;
	k++;
      }
      if(config.t[p.posY+1][p.posX-1] % 2 != 0 && config.t[p.posY+2][p.posX-2] == 0 && p.posY+2 < 10 && p.posX-2 >= 0){
	cps[k].x=p.posX-2;
	cps[k].y=p.posY+2;
	cps_l ++;
	cpExcls[k].x=p.posX-1;
	cpExcls[k].y=p.posY+1;
	prise++;
	k++;
      }
      if(config.t[p.posY-1][p.posX+1] % 2 != 0 && config.t[p.posY-2][p.posX+2] == 0 && p.posY-2 >= 0 && p.posX+2 < 10 ){
	cps[k].x=p.posX+2;
	cps[k].y=p.posY-2;
	cps_l ++;
	cpExcls[k].x=p.posX+1;
	cpExcls[k].y=p.posY-1;
	prise++;
	k++;
      }
      if(config.t[p.posY-1][p.posX-1] % 2 != 0 && config.t[p.posY-2][p.posX-2] == 0 && p.posY-2 >=0 && p.posX-2>=0){
	cps[k].x=p.posX-2;
	cps[k].y=p.posY-2;
	cps_l ++;
	cpExcls[k].x=p.posX-1;
	cpExcls[k].y=p.posY-1;
	prise++;
	k++;
      }
    }
    /* PION NOIR */
    else{
      if(config.t[p.posY+1][p.posX+1]!=0 && config.t[p.posY+1][p.posX+1]%2==0 && config.t[p.posY+2][p.posX+2] == 0 && p.posY+2 < 10 && p.posX+2 < 10){
	cps[k].x=p.posX+2;
	cps[k].y=p.posY+2;
	cps_l ++;
	cpExcls[k].x=p.posX+1;
	cpExcls[k].y=p.posY+1;
	prise ++;
	k++;
      }
      if(config.t[p.posY+1][p.posX-1]!=0 && config.t[p.posY+1][p.posX-1]%2==0 && config.t[p.posY+2][p.posX-2] == 0 && p.posY+2 < 10 && p.posX-2 >= 0){
	cps[k].x=p.posX-2;
	cps[k].y=p.posY+2;
	cps_l ++;
	cpExcls[k].x=p.posX-1;
	cpExcls[k].y=p.posY+1;
	prise++;
	k++;
      }
      if(config.t[p.posY-1][p.posX+1]!=0 && config.t[p.posY-1][p.posX+1]%2==0 && config.t[p.posY-2][p.posX+2] == 0 && p.posY-2 >= 0 && p.posX+2 < 10){
	cps[k].x=p.posX+2;
	cps[k].y=p.posY-2;
	cps_l ++;
	cpExcls[k].x=p.posX+1;
	cpExcls[k].y=p.posY-1;
	prise++;
	k++;
      }
      if(config.t[p.posY-1][p.posX-1]!=0 && config.t[p.posY-1][p.posX-1]%2==0 && config.t[p.posY-2][p.posX-2] == 0 && p.posY-2 >=0 && p.posX-2>=0){
	cps[k].x=p.posX-2;
	cps[k].y=p.posY-2;
	cps_l ++;
	cpExcls[k].x=p.posX-1;
	cpExcls[k].y=p.posY-1;
	prise++;
	k++;
      }
    }
  }
  /* POUR UNE DAME */
  else{
    /* parcourir les diagonales pour compter les possibilités de prise possible */
    /* parcourir la diagonale en bas à droite */
    for(i=p.posY,j=p.posX;i<N && j<N;i++,j++){
      cp.x = j;
      cp.y = i;
      /* si on rencontre une prise valide */
      if(priseEstValide(config,p,cp)){
	/* on le stocke dans cps et on incrémente prise */
	cps[k].x=j;
	cps[k].y=i;
	cps_l ++;
	k++;
	indicateurPrise ++;
      }
      if(indicateurPrise > 0)
	prise++;
      /* on exclus les coups testés */
      cpExcls[l]=cp;
      l++;
    }
    
    /* réinitialiser indicateurPrise */
    indicateurPrise = 0;
    
    /* parcourir la diagonale en bas à gauche */
    for(i=p.posY,j=p.posX;i<N && j>=0;i++,j--){
      cp.x = j;
      cp.y = i;
      /* si on rencontre une prise valide */
      if(priseEstValide(config,p,cp)){
	/* on le stocke dans cps et on incrémente prise */
	cps[k].x=j;
	cps[k].y=i;
	cps_l ++;
	k++;
	indicateurPrise ++;
      }
      if(indicateurPrise > 0)
	prise++;
      /* on exclus les coups testés */
      cpExcls[l]=cp;
      l++;
    }

    indicateurPrise = 0;
    
    /* parcourir la diagonale en haut à droite */
    for(i=p.posY,j=p.posX;i>=0 && j<N;i--,j++){
      cp.x = j;
      cp.y = i;
      /* si on rencontre une prise valide */
      if(priseEstValide(config,p,cp)){
	/* on le stocke dans cps et on incrémente prise */
	cps[k].y=i;
	cps[k].x=j;
	cps_l ++;
	k++;
	indicateurPrise ++;
      }
      if(indicateurPrise > 0)
	prise++;
      /* on exclus les coups testés */
      cpExcls[l]=cp;
      l++;
    }

    indicateurPrise = 0;
    
    /* parcourir la diagonale en haut à gauche */
    for(i=p.posY,j=p.posX;i>=0 && j>=0;i--,j--){
      cp.x = j;
      cp.y = i;
      /* si on rencontre une prise valide */
      if(priseEstValide(config,p,cp)){
	/* on le stocke dans cps et on incrémente prise */
	cps[k].y=i;
	cps[k].x=j;
	cps_l ++;
	k++;
	indicateurPrise ++;
      }
      if(indicateurPrise > 0)
	prise++;
      /* on exclus les coups testés */
      cpExcls[l]=cp;
      l++;
    }
    
  }

  /* on renvoie le nombre de prise possible */
  return prise;
}






/* définition de la fonction qui determine le nombre de possibilité de déplacement pour une pièce et les coups correspondants */
int nombreDeplacementPossible(configuration config,piece pc,coup cps[N]){
  int i,j;
  int k=0;
  coup cp1;
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      cp1.x = j;
      cp1.y = i;
      if(deplacerEstValide(config,pc,cp1)){
	cps[k].x = cp1.x;
	cps[k].y = cp1.y;
	k++;
      }
    }
  }
  return k;
}




/* définition DES FONCTIONS  qui va permettre à L'ORDINATEUR DE JOUER à la place du JOUEUR_NOIR */

/* définition de la fonction selectionner */
void ordinateurSelectionne(configuration config,selection *select,coup cps[N],int *cps_l){
  int i,j;
  piece pc;
  coup cpExcls[50];
  int k=0,l=0;
  selection selectPrises[20];
  selection selectDeps[20];
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      if(config.t[i][j] == 1 || config.t[i][j] == 3){
	/* determiner la piece */
	if(config.t[i][j] == 1){
	  pc.tpc = PION;
	  pc.cpc = NOIR;
	  pc.posX = j;
	  pc.posY = i;
	}
	else{
	  pc.tpc = DAME;
	  pc.cpc = NOIR;
	  pc.posX = j;
	  pc.posY = i;
	}
	/* si pour la pièce il y a au moins une prise possible */
	if(nombreDePrisePossible(config,pc,cps,cps_l,cpExcls) > 0){
	  /* stocker dans selectPrises les coordonnés de selection pour la pièce */
	  selectPrises[k].x = pc.posX;
	  selectPrises[k].y = pc.posY;
	  k++;
	}
	/* si pour la pièce il y a au moins un déplacement possible */
	if(nombreDeplacementPossible(config,pc,cps) > 0){
	  /* stocker dans selectDeps les coordonnés de selection pour la pièce */
	  selectDeps[l].x = pc.posX;
	  selectDeps[l].y = pc.posY;
	  l++;
	}
      }
    }
  }

  printf("nombre prise possible = %d\n",k);
  printf("nombre deplacement possible = %d\n",l);

  /* si k > 0 c a d qu'il y a une selection pour une prise */
  if(k>0){
    i=rand() % k;
    /* On favorise la selection pour une prise donc selectionner au hasard une selection dans selectPrises */
    select->x = selectPrises[i].x;
    select->y = selectPrises[i].y;
    printf("select Prise = %d %d \n",selectPrises[i].x,selectPrises[i].y);
    
  }
  /* sinon si l > 0 c a d qu'il y a une selection pour un déplacement */
  else if(l>0){
    i=rand() % l;
    /* On selectionne au hasard une selection dans selectDeps */
    select->x = selectDeps[i].x;
    select->y = selectDeps[i].y;
    printf("select Deps = %d %d \n",selectDeps[i].x,selectDeps[i].y);
  }
  /* sinon on ne peut ni se déplacer ni effectuer une prise donc abandonner */
  else{
    select->x = -1;
    select->y = -1;
  }
}





/* copier dans coup une autre piece */
static void copierPieceDansCoup(coup *cp,piece p){
  cp->pc.tpc = p.tpc;
  cp->pc.cpc = p.cpc;
  cp->pc.posX = p.posX;
  cp->pc.posY = p.posY;
  cp->pc.val = p.val;
}




/* définition de la fonction pour jouer un coup */
void ordinateurJouerCoup(configuration config,piece p,coup *cp){
  printf("rentré dans ordinateurJouerCoup \n\n");
  int i,j;
  int k=0,l=0;
  coup cp1;
  coup coupPrises[20];
  coup coupDeps[20];
  /* parcourir le damier pour chercher les coup valide pour une piece selectionnée */
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      cp1.x = j;
      cp1.y = i;
      copierPieceDansCoup(&cp1,p);
      /* tester si le coup est une prise valide */
      if(priseEstValide(config,p,cp1) == 1){
	/* et le mettre dans un tableau de coup des coups pour une prise */
	coupPrises[k].x=cp1.x;
	coupPrises[k].y=cp1.y;
	copierPieceDansCoup(&coupPrises[k],p);
	k++;
      }
      /* tester si le coup est un déplacement valide */
      if(deplacerEstValide(config,p,cp1) == 1){
	/* et le mettre dans un tableau de coup des coups pour un déplacement */
	coupDeps[l].x = cp1.x;
	coupDeps[l].y = cp1.y;
	copierPieceDansCoup(&coupDeps[l],p);
	l++;
      }
    }
  }

  printf("coup Dep possible : %d coup Prise possible : %d \n\n",l,k);

  /* s'il y a au moins un coup pour une prise valide */
  if(k>0){
    /* on sélectionne au hasard un coup dans coupPrises */
    i=rand() % k;
    cp->x = coupPrises[i].x;
    cp->y = coupPrises[i].y;
    copierPieceDansCoup(cp,p);
  }
  /* sinon il y a au moins un déplacement valide */
  else{
    /* on sélectionne au hasard un coup dans coupDeps */
    i=rand() % l;
    cp->x = coupDeps[i].x;
    cp->y = coupDeps[i].y;
    copierPieceDansCoup(cp,p);
  }
  
}




