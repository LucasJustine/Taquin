#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include "algorithme.h"
#include "affichage.h"
#include "mouvement.h"
#include "define.h"


/*Déplace les cases selon les mouvements sélectionner*/
int mouvement(int tab[], int n, int p, int largeur_image, int hauteur_image, int direction, int ecran){
	
	int position_0;
	int largeur_case = largeur_image / p;
	int hauteur_case = hauteur_image / n;
	/* Position du coin supérieur gauche du taquin*/
	int taquin_x = LARGEUR_FEN - IMAGE_X - (largeur_case + ECART) * p;
	int taquin_y = IMAGE_Y;

	position_0 = get_position(tab, n, p, 0);

	
	switch(direction){
		/* % p permet connaitre la colonne 
		   / p permet de connaitre la ligne */
		case (XK_Up) :{
			if((position_0 / p + 1 )!= n){
				int nbdeplacer = position_0 + p;
				permutation(tab + position_0, tab + nbdeplacer);
				affiche_case(tab[position_0], largeur_case, hauteur_case, p, taquin_x + (largeur_case + ECART ) * (position_0 % p), taquin_y + (hauteur_case + ECART) * (position_0 / p),ecran);
				affiche_case(tab[nbdeplacer], largeur_case, hauteur_case, p, taquin_x + (largeur_case + ECART ) * (nbdeplacer % p), taquin_y + (hauteur_case + ECART) * (nbdeplacer / p),ecran);
				return 1;
			}
			return 0;
		}

		case (XK_Down) : {
			if((position_0 / p + 1 ) != 1){
				int nbdeplacer = position_0 - p;
				permutation(tab + position_0, tab + nbdeplacer);
				affiche_case(tab[position_0], largeur_case, hauteur_case, p, taquin_x + (largeur_case + ECART ) * (position_0 % p), taquin_y + (hauteur_case + ECART) * (position_0 / p),ecran);
				affiche_case(tab[nbdeplacer], largeur_case, hauteur_case, p, taquin_x + (largeur_case + ECART ) * (nbdeplacer % p), taquin_y + (hauteur_case + ECART) * (nbdeplacer / p),ecran);
				return 1;
			}
			return 0;
			
		}

		case (XK_Left) :{
			if((position_0 % p + 1 ) != p){
				int nbdeplacer = position_0 + 1;
				permutation(tab + position_0, tab + position_0 + 1);
				affiche_case(tab[position_0], largeur_case, hauteur_case, p, taquin_x + (largeur_case + ECART ) * (position_0 % p), taquin_y + (hauteur_case + ECART) * (position_0 / p),ecran);
				affiche_case(tab[nbdeplacer], largeur_case, hauteur_case, p, taquin_x + (largeur_case + ECART ) * (nbdeplacer % p), taquin_y + (hauteur_case + ECART) * (nbdeplacer / p),ecran);
				return 1;
			}
			return 0;
		}

		case (XK_Right) : {
			if((position_0 % p + 1 ) != 1){
				int nbdeplacer = position_0 - 1;
				permutation(tab + position_0, tab + position_0 - 1);
				affiche_case(tab[position_0], largeur_case, hauteur_case, p, taquin_x + (largeur_case + ECART ) * (position_0 % p), taquin_y + (hauteur_case + ECART) * (position_0 / p),ecran);
				affiche_case(tab[nbdeplacer], largeur_case, hauteur_case, p, taquin_x + (largeur_case + ECART ) * (nbdeplacer % p), taquin_y + (hauteur_case + ECART) * (nbdeplacer / p),ecran);
				return 1;
			}
			return 0;
		}

		default:
			return 0;
	}
}	

int controle_souris(int tab[], int n, int p, int largeur_image, int hauteur_image, int ecran){
	int largeur_case = largeur_image / p;
	int hauteur_case = hauteur_image / n;

	/*Position des coins supérieur gauche et inférieur droit du taquin*/
	int min_taquin_x = LARGEUR_FEN - IMAGE_X - (largeur_case + ECART) * p;
	int min_taquin_y = IMAGE_Y;
	int max_taquin_x = LARGEUR_FEN - IMAGE_X - ECART;
	int max_taquin_y = IMAGE_Y + hauteur_image + n * ECART;

	/*Position de la case vide*/
	int position_0 = get_position(tab, n, p, 0);
	
	/*Calcul des coordonnées du coin supérieure gauche de la case vide */
	int posx_0 = min_taquin_x + (largeur_case + ECART ) * (position_0 % p);
	int posy_0 = min_taquin_y + (hauteur_case + ECART) * (position_0 / p);
	
	/*Vérifie si le clic est dans le taquin*/
	if((_X > min_taquin_x && _Y > min_taquin_y) && (_X < max_taquin_x && _Y < max_taquin_y)){
		/*Vérifie si le clic est dans la case en haut de la case vide*/
		if(_X > posx_0 && _Y > posy_0 - hauteur_case && _X < posx_0 + largeur_case && _Y < posy_0){
			mouvement(tab,n,p,largeur_image,hauteur_image,XK_Down,ecran);
			return 1;
		}
		/*Vérifie si le clic est dans la case en bas de la case vide*/
		else if(_X > posx_0 && _Y > posy_0 + hauteur_case && _X < posx_0 + largeur_case && _Y < posy_0 + 2 * hauteur_case){
			mouvement(tab,n,p,largeur_image,hauteur_image,XK_Up,ecran);
			return 1;
		}
		/*Vérifie si le clic est dans la case a gauche de la case vide*/
		else if(_X > posx_0 - largeur_case && _Y > posy_0 && _X < posx_0 && _Y < posy_0 + hauteur_case){
			mouvement(tab,n,p,largeur_image,hauteur_image,XK_Right,ecran);
			return 1;
		}
		/*Vérifie si le clic est dans la case a droite de la case vide*/
		else if(_X > posx_0 + largeur_case && _Y > posy_0 && _X < posx_0 + 2 * largeur_case && _Y < posy_0 + hauteur_case){
			mouvement(tab,n,p,largeur_image,hauteur_image,XK_Left,ecran);
			return 1;
		}
	}
	return 0;
}