#
# FICHIER Makefile pour automatiser la creation de l'executable de notre jeu
#

CC=gcc -Wall -W -std=c89 -pedantic
OPTIONS_MLV1= -W   `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV`
OPTIONS_MLV2=`pkg-config --libs-only-l MLV`

jeuDame : jeuDame.o plateforme.o bougerPiece.o gestionScoreEtFin.o gestionBoutton.o sauvegarde.o intelligenceArtificiel.o interfaceGraphique.o
	$(CC) $(OPTIONS_MLV1) jeuDame.o plateforme.o bougerPiece.o gestionScoreEtFin.o gestionBoutton.o  sauvegarde.o intelligenceArtificiel.o interfaceGraphique.o $(OPTIONS_MLV2) -o jeuDame
jeuDame.o : jeuDame.c type.h type.h constante.h
	$(CC) -c jeuDame.c
plateforme.o : plateforme.c plateforme.h type.h
	$(CC) -c plateforme.c
bougerPiece.o : bougerPiece.c bougerPiece.h type.h
	$(CC) -c bougerPiece.c
gestionScoreEtFin.o : gestionScoreEtFin.c gestionScoreEtFin.h type.h
	$(CC) -c gestionScoreEtFin.c
gestionBoutton.o : gestionBoutton.c gestionBoutton.h type.h
	$(CC) -c gestionBoutton.c
sauvegarde.o : sauvegarde.c sauvegarde.h type.h
	$(CC) -c sauvegarde.c
intelligenceArtificiel.o : intelligenceArtificiel.c intelligenceArtificiel.h type.h
	$(CC) -c intelligenceArtificiel.c
interfaceGraphique.o : interfaceGraphique.c interfaceGraphique.h type.h
	$(CC) -c interfaceGraphique.c

clean :
	rm  *~
