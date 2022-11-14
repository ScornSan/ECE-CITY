#include "../structures.h"
#include "../prototypes.h"

void condition_type(BITMAP * buffer, t_plateau* plateau, int x1, int x2, int y1, int y2, int r, int g, int b){
    for (int i = plateau->lig_mouse - x1; i < plateau->lig_mouse + x2; i++) {
        for (int j = plateau->col_mouse - y1; j < plateau->col_mouse + y2; j++) {
            if(plateau->matrice[i][j].element == 0 || x1 ==0)
                dessin_bloc_unique(buffer, i,j, plateau, r,g,b);
        }
    }
}

void affichage_zone_constru_terrain(BITMAP * buffer, t_plateau *plateau, int type){
    int compteur;
    switch(type){
        case 1: // elements sur case 1x1
            if (plateau->matrice[plateau->lig_mouse][plateau->col_mouse].element == 0)
                condition_type(buffer, plateau, 0, 1, 0, 1, 0,0, 255);
            else
                condition_type(buffer, plateau, 0, 1, 0, 1, 255, 0, 0);
            break;
        case 2:  // elements sur case 3x3
            compteur = 0;
            for (int i = plateau->lig_mouse - 1; i < plateau->lig_mouse + 2; i++) {
                for (int j = plateau->col_mouse - 1; j < plateau->col_mouse + 2; j++) {
                    if(plateau->matrice[i][j].element != 0){
                        compteur = 1;
                    }
                }
            }
            if (compteur == 0)
                condition_type(buffer, plateau, 1, 2, 1, 2, 0,0, 255);
            else
                condition_type(buffer, plateau, 1, 2, 1, 2, 255, 0, 0);
            break;
        case 3:  // elements sur case 4x6
            compteur = 0;
            for (int i = plateau->lig_mouse - 1; i < plateau->lig_mouse + 3; i++) {
                for (int j = plateau->col_mouse - 2; j < plateau->col_mouse + 4; j++) {
                    if(plateau->matrice[i][j].element != 0){
                        compteur = 1;
                    }
                }
            }
            if (compteur == 0)
                condition_type(buffer, plateau, 1, 3, 2, 4, 0,0, 255);
            else
                condition_type(buffer, plateau, 1, 3, 2, 4, 255, 0, 0);
            break;
    }
}


void placement_construction(t_affichage *hud, BITMAP* buffer, t_joueur* joueur, t_plateau* plateau, int indice){
    int clic = 0;

    while(!clic){
        affichage_hud_et_clic(hud, buffer, joueur, plateau);
        textprintf_ex(buffer,font,60,300,makecol(0,255,0),makecol(0,0,0),"%4d %4d",mouse_x,mouse_y);
        reperage_bloc_souris(plateau);
        affichage_zone_constru_terrain(buffer,plateau,3);
        quadrillage_test(buffer);
        textprintf_ex(buffer,font,300,300,makecol(0,255,0),makecol(0,0,0),"%4d %4d",plateau->lig_mouse,plateau->col_mouse);
        for(int i = 0; i< 4; i++){
            if (i == indice){
                masked_blit(hud->construction[indice][2], buffer, 0, 0, plateau->matrice[plateau->lig_mouse][plateau->col_mouse+1].x_bloc - plateau->batiment->construction[indice][2]->w/2, plateau->matrice[plateau->lig_mouse][plateau->col_mouse+1].y_bloc - plateau->batiment->construction[indice][2]->h/2, SCREEN_W, SCREEN_H);
            }
        }
        if(mouse_b&1 && plateau->lig_mouse != -1) {
            for (int i = plateau->lig_mouse - 1; i < plateau->lig_mouse + 3; i++) {
                for (int j = plateau->col_mouse - 2; j < plateau->col_mouse + 4; j++) {
                    plateau->matrice[i][j].element = indice+1;
                    plateau->matrice[i][j].b_element = plateau->batiment->construction[indice][1];
                    plateau->matrice_map[i][j] = indice+1;
                }
            }
            for(int i = 0; i<35; i++){
                for(int j = 0; j<45; j++){
                    printf("%d ", plateau->matrice_map[i][j]);
                }
                printf("\n");
            }
            clic = 1;
            usleep(CLIC);
        }
        else if(mouse_b&1){
            clic = 1;
            usleep(CLIC);
        }
        masked_blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
}