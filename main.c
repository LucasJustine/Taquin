#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <unistd.h>
#include "affichage.h"
#include "define.h"
#include "jeu.h"

int main(void){

	int continuer = 1;
	InitialiserGraphique();
	charger_image();
	do{
		/*Tant que l'utilisateur veut continuer à jouer*/
		continuer = demarrer();
		if(continuer){
			regles();
			continuer = jouer();
		}
	}while(continuer);

	FermerGraphique();
	return EXIT_SUCCESS;
}
