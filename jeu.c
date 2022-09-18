#include <stdio.h> 
#include <stdlib.h>
#include <graph.h>
#include <unistd.h>
#include "affichage.h"
#include "algorithme.h"
#include "taille_taquin.h"
#include "mouvement.h"
#include "jeu.h"
#include "define.h"

/* Changer nom fichier en demarrer_jeu.c */

/* Affiche les boutons JOUER et QUITTER et renvoie le choix */
int demarrer(void){

	int delay = (int) (1.0f/RAFRAICHISSEMENT)*1000000.0f;
	ChoisirEcran(0);
	CopierZone(2,0,0,0,LARGEUR_FEN,HAUTEUR_FEN,0,0);
	while (1){	
		if( SourisCliquee()) {
			
			if ((_X > POSX_JOUER &&  _Y > POSY_JOUER) && (_X < POSX_JOUER + LARGEUR_JOUER_QUITTER_CONTINUER && _Y < POSY_JOUER + HAUTEUR_JOUER_QUITTER_CONTINUER))
				return TRUE; 
 
			if ((_X > POSX_QUITTER && _Y > POSY_QUITTER)&& (_X < POSX_QUITTER + LARGEUR_JOUER_QUITTER_CONTINUER && _Y < POSY_QUITTER + HAUTEUR_JOUER_QUITTER_CONTINUER)){
				return FALSE;
			}
		}
		usleep(delay);
	}
}

int choix_img(void){

	int delay = (int) (1.0f/RAFRAICHISSEMENT)*1000000.0f;
	/*affiche le fond d'ecran*/
	CopierZone(1,0,0,0,LARGEUR_FEN,HAUTEUR_FEN,0,0);
	/*affiche les images proposées */
	/*Seules positions non définies dans des constantes*/
	CopierZone(4,0,0,0,LARGEUR_IMG,HAUTEUR_IMG,50,200);
	CopierZone(5,0,0,0,LARGEUR_IMG2,HAUTEUR_IMG2,574,200);
	CopierZone(6,0,0,0,LARGEUR_IMG3,HAUTEUR_IMG3,1300,200);

	
	while (1){
		if( SourisCliquee()) {
			if ((_X > 50 && _Y > 200 ) && ( _X < LARGEUR_IMG + 50 && _Y < HAUTEUR_IMG + 200 ))
				return 1;

			if ((_X > 574 && _Y > 200 ) && ( _X < LARGEUR_IMG2 + 574 && _Y < HAUTEUR_IMG2 + 200 ))
				return 2;

			if ((_X > 1300 && _Y > 200 ) && ( _X < LARGEUR_IMG3 + 1300 && _Y < HAUTEUR_IMG3 + 200 ))
				return 3;
		}
		/*Permet de réduire l'utilisation du processeur*/
		usleep(delay);
	}	
}


int jouer(void){
	/*Initialisation des variables */
	int ligne, colonne, largeur_image,hauteur_image,touche,ecran;
	/*Utilisation d'un tableau à une dimension*/
	int * tableau = NULL;
	/*Tableau du taquin finalisé*/
	int * tab = NULL;
	/*Variable pour le compteur*/
	int compteur = 0;
	/*Taux de rafraichissement*/
	int delay = (int) (1.0f/RAFRAICHISSEMENT)*1000000.0f;

		switch(choix_img()){
			case(1):{
				largeur_image = LARGEUR_IMG;
				hauteur_image = HAUTEUR_IMG;
				ecran = 4;
				break;
			}
				
			case(2):{
				largeur_image = LARGEUR_IMG2;
				hauteur_image = HAUTEUR_IMG2;
				ecran = 5;
				break;
			}
				
			case(3):{
				largeur_image = LARGEUR_IMG3;
				hauteur_image = HAUTEUR_IMG3;
				ecran = 6;
				break;
			}
		}
		/*Choix du nombre de lignes*/
		lignes();
		ligne = boutons_ligne_colonne();
		/*Choix du nombre de colonnes*/
		colonnes();
		colonne = boutons_ligne_colonne();
		/*Initialisation de la configuration finale*/
		tab = initialiser_taquin(ligne,colonne);
		/*Initialisation du taquin*/
		tableau = melanger_taquin( ligne, colonne );
		affiche_taquin(tableau,ligne,colonne,largeur_image,hauteur_image,ecran);
		

	while (1){
		if(ToucheEnAttente()){
			touche = Touche();
			if(touche == XK_Escape){
				free(tableau);
				return TRUE;
			}
			compteur += mouvement(tableau,ligne,colonne,largeur_image,hauteur_image,touche,ecran);
			affiche_compteur(compteur);	
		}
		else if(SourisCliquee()){
			compteur +=  controle_souris(tableau,ligne,colonne,largeur_image,hauteur_image,ecran);
			affiche_compteur(compteur);	
		}

		else if(same_int_tab(tableau, tab, ligne, colonne)){
					free(tableau);
					ChargerImage("images/win.png",IMAGE_X,IMAGE_Y,0,0,LARGEUR_WIN,HAUTEUR_WIN);
					return rejouer();
		}
		
		/*Permet de réduire l'utilisation du processeur*/
		usleep(delay);
	}
}

int rejouer(void){
	int delay = (int) (1.0f/RAFRAICHISSEMENT)*1000000.0f;
	ChargerImage("images/replay.png",POSX_REPLAY,POSY_REPLAY,0,0,LARGEUR_REPLAY,HAUTEUR_REPLAY);
	ChargerImage("images/exit.png",LARGEUR_FEN - POSX_REPLAY - LARGEUR_EXIT ,POSY_REPLAY,0,0,LARGEUR_REPLAY,HAUTEUR_REPLAY);
	while (1){	
		if( SourisCliquee()) {
			if ((_X > POSX_REPLAY && _Y > POSY_REPLAY) && 
				(_X < POSX_REPLAY + LARGEUR_REPLAY && _Y < POSY_REPLAY + HAUTEUR_REPLAY))
				return TRUE; 

			if ((_X > LARGEUR_FEN - POSX_REPLAY - LARGEUR_EXIT &&  _Y > POSY_REPLAY) && 
				(_X < LARGEUR_FEN - POSX_REPLAY - LARGEUR_EXIT + LARGEUR_EXIT && _Y < POSY_REPLAY + HAUTEUR_EXIT))
				return FALSE;
		}
		/*Permet de réduire l'utilisation du processeur*/
		usleep(delay);
	}
}