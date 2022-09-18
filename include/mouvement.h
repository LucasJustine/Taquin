#ifndef MOUVEMENT_H
#define MOUVEMENT_H

/*Vérifie si la direction donnée est possible a réalisé et interverti les images du taquin en conséquence*/
int mouvement(int tab[], int n, int p, int largeur_image, int hauteur_image, int direction, int ecran);
/*Vérifie si la souris est sur l'une des cases adjacentes à la case vide et déplace les images en conséquences*/
int controle_souris(int tab[], int n, int p, int largeur_image, int hauteur_image, int ecran);

#endif