#include "../structures.h"
#include "../prototypes.h"

void condition_type(BITMAP * buffer, t_plateau* plateau, int x1, int x2, int y1, int y2, int r, int g, int b){
    for (int i = plateau->lig_mouse - x1; i < plateau->lig_mouse + x2; i++) {
        for (int j = plateau->col_mouse - y1; j < plateau->col_mouse + y2; j++) {
            if(plateau->matrice[i][j].element == 0 || x1 == 0)
                dessin_bloc_unique(buffer, i,j, plateau, r,g,b);
        }
    }
}

void affichage_zone_constru_terrain(BITMAP * buffer, t_plateau *plateau, int type){
    int compteur;
    switch(type){
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
        affichage_hud(hud, buffer, joueur, plateau);
        textprintf_ex(buffer,font,60,300,makecol(0,255,0),makecol(0,0,0),"%4d %4d",mouse_x,mouse_y);
        reperage_bloc_souris(plateau);
        textprintf_ex(buffer,font,300,300,makecol(0,255,0),makecol(0,0,0),"%4d %4d",plateau->lig_mouse,plateau->col_mouse);
        if(indice == 4){        // si c'est une maison
            affichage_zone_constru_terrain(buffer,plateau,2);
            masked_blit(hud->construction[indice][2], buffer, 0, 0, plateau->matrice[plateau->lig_mouse][plateau->col_mouse].x_bloc - hud->construction[indice][2]->w/2 - plateau->screenx, plateau->matrice[plateau->lig_mouse][plateau->col_mouse].y_bloc - hud->construction[indice][2]->h/2 - plateau->screeny, SCREEN_W, SCREEN_H);
            if(mouse_b&1 && plateau->lig_mouse != -1) {
                t_construction * construction= init_build();
                construction->premier_bloc = plateau->matrice[plateau->lig_mouse-1][plateau->col_mouse-1];
                plateau->habitations[plateau->indice_tab_habitations] = construction;
                construction->timer = time(NULL);
                construction->distance_chateau = 1000;
                construction->id_element = plateau->indice_tab_habitations;
                for (int i = plateau->lig_mouse - 1; i < plateau->lig_mouse + 2; i++) {
                    for (int j = plateau->col_mouse - 1; j < plateau->col_mouse + 2; j++) {
                        plateau->matrice[i][j].element = indice+1;
                        plateau->matrice[i][j].b_element = hud->construction[indice][1];
                        plateau->matrice[i][j].id_element = plateau->indice_tab_habitations;
                    }
                }
                plateau->indice_tab_habitations++;
                for(int i = 0; i< 3; i++){
                    for(int j = 0;j < 3;j++){
                        construction->surface[i][j].ligne = construction->premier_bloc.ligne + i;
                        construction->surface[i][j].colonne = construction->premier_bloc.colonne + j;
                    }
                }
                clic = 1;
                usleep(CLIC);
            }
            else if(mouse_b&1){
                clic = 1;
                usleep(CLIC);
            }
        }
        else{       // si c'est un batiment
            affichage_zone_constru_terrain(buffer,plateau,3);
            for(int i = 0; i< 4; i++){
                if (i == indice){
                    masked_blit(hud->construction[indice][2], buffer, 0, 0, plateau->matrice[plateau->lig_mouse][plateau->col_mouse+1].x_bloc - hud->construction[indice][2]->w/2 - plateau->screenx, plateau->matrice[plateau->lig_mouse][plateau->col_mouse+1].y_bloc - hud->construction[indice][2]->h/2 - plateau->screeny, SCREEN_W, SCREEN_H);
                }
            }
            if(mouse_b&1 && plateau->lig_mouse != -1) {
                t_batiment * batiment = (t_batiment*)malloc(sizeof(t_batiment));
                batiment->premier_bloc = plateau->matrice[plateau->lig_mouse-1][plateau->col_mouse-2];
                batiment->indice_ordre = 0;
                batiment->id_batiment = plateau->indice_tab_batiment;
                printf("premier bloc = %d et %d", batiment->premier_bloc.ligne, batiment->premier_bloc.colonne);
                plateau->batiments[plateau->indice_tab_batiment] = batiment;

                for (int i = plateau->lig_mouse - 1; i < plateau->lig_mouse + 3; i++) {
                    for (int j = plateau->col_mouse - 2; j < plateau->col_mouse + 4; j++) {
                        plateau->matrice[i][j].element = indice+1;
                        plateau->matrice[i][j].b_element = hud->construction[indice][1];
                        plateau->matrice[i][j].id_element = plateau->indice_tab_batiment;
                    }
                }
                plateau->indice_tab_batiment++;
                for(int i = 0; i< 4; i++){
                    for(int j = 0;j < 6;j++){
                        batiment->surface[i][j].ligne = batiment->premier_bloc.ligne + i;
                        batiment->surface[i][j].colonne = batiment->premier_bloc.colonne + j;
                    }
                }
                clic = 1;
                usleep(CLIC);
            }
            else if(mouse_b&1){
                clic = 1;
                usleep(CLIC);
            }
        }
        masked_blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
}