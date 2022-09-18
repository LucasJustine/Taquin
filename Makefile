# CHAPITRE 1 : BUT FINAL

but : projet.out

# CHAPITRE 2 : VARIABLES

OFILES = affichage.o \
         algorithme.o \
         mouvement.o \
         jeu.o \
         taille_taquin.o \
         main.o

CC = gcc
# DOSSIER Où L'ON TROUVE LES EN-TÊTES
FOLDER = include

CFLAGS = -Wall -pedantic -g -I$(FOLDER)

LIBS = -lgraph

# CHAPITRE 3 : DEPENDANCES (REGLES IMPLICITES)

main.o : $(FOLDER)/jeu.h $(FOLDER)/define.h $(FOLDER)/affichage.h

affichage.o : $(FOLDER)/affichage.h $(FOLDER)/taille_taquin.h $(FOLDER)/define.h $(FOLDER)/jeu.h

algorithme.o : $(FOLDER)/algorithme.h $(FOLDER)/define.h

mouvement.o : $(FOLDER)/algorithme.h $(FOLDER)/affichage.h $(FOLDER)/mouvement.h $(FOLDER)/define.h

jeu.o : $(FOLDER)/jeu.h $(FOLDER)/affichage.h $(FOLDER)/define.h $(FOLDER)/algorithme.h $(FOLDER)/mouvement.h $(FOLDER)/taille_taquin.h

taille_taquin.o : $(FOLDER)/taille_taquin.h $(FOLDER)/define.h

#CHAPITRE 4 : DEPENDANCES AVEC COMMANDES

projet.out : $(OFILES)
	$(CC) $(CFLAGS) -o projet.out $(OFILES) $(LIBS)

#CHAPITRE 5 : NETTOYAGE DES FICHIERS GENERES ET LANCEMENT DU PROGRAMME

clean :
	rm -f $(OFILES) projet.out


run : projet.out
	@./projet.out

#CHAPITRE 6 : BUTS FACTICES

.PHONY : but clean run
