/*
 * MODULE : **** BOUGER LES PIECES ****
 * DEFINITION des fonctions pour manipuler les pions sur le damier
 * c'est à dire modifier les valeurs dans la matrice de configuration
*/


#include "type.h" /* inclusion des types manipulés dans cette modules */



/* définition de la fonction pour selectionner une piece dans une configuration */
piece selectionner(configuration *config,selection s){
  piece p;
  switch(config->t[s.y][s.x]){
  case 2:
    config->t[s.y][s.x] = -2;
    p.tpc = PION;
    p.cpc = BLANC;
    p.val = 2;
    break;
  case 1:
    config->t[s.y][s.x] = -1;
    p.tpc = PION;
    p.cpc = NOIR;
    p.val = 1;
    break;
  case 4:
    config->t[s.y][s.x] = -4;
    p.tpc = DAME;
    p.cpc = BLANC;
    p.val = 4;
    break;
  case 3:
    config->t[s.y][s.x] = -3;
    p.tpc = DAME;
    p.cpc = NOIR;
    p.val = 3;
    break;
  default:
    break;
  }

  p.posX = s.x;
  p.posY = s.y;

  return p;
  
}




/* définition de la fonction pour vérifier si une selecton dans une configuration est valide */
int selectionEstValide(configuration config, selection s){
  /* si le JOUEUR_BLANC selectionne */
  if(config.j == JOUEUR_BLANC){
    if(config.t[s.y][s.x] == 2 || config.t[s.y][s.x] == 4){
      return 1;
    }else{
      return 0;
    }
  }
  /* sinon le JOUEUR_NOIR */
  else{
    if(config.t[s.y][s.x] == 1 || config.t[s.y][s.x] == 3){
      return 1;
    }else{
      return 0;
    }
  }
}



/* définition de la fonction pour déplacer une piece sur le damier  */
void deplacerPiece(configuration *config,piece p,coup cp){
  /* enlever la piece de sa position en le mettant à 0 */
  config->t[p.posY][p.posX]=0;
  /* poser la piece à la position choisis en remplacant la valeur par la valeur stocker dans la piece p */
  config->t[cp.y][cp.x] = p.val;
}

/* définition de la fonction pour vérifier si un coup pour déplacer une pièce dans la configuration est valide selon les règles du jeu de dame */
int deplacerEstValide(configuration config,piece p,coup cp){
  int i,j;
  int nombrePiece = 0;
  /* la case où se déplacer est vide */
  if(config.t[cp.y][cp.x] == 0){
    /* PION */
    if(p.tpc == PION){
      /* NOIR */
      if(p.cpc == NOIR){
	if((cp.x == p.posX + 1 || cp.x == p.posX - 1) && cp.y == p.posY + 1){
	  return 1;
	}else{
	  return 0;
	}
      }
      /* BLANC */
      else{
	if((cp.x == p.posX + 1 || cp.x == p.posX - 1) && cp.y == p.posY - 1){
	  return 1;
	}else{
	  return 0;
	}
      }
    }
    /* DAME */
    else{
      /* si on se déplace à travers la diagonale orienté à droite */
      if(cp.x + cp.y == p.posX + p.posY){
	/* vérifier qu'il n'y a aucune pièce sur la diagonale */
	if(cp.x > p.posX){
	  for(i=p.posY-1,j=p.posX+1;i>cp.y && j<cp.x;i--,j++){
	    if(config.t[i][j] != 0){
	      nombrePiece ++;
	    }
	  }
	}
	else{
	  for(i=p.posY+1,j=p.posX-1;i<cp.y && j>cp.x;i++,j--){
	    if(config.t[i][j] != 0){
	      nombrePiece ++;
	    }
	  }
	}
	if(nombrePiece == 0){
	  return 1;
	}else{
	  return 0;
	}
      }
      else{
      
	/* si on se déplace à travers la diagonale orienté à gauche */
	/* on se déplace vers la droite */
	if(cp.x > p.posX){
	for(i=p.posY+1,j=p.posX+1;i<10 && j<10;i++,j++){
	  if(config.t[i][j] != 0)
	    nombrePiece ++;
	  if(cp.y == i && cp.x == j && nombrePiece == 0){
	    return 1;
	  }
	}
	}else{
	  /* on se déplace vers la gauche */
	  for(i=p.posY-1,j=p.posX-1;i>=0 && j>=0;i--,j--){
	    if(config.t[i][j] != 0)
	      nombrePiece ++;
	    if(cp.y == i && cp. x == j && nombrePiece == 0){
	      return 1;
	    }
	  }
	}
      }
      
      /* sinon déplacement invalide */
      return 0;
    }
  }
  /* sinon on se déplace dans une case non vide donc invalide */
  else{
    return 0;
  }
}

/* définition de la fonction prise qui permettra de prendre une piece du damier */
void prisePiece(configuration *config,piece p,coup cp){
  int i,j;
  
  /* enlever la piece prise */
  /* on a effecture une prise en haut à droite */
  if(cp.x > p.posX && cp.y < p.posY){
    /* on parcours la diagonale en haut à droite */
    for(i=p.posY-1,j=p.posX+1;i>cp.y && j<cp.x;i--,j++){
      /* enlever la première piece rencontrer */
      if(config->t[i][j] != 0){
	config->t[i][j] = 0;
      }
    }
  }
  /* si on a effectuer une prise en haut à gauche */
  else if(cp.x < p.posX && cp.y < p.posY){
    /* on parcours la diagonale en haut à gauche */
    for(i=p.posY-1,j=p.posX-1;i>cp.y && j>cp.x;i--,j--){
      /* enlever la première piece rencontrer */
      if(config->t[i][j] != 0){
	config->t[i][j] = 0;
      }
    }
  }
  /* si on a effectuer une prise en bas à droite */
  else if(cp.x > p.posX && cp.y > p.posY){
    /* on parcours la diagonale en bas à droite */
    for(i=p.posY+1,j=p.posX+1;i<cp.y && j<cp.x;i++,j++){
      /* enlever la première pièce rencontrer*/
      if(config->t[i][j] != 0){
	config->t[i][j] = 0;
      }
    }
  }
  /* sinon on a effectuer une prise en bas à gauche */
  else{
    /* on parcours la diagonale en bas à gauche */
    for(i=p.posY+1,j=p.posX-1;i<cp.y && j>cp.x;i++,j--){
      /* enlever la première pièce rencontrer */
      if(config->t[i][j] != 0){
	config->t[i][j] = 0;
      }
    }
  }

  /* déplacer la piece */
  deplacerPiece(config,p,cp);
}

/* définition de la fonction qui vérifie si une prise est valide selon les règles du jeu de dame */
int priseEstValide(configuration config,piece p,coup cp){
  int i,j;
  int posX,posY;
  int nombrePiece = 0;
  int indicateur = 0; /* pour vérifier si le coup d'une dame est bien sur les diagonales */
  
  /* prise valide pour un PION */
  if(p.tpc == PION){
    /* si on ne fait pas une prise sur la même colonne et la même ligne que la position initial de la pièce */
    if(cp.x != p.posX && cp.y != p.posY){
      /* s'il y a au moins une pièce adverse à capturée */
      if(cp.x == p.posX + 2 && cp.y == p.posY - 2 && config.t[cp.y][cp.x] == 0){
	if(p.cpc == BLANC){
	  if(config.t[p.posY - 1][p.posX + 1] % 2 != 0){
	    return 1;
	  }else{
	    return 0;
	  }
	}
	else{
	  if(config.t[p.posY - 1][p.posX + 1] == 2 || config.t[p.posY - 1][p.posX + 1] == 4){
	    return 1;
	  }else{
	    return 0;
	  }
	}
      }
      else if(cp.x == p.posX + 2 && cp.y == p.posY + 2 && config.t[cp.y][cp.x] == 0){
	if(p.cpc == BLANC){
	  if(config.t[p.posY + 1][p.posX + 1] % 2 != 0){
	    return 1;
	  }else{
	    return 0;
	  }
	}
	else{
	  if(config.t[p.posY + 1][p.posX + 1] == 2 || config.t[p.posY + 1][p.posX + 1] == 4){
	    return 1;
	  }else{
	    return 0;
	  }
	}
      }
      else if(cp.x == p.posX - 2 && cp.y == p.posY - 2 && config.t[cp.y][cp.x] == 0){
	if(p.cpc == BLANC){
	  if(config.t[p.posY - 1][p.posX - 1] % 2 != 0){
	    return 1;
	  }else{
	    return 0;
	  }
	}
	else{
	  if(config.t[p.posY - 1][p.posX - 1] == 2 || config.t[p.posY - 1][p.posX - 1] == 4){
	    return 1;
	  }else{
	    return 0;
	  }
	}
      }
      else if(cp.x == p.posX - 2 && cp.y == p.posY + 2 && config.t[cp.y][cp.x] == 0){
	if(p.cpc == BLANC){
	  if(config.t[p.posY + 1][p.posX - 1] % 2 != 0){
	    return 1;
	  }else{
	    return 0;
	  }
	}
	else{
	  if(config.t[p.posY + 1][p.posX - 1] == 2 || config.t[p.posY + 1][p.posX - 1] == 4){
	    return 1;
	  }else{
	    return 0;
	  }
	}
      }
      else{
	return 0;
      }
    }
    else{
      return 0;
    }
  }

  /* prise valide pour une DAME */
  else{
    /* si on ne fait pas une prise sur la même colonne et la même ligne que la position initiale de la pièce */
    if(cp.x != p.posX && cp.y != p.posY && config.t[cp.y][cp.x] == 0){
      /* si le coup se trouve sur les diagonales */
       if(cp.x > p.posX && cp.y > p.posY){
	for(i=p.posY+1,j=p.posX+1;i<10 && j<10;i++,j++){
	  if(cp.x == j && cp.y == i)
	    indicateur = 1;
	}
       }
       else if(cp.x > p.posX && cp.y < p.posY){
	 for(i=p.posY-1,j=p.posX+1;i>=0 && j<10;i--,j++){
	   if(cp.x == j && cp.y == i)
	    indicateur = 1;
	 }
       }
       else if(cp.x < p.posX && cp.y < p.posY){
	 for(i=p.posY-1,j=p.posX-1;i>=0 && j>=0;i--,j--){
	   if(cp.x == j && cp.y == i)
	    indicateur = 1;
	 }
       }
       else{
	 for(i=p.posY+1,j=p.posX-1;i<10 && j>=0;i++,j--){
	   if(cp.x == j && cp.y == i)
	     indicateur = 1;
	 }
       }
       /* si indicateur est nulle alors le coup n'est pas sur les diagonales */
       if(indicateur == 0){
	 return 0;
       }
      
      /* on vérifie qu'il y a qu'une seule pièce adverse et doit être la seule pièce entre la diagonale de la position de la pièce et la position où se déplacer */
      if(cp.x > p.posX && cp.y > p.posY){
	for(i=p.posY+1,j=p.posX+1;i<=cp.y && j<=cp.x;i++,j++){
	  if(config.t[i][j] != 0){
	    nombrePiece ++;
	    posX = j;
	    posY = i;
	  }
	}
	if(nombrePiece == 1){
	  if(p.cpc == BLANC){
	    if(config.t[posY][posX] % 2 != 0){
	      return 1;
	    }else{
	      return 0;
	    }
	  }
	  else{
	    if(config.t[posY][posX] % 2 == 0 ){
	      return 1;
	    }else{
	      return 0;
	    }
	  }
	}else{
	  return 0;
	}
      }
      else if(cp.x > p.posX && cp.y < p.posY){
	for(i=p.posY-1,j=p.posX+1;i>=cp.y && j<=cp.x;i--,j++){
	  if(config.t[i][j] != 0){
	    nombrePiece ++;
	    posX = j;
	    posY = i;
	  }
	  
	}
	if(nombrePiece == 1){
	  if(p.cpc == BLANC){
	    if(config.t[posY][posX] % 2 != 0){
	      return 1;
	    }else{
	      return 0;
	    }
	  }
	  else{
	    if(config.t[posY][posX] % 2 == 0){
	      return 1;
	    }else{
	      return 0;
	    }
	  }
	}else{
	  return 0;
	}
      }
      else if(cp.x < p.posX && cp.y < p.posY){
	for(i=p.posY-1,j=p.posX-1;i>=cp.y && j>=cp.x;i--,j--){
	  if(config.t[i][j] != 0){
	    nombrePiece ++;
	    posX = j;
	    posY = i;
	  }
	}
	if(nombrePiece == 1){
	  if(p.cpc == BLANC){
	    if(config.t[posY][posX] % 2 != 0){
	      return 1;
	    }else{
	      return 0;
	    }
	  }
	  else{
	    if(config.t[posY][posX] % 2 == 0){
	      return 1;
	    }else{
	      return 0;
	    }
	  }
	}else{
	  return 0;
	}
      }
      else{
	for(i=p.posY+1,j=p.posX-1;i<=cp.y && j>=cp.x;i++,j--){
	  if(config.t[i][j] != 0){
	    nombrePiece ++;
	    posX = j;
	    posY = i;
	  }
	}
	if(nombrePiece == 1){
	  if(p.cpc == BLANC){
	    if(config.t[posY][posX] % 2 != 0){
	      return 1;
	    }else{
	      return 0;
	    }
	  }
	  else{
	    if(config.t[posY][posX] % 2 == 0){
	      return 1;
	    }else{
	      return 0;
	    }
	  }
	}else{
	  return 0;
	}
      }
    }else{
      return 0;
    }
  }
}



/* définition de la fonction pour changer les pions en dame */
void changerPionEnDame(configuration *config){
  int i;
  /* un pion devient une dame si à la fin d'un coup par un joueur il se trouve dans la base du damier adverse */
  /* parcourir les bases et changer tout les pions */
  for(i=0;i<10;i++){
    if(config->t[0][i] == 2){
      config->t[0][i] = 4;
    }
    if(config->t[9][i] == 1){
      config->t[9][i] = 3;
    }
  }
}
