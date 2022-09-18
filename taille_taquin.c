#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <unistd.h>
#include "taille_taquin.h"
#include "define.h"



/* Renvoie le choix du nombre de lignes ou de colonnes */
int boutons_ligne_colonne(void){
	
	int delay = (int) (1.0f/RAFRAICHISSEMENT)*1000000.0f;

	while(1){
		if (ToucheEnAttente()){
			switch(Touche()){
					case(XK_KP_3):
						return 3;
						
					case(XK_KP_4):
						return 4;
						
					case(XK_KP_5):
						return 5;
						
					case(XK_KP_6):
						return 6;
						
					case(XK_KP_7):
						return 7;
						
					case(XK_KP_8):
						return 8;

					case(XK_Return):
						return 4;
			}		
		}
		if( SourisCliquee()) {
			if ((_X > POSX_COLONNE1 && _Y > POSY_LIGNE1 ) && ( _X < POSX_COLONNE1 + LARGEUR_BTN_TAILLE && _Y < POSY_LIGNE1 + HAUTEUR_BTN_TAILLE))
				return 3; 

			if ((_X > POSX_COLONNE2 && _Y > POSY_LIGNE1 ) && ( _X < POSX_COLONNE2 + LARGEUR_BTN_TAILLE  && _Y < POSY_LIGNE1 + HAUTEUR_BTN_TAILLE))
				return 4;

			if ((_X > POSX_COLONNE3 && _Y > POSY_LIGNE1 ) && ( _X < POSX_COLONNE3 + LARGEUR_BTN_TAILLE  && _Y < POSY_LIGNE1 + HAUTEUR_BTN_TAILLE))
				return 5; 

			if ((_X > POSX_COLONNE1 && _Y > POSY_LIGNE2 ) && ( _X < POSX_COLONNE1 + LARGEUR_BTN_TAILLE && _Y < POSY_LIGNE2 + HAUTEUR_BTN_TAILLE))
				return 6; 

			if ((_X > POSX_COLONNE2 && _Y > POSY_LIGNE2 ) && ( _X < POSX_COLONNE2 + LARGEUR_BTN_TAILLE && _Y < POSY_LIGNE2 + HAUTEUR_BTN_TAILLE))
				return 7;

			if ((_X > POSX_COLONNE3 && _Y > POSY_LIGNE2 ) && ( _X < POSX_COLONNE3 + LARGEUR_BTN_TAILLE && _Y < POSY_LIGNE2 + HAUTEUR_BTN_TAILLE))
				return 8; 

		}
	usleep(delay);
	}
}
	
/* Copie le fond d'écran contenant les boutons et le texte pour les lignes */
void lignes(void){
	CopierZone(3,0,0,0,LARGEUR_FEN,HAUTEUR_FEN,0,0);
}
/* Copie le fond d'écran contenant les boutons et le texte pour les colonnes */
void colonnes(void){
	CopierZone(7,0,0,0,LARGEUR_FEN,HAUTEUR_FEN,0,0);

}