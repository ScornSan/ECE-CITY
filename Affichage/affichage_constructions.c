#include "../structures.h"
#include "../prototypes.h"

void boucle_affichage(int i, int j, int hauteur, int longueur,t_plateau * plateau, BITMAP * buffer, int position_x, int position_y, int deplacement){
    for(int k = i; k< i+hauteur; k++){
        for(int l = j; l< j+longueur; l++){
            plateau->matrice[k][l].affiche = 1;
        }
    }
    masked_blit(plateau->matrice[i][j].b_element, buffer, 0, 0, plateau->matrice[i+position_y][j+position_x].x_bloc +2*deplacement - plateau->matrice[i][j].b_element->w/2, plateau->matrice[i+position_y][j+position_x].y_bloc +deplacement -plateau->matrice[i][j].b_element->h/2, SCREEN_W, SCREEN_H);
}

void affichage_elements(t_affichage * hud,t_batiment * batiment, BITMAP *buffer, t_joueur* joueur, t_plateau * plateau){
    /// affichage éléments sur le terrain
    for(int i = 0; i< 35; i++){
        for (int j = 0;j <45;j++){
            if(plateau->matrice[i][j].affiche != 1){ ///pour voir si on affiche pas deux fois la meme maison en allant sur le bloc suivant
                int type = plateau->matrice[i][j].element;
                switch(type){
                    case 0 :break;
                    case 1 :
                        boucle_affichage(i,j,4,6, plateau,buffer,3,0,7);
                        break;
                    case 2:
                        boucle_affichage(i,j,4,6, plateau,buffer,3,0,7);
                        break;
                    case 3:
                        boucle_affichage(i,j,4,6, plateau,buffer,3,0,7);
                        break;
                    case 4:
                        boucle_affichage(i,j,4,6, plateau,buffer,3,0,7);
                        break;
                    case 5:
                        boucle_affichage(i,j,3,3, plateau,buffer,1,1,0);
                        break;
                    case 6:
                        boucle_affichage(i,j,3,3, plateau,buffer,1,1,0);
                        break;
                    case 7:
                        boucle_affichage(i,j,3,3, plateau,buffer,1,1,0);
                        break;
                    case 8 :
                        boucle_affichage(i,j,3,3, plateau,buffer,1,1,0);
                        break;
                    case 9:
                        boucle_affichage(i,j,3,3, plateau,buffer,1,1,0);
                        break;
                }
            }
        }
    }
    for(int i = 0; i<35; i++){
        for(int j = 0; j<45; j++){
            plateau->matrice[i][j].affiche = 0;
        }
    }
}