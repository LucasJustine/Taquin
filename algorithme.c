#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "algorithme.h"
#include "define.h"

 

    /*Permute deux éléments*/
    void permutation(int *x, int *y){
        int z = *x;
        *x = *y;
        *y = z;
    }

    /*Initialise un tableau de n lignes et p colonnes*/
    int * initialiser_taquin(int n, int p){
        int i;
        int * tab = (int *) malloc(sizeof(int)*n*p);
        for(i = 0; i < n * p; i++)
            tab[i] = i;
        return tab;
    }

    /*Renvoie 1 si deux tableaux( n ligne(s), p colonne(s)) sont identiques*/
    int same_int_tab(const int tab1[], const int tab2[], int n, int p){
        int i;
        for(i = 0; i < n*p; i++)
            if(tab1[i] != tab2[i]) 
                return FALSE;
        return TRUE;
        
    }

    /*Retourne la position d'un nombre recherche dans le tableau. -1 si l'élément n'est pas présent*/
    int get_position(const int tab[], int ligne, int colonne, int nombre_recherche){
        int i;
        for(i = 0; i < ligne*colonne; i++){
            if(tab[i] == nombre_recherche){
                return i;
            }
        }
        return -1;   
    }


void simul_mouvement(int tab[], int n, int p, int alea){
    
    int position_0;
    position_0 = get_position(tab, n, p, 0);
    switch(alea){
        /* % p permet connaitre la colonne 
           / p permet de connaitre la ligne*/
        /*haut*/
        case (0) :{
            if((position_0 / p + 1 )!= n){
                int nbdeplacer = position_0 + p;
                permutation(tab + position_0, tab + nbdeplacer);
                return;
            }
        }
        /*bas*/
        case (1) : {
            if((position_0 / p + 1 ) != 1){
                int nbdeplacer = position_0 - p;
                permutation(tab + position_0, tab + nbdeplacer);
                return;
            }            
        }
        /*gauche*/
        case (2) : {
            if((position_0 % p + 1 ) != p){
                permutation(tab + position_0, tab + position_0 + 1);
                return;
            }
        }
        /*droite*/
        case (3) : {
            if((position_0 % p + 1 ) != 1){
                permutation(tab + position_0, tab + position_0 - 1);
                return;
            }
        }
    }
}   
    /*Mélange le taquin*/
    int * melanger_taquin(int n, int p){
        int i;
        int * tab = initialiser_taquin(n, p);
        srand(time(NULL));
            for(i = 0; i < (n*p) * (n*p) * (n*p); i++){
               simul_mouvement( tab, n, p, rand() % 4);
            }

        return tab;
    }

    