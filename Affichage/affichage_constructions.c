#include "../structures.h"
#include "../prototypes.h"
#include <time.h>


void boucle_affichage(int i, int j, int hauteur, int longueur,t_plateau * plateau, BITMAP * buffer, int position_x, int position_y, int deplacement, int type, int indice){
    for(int k = i; k< i+hauteur; k++){
        for(int l = j; l< j+longueur; l++){
            plateau->matrice[k][l].affiche = 1;
        }
    }
    switch(type){
        case 2 :   /// habitations 3x3
            masked_blit(plateau->habitations[indice]->style[plateau->habitations[indice]->niveau], buffer, 0, 0, plateau->matrice[i+position_x][j+position_y].x_bloc +2*deplacement - plateau->matrice[i][j].b_element->w/2, plateau->matrice[i+position_x][j+position_y].y_bloc +deplacement -plateau->matrice[i][j].b_element->h/2, SCREEN_W, SCREEN_H);
            break;
        case 3:   /// batiments 4x6
            masked_blit(plateau->matrice[i][j].b_element, buffer, 0, 0, plateau->matrice[i+position_x][j+position_y].x_bloc +2*deplacement - plateau->matrice[i][j].b_element->w/2, plateau->matrice[i+position_x][j+position_y].y_bloc +deplacement -plateau->matrice[i][j].b_element->h/2, SCREEN_W, SCREEN_H);
            break;
    }
}

void affichage_elements(t_affichage * hud, BITMAP *buffer, t_joueur* joueur, t_plateau * plateau){
    blit(plateau->terrain, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    /// maj evolution des habitations

    for(int x = 0; x < plateau->indice_tab_habitations; x++) // on parcours notre tableau d'habitation
    {
        if( (int)time(NULL) - plateau->habitations[x]->timer >= TIME_CYCLE && plateau->indice_tab_habitations != 0) // on verifie si le cycle de 15 secondes d'une des habitations est fini
        {
            plateau->habitations[x]->timer = time(NULL);
            maj_habitation(x, plateau, joueur, buffer, hud);
        }
        else
        {
            rectfill(buffer, 993, 723, 993 - (int)((time(NULL)) - plateau->habitations[x]->timer) * 11, 746, makecol(255, 0, 0)); // barre de temps
        }
    }
    /// affichage éléments sur le terrain
    for(int i = 0; i< 35; i++){
        for (int j = 0;j <45;j++){
            maj_routes(hud, buffer, joueur, plateau, i, j);
            maj_trottoirs(hud, buffer, joueur, plateau, i, j);
            if(plateau->matrice[i][j].affiche != 1){ ///pour voir si on affiche pas deux fois la meme maison en allant sur le bloc suivant
                switch(plateau->matrice[i][j].element){
                    case 0 :break;
                    case 1 :
                        boucle_affichage(i,j,4,6, plateau,buffer,0,3,7,3,0);
                        break;
                    case 2:
                        boucle_affichage(i,j,4,6, plateau,buffer,0,3,7,3,0);
                        break;
                    case 3:
                        boucle_affichage(i,j,4,6, plateau,buffer,0,3,7,3,0);
                        break;
                    case 4:
                        boucle_affichage(i,j,4,6, plateau,buffer,0,3,7,3,0);
                        break;
                    case 5:
                        boucle_affichage(i,j,3,3, plateau,buffer,1,1,0,2, plateau->matrice[i][j].id_element);
                        break;
                    case 6:
                        boucle_affichage(i,j,3,3, plateau,buffer,1,1,0,2, plateau->matrice[i][j].id_element);
                        break;
                    case 7:
                        boucle_affichage(i,j,3,3, plateau,buffer,1,1,0,2, plateau->matrice[i][j].id_element);
                        break;
                    case 8 :
                        boucle_affichage(i,j,3,3, plateau,buffer,1,1,0,2, plateau->matrice[i][j].id_element);
                        break;
                    case 9:
                        boucle_affichage(i,j,3,3, plateau,buffer,1,1,0,2, plateau->matrice[i][j].id_element);
                        break;
                    case 11:
                        plateau->matrice[i][j].affiche = 1;
                        dessin_bloc_unique(buffer, i, j, plateau, 0, 255, 0);
                        break;
                    case 13:
                        plateau->matrice[i][j].affiche = 1;
                        masked_blit(plateau->matrice[i][j].b_element, buffer, 0, 0, plateau->matrice[i][j].x_bloc - plateau->matrice[i][j].b_element->w/2, plateau->matrice[i][j].y_bloc -plateau->matrice[i][j].b_element->h/2, SCREEN_W, SCREEN_H);
                        break;
                    case 14:
                        plateau->matrice[i][j].affiche = 1;
                        dessin_bloc_unique(buffer, i, j, plateau, 119, 136, 153);
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