#include "../structures.h"
#include "../prototypes.h"

void placement_construction(t_affichage* hud, BITMAP* buffer, t_joueur* joueur, t_plateau* plateau, int indice){
    int clic = 0;
    while(!clic){
        affichage_hud_et_clic(hud, buffer, joueur, plateau);
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
        textprintf_ex(buffer,font,60,300,makecol(0,255,0),makecol(0,0,0),"%4d %4d",mouse_x,mouse_y);
        reperage_bloc_souris(plateau);
        textprintf_ex(buffer,font,300,300,makecol(0,255,0),makecol(0,0,0),"%4d %4d",plateau->lig_mouse,plateau->col_mouse);

        if(mouse_b&1 && plateau->lig_mouse != -1) {
            usleep(CLIC);
            for (int i = plateau->lig_mouse - 1; i < plateau->lig_mouse + 3; i++) {
                for (int j = plateau->col_mouse - 2; j < plateau->col_mouse + 4; j++) {
                    plateau->matrice[i][j].element = 2;
                    plateau->matrice_map[i][j] = 2;
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
            printf("sortie\n");
        }
        masked_blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(20);
    }

}