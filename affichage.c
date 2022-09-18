#include <stdio.h>
#include <stdlib.h>
#include <graph.h>
#include <unistd.h>
#include "affichage.h"
#include "jeu.h"
#include "taille_taquin.h"
#include "define.h"



/*Affiche la case du taquin à la position voulue en fonction de la taille de l'image et de la taille du taquin*/
void affiche_case(int num_case, int largeur_case, int hauteur_case, int colonne, int xx, int yy,int ecran){
	/*Position x et y du coin supérieur gauche de la case a afficher
	L'image se trouve en 0,0 dans l'écran passé en paramètre*/
    int x = largeur_case * (num_case % colonne); 
    int y = hauteur_case * (num_case / colonne);
    if(num_case != 0)
        CopierZone(ecran,0,x ,y ,largeur_case,hauteur_case, xx, yy);
    else{
        ChoisirCouleurDessin(CouleurParComposante(251,255,235));
        RemplirRectangle(xx,yy,largeur_case,hauteur_case);
    }
}

void affiche_taquin(int tab[], int ligne, int colonne ,int largeur_image, int hauteur_image, int ecran){

    int i, j;
    /* Calcule la largeur d'une case en fonction du nombre de case */
    int largeur_case = largeur_image / colonne ;

    /* Calcule la hauteur d'une case en fonction du nombre de case */
    int hauteur_case = hauteur_image / ligne ;

    /*Calcule la position du coin supérieur gauche du taquin pour équilibrer la distance
    entre l'image non découpée et le taquin*/
    int taquin_x = LARGEUR_FEN - IMAGE_X - (largeur_case + ECART) * colonne;
    int taquin_y = IMAGE_Y;
    
    /* Affiche le fond */
    CopierZone(1,0,0,0,LARGEUR_FEN,HAUTEUR_FEN,0,0);

    /* Affiche l'image non découpée */
    ChoisirCouleurDessin(CouleurParComposante(255,226,202));
    RemplirRectangle(IMAGE_X - ECART, IMAGE_Y - ECART,largeur_image + 2 * ECART, hauteur_image + 2 * ECART);
    CopierZone(ecran,0,0,0,largeur_image,hauteur_image, IMAGE_X,IMAGE_Y);

    /* Affiche le fond et le contour du taquin */
    RemplirRectangle(taquin_x - ECART,taquin_y - ECART,(largeur_case + ECART) * colonne + ECART,(hauteur_case + ECART) * ligne + ECART);
    ChoisirCouleurDessin(CouleurParComposante(251,255,235));
    RemplirRectangle(taquin_x,taquin_y,(largeur_case + ECART) * colonne - ECART,(hauteur_case + ECART) * ligne - ECART);
    /*Affiche le taquin*/
    for (i = 0; i < ligne; i++){
        for( j = 0; j < colonne; j++)
                affiche_case(tab[i * colonne + j], largeur_case, hauteur_case, colonne, taquin_x + (largeur_case + ECART ) * j, taquin_y + (hauteur_case + ECART) * i,ecran);    
    }
}

void regles(void){

	int delay = (int) (1.0f/RAFRAICHISSEMENT)*1000000.0f;
	/*Affichage du fond*/
	CopierZone(8,0,0,0,LARGEUR_FEN,HAUTEUR_FEN,0,0);
	
	while (1){	
		if( SourisCliquee()) 
			if ((_X > POSX_CONTINUER && _Y > POSY_CONTINUER) && 
				(_X < POSX_CONTINUER + LARGEUR_JOUER_QUITTER_CONTINUER && _Y < POSY_CONTINUER + HAUTEUR_JOUER_QUITTER_CONTINUER))
				return;
		usleep(delay);
	}
}	

/*Charge les images dans les écrans virtuels et renvoie 1 si le joueur veut jouer */
void charger_image(void){
	/*Crée la fenêtre et change son nom*/
	CreerFenetre(POSX_FEN,POSY_FEN,LARGEUR_FEN,HAUTEUR_FEN);
	ChoisirTitreFenetre("Taquin");
	/*Charge dans l'écran virtuel 1 le fond d'écran */
	ChoisirEcran(1);
	ChargerImage("images/imgfond.xpm",0,0,0,0,LARGEUR_FEN,HAUTEUR_FEN);

	/*affiche dans l'ecran virtuel 2 les images du menu */
	ChoisirEcran(2);
	ChargerImage("images/menu.xpm",0,0,0,0,LARGEUR_FEN,HAUTEUR_FEN);

	/*affiche dans l'ecran virtuel 3 l'image pour le fond */
	ChoisirEcran(3);
	ChargerImage("images/lignes.xpm",0,0,0,0,LARGEUR_FEN,HAUTEUR_FEN);
	

	/*affiche dans l'ecran virtuel 4 l'image pour les boutons_lignes_colonnes */
	ChoisirEcran(4);
	ChargerImage("images/leopard.xpm",0,0,0,0,LARGEUR_IMG,HAUTEUR_IMG);

	ChoisirEcran(5);
	ChargerImage("images/leopard2.xpm",0,0,0,0,LARGEUR_IMG2,HAUTEUR_IMG2);

	ChoisirEcran(6);
	ChargerImage("images/lion.xpm",0,0,0,0,LARGEUR_IMG3,HAUTEUR_IMG3); 
	/*affiche dans l'ecran virtuel 7 les images transparentes*/
	ChoisirEcran(7);
	ChargerImage("images/colonnes.xpm",0,0,0,0,LARGEUR_FEN,HAUTEUR_FEN);

	ChoisirEcran(8);
	ChargerImage("images/regle.xpm",0,0,0,0,LARGEUR_FEN,HAUTEUR_FEN);

}

void affiche_compteur(int compteur){
	int posx_chaine, posy_chaine;
	/*Chaine de caractère pour le compteur*/
	char nombre[20];
	sprintf(nombre,"Nombre de coups : %d",compteur);

	posx_chaine = LARGEUR_FEN / 2 - TailleChaineEcran(nombre,2) / 2;
	posy_chaine = HAUTEUR_FEN - 5 * TailleSupPolice(2);

	CopierZone(1,0,posx_chaine, posy_chaine - TailleSupPolice(2),TailleChaineEcran(nombre,2),
				2 * TailleSupPolice(2),posx_chaine,posy_chaine - TailleSupPolice(2));
	ChoisirCouleurDessin(CouleurParNom("white"));
	EcrireTexte(posx_chaine, posy_chaine,nombre,2);
}