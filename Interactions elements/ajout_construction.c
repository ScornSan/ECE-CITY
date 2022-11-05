#include "../structures.h"
#include "../prototypes.h"

void placement_construction(t_affichage* hud, BITMAP* buffer, t_joueur* joueur, t_plateau* plateau, int indice){
    int clic = 0;
    while(!clic){
        affichage_global(hud, buffer, joueur, plateau);
        for(int i = 0; i< 4; i++){
            if(i != indice){
                masked_blit(hud->construction[i][0], buffer, 0, 0, 10, 250 +i*100, SCREEN_W, SCREEN_H);
            }
            else if(bouton(hud->construction[indice][2], 10, 250 +indice*100)){
                masked_blit(hud->construction[indice][2], buffer, 0, 0, 10, 250 +indice*100, SCREEN_W, SCREEN_H);
            }
            else{
                masked_blit(hud->construction[indice][2], buffer, 0, 0, mouse_x - hud->construction[indice][2]->w/2, mouse_y - hud->construction[indice][2]->h/2, SCREEN_W, SCREEN_H);
            }
        }
        reperage_bloc_souris(plateau);
        if(mouse_b&1 && plateau->lig_mouse != -1){
            usleep(CLIC);
            for(int i = plateau->lig_mouse -1; i < plateau->lig_mouse +2; i++){
                for(int j = plateau->col_mouse -2; j < plateau->col_mouse +3; j++){
                    plateau->matrice[i][j].element = 2;
                }
            }
            clic = 1;
            usleep(CLIC);
        }
        else if(mouse_b&1){
            clic = 1;
            printf("sortie\n");
        }
        masked_blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(20);
    }

}